#include "exifget_data.h"
#include "libexifget.h"
#include "tiff.h"
#include "ifd_entry_value.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BYTE_ORDER_TEST_NUMBER 0x12345678
#define LEAST_SIGNIFICANT_BYTE 0x78
#define MOST_SIGNIFICANT_BYTE 0x12

#define MAGIC_NUMBER_LENGTH 4
#define JPEG_TIFF_OFFSET 12
#define JPEG_TIFF_OFFSET_2 30
#define TIFF_TIFF_OFFSET 0

#define BYTES_PER_TAG 2
#define BYTES_PER_TYPE 2
#define BYTES_PER_COUNT 4
#define BYTES_PER_VALUE_OFFSET 4

static int
file_tiff_offset(FILE *fp);

static enum exifget_byte_order
get_system_byte_order();

static int 
seek_to_ifd(exifget_data_t *data, long offset)
{
    int err;
    uint16_t num_ifd_entries;

    err = EXIFGET_ENOERR;
    if (fseek(data->fp, offset, SEEK_SET) != 0) {
#ifdef DEBUG
        fprintf(stderr, "ERROR: Bad offset 0x%lx\n", offset);
        abort();
#endif /* DEBUG */
        return EXIFGET_EOFFSET;
    }
    tiff_read_short(data, &num_ifd_entries);
    data->ifd.num_entries = num_ifd_entries;
    data->ifd.current_entry_index = 0;

    return err;
}

int
exifget_open(const char *file_name, exifget_data_t **data_ptr)
{
    FILE *fp;
    enum exifget_byte_order system_byte_order;
    int tiff_offset;
    struct tiff_header header;
    int err;
    long offset;
    uint16_t num_ifd_entries;

    *data_ptr = malloc(sizeof(struct exifget_data));
    if (*data_ptr == NULL) {
        return EXIFGET_ENOMEM;
    }

    fp = fopen(file_name, "rb");
    if (fp == NULL) {
        return EXIFGET_ECANTOPEN;
    }
    (*data_ptr)->fp = fp;

    system_byte_order = get_system_byte_order();
    if (system_byte_order == EXIFGET_UNDEFINED_BYTE_ORDER) {
        err = EXIFGET_EBYTEORDER;
        goto fatal_error;
    }
    (*data_ptr)->system_byte_order = system_byte_order;

    tiff_offset = file_tiff_offset(fp);
    if (tiff_offset < 0) {
        err = EXIFGET_EBADOFFSET;
        goto fatal_error;
    }
    (*data_ptr)->tiff_offset = tiff_offset;

    tiff_read_header(*data_ptr, &header);
    if (header.magic_number != TIFF_MAGIC_NUMBER) {
        err = EXIFGET_EBADMAGIC;
        goto fatal_error;
    }
    if (header.byte_order == TIFF_LITTLE_ENDIAN) {
        (*data_ptr)->tiff_byte_order = EXIFGET_LITTLE_ENDIAN;
    } else if (header.byte_order == TIFF_BIG_ENDIAN) {
        (*data_ptr)->tiff_byte_order = EXIFGET_BIG_ENDIAN;
    } else {
        err = EXIFGET_EBYTEORDER;
        goto fatal_error;
    }
    (*data_ptr)->next_ifd_offset = header.ifd_offset;

    (*data_ptr)->ifd.offset = header.ifd_offset;
    offset = (*data_ptr)->next_ifd_offset + (*data_ptr)->tiff_offset;
    err = seek_to_ifd(*data_ptr, offset);
    if (err != EXIFGET_ENOERR) {
        goto fatal_error;
    }

    exif_tags_array_init(&((*data_ptr)->exif_tags));

    return EXIFGET_ENOERR;

fatal_error:
    fclose(fp);
    (*data_ptr)->fp = NULL;
    free(*data_ptr);

    return err;
}

static enum exifget_byte_order
get_system_byte_order()
{
    uint32_t byte_order_test;
    uint8_t *first_byte;
    enum exifget_byte_order byte_order;

    byte_order_test = BYTE_ORDER_TEST_NUMBER;
    first_byte = (uint8_t *)(&byte_order_test);
    if (*first_byte == LEAST_SIGNIFICANT_BYTE) {
        byte_order = EXIFGET_LITTLE_ENDIAN;
    } else if (*first_byte == MOST_SIGNIFICANT_BYTE) {
        byte_order = EXIFGET_BIG_ENDIAN;
    } else {
        byte_order = EXIFGET_UNDEFINED_BYTE_ORDER;
    }
    return byte_order;
}

static int
file_tiff_offset(FILE *fp)
{
    uint8_t magic[MAGIC_NUMBER_LENGTH];
    int offset;
    size_t bytes_read;
    
    bytes_read = fread(magic, MAGIC_NUMBER_LENGTH, 1, fp);
    if (bytes_read == 0) {
#ifdef DEBUG
        fprintf(stderr, "ERROR: Could not read magic number\n");
        abort();
#endif /* DEBUG */
        return EXIFGET_EREAD;
    }
    if (magic[0] == 0xFF
            && magic[1] == 0xD8
            && magic[2] == 0xFF
            && magic[3] == 0xE1) {
        offset = JPEG_TIFF_OFFSET;
    } else if (magic[0] == 0xFF
            && magic[1] == 0xD8
            && magic[2] == 0xFF
            && magic[3] == 0xE0) {
        offset = JPEG_TIFF_OFFSET_2;
    } else if (magic[0] == 0x49
            && magic[1] == 0x49
            && magic[2] == 0x2A
            && magic[3] == 0x00) {
        offset = TIFF_TIFF_OFFSET;
    } else if (magic[0] == 0x4D
            && magic[1] == 0x4D
            && magic[2] == 0x00
            && magic[3] == 0x2A) {
        offset = TIFF_TIFF_OFFSET;
    } else {
        offset = -1;
    }

    fseek(fp, 0, SEEK_SET);

    return offset;
}

void
exifget_close(exifget_data_t *data)
{
    fclose(data->fp);
    free(data->exif_tags);
    free(data);
}

int
exifget_next_ifd_entry(exifget_data_t *data, struct ifd_entry *entry)
{
    struct ifd *ifd;
    uint16_t tag;
    uint16_t type;
    uint32_t count;
    uint32_t value_offset;
   
    ifd = &(data->ifd);
    if (ifd->current_entry_index >= ifd->num_entries) {
        return -1;
    }

    if (tiff_read_short(data, &tag) != 0) {
#ifdef DEBUG
        fprintf(stderr, "Could not read tag\n");
        abort();
#endif /* DEBUG */
        return EXIFGET_EREAD;
    }
    entry->tag = tag;

    if (tiff_read_short(data, &type) != 0) {
#ifdef DEBUG
        fprintf(stderr, "Could not read type\n");
        abort();
#endif /* DEBUG */
        return EXIFGET_EREAD;
    }
    entry->type = type;

    if (tiff_read_long(data, &count) != 0) {
#ifdef DEBUG
        fprintf(stderr, "Could not read count\n");
        abort();
#endif /* DEBUG */
        return EXIFGET_EREAD;
    }
    entry->count = count;

    if (tiff_read_long(data, &value_offset) != 0) {
#ifdef DEBUG
        fprintf(stderr, "Could not read data offset\n");
        abort();
#endif /* DEBUG */
        return EXIFGET_EREAD;
    }
    entry->value_offset = value_offset;
    entry->value.value_ascii = NULL;

    data->ifd.current_entry_index++;

    if (entry->tag == EXIF_TAG_EXIF_IFD) {
        seek_to_ifd(data, entry->value_offset + data->tiff_offset);
    }

    return 0;
}

static size_t
entry_value_size(const struct ifd_entry *entry)
{
    size_t value_size;
    size_t total_size;

    switch (entry->type) {
    case EXIFGET_IFD_ENTRY_DATA_TYPE_BYTE:
        value_size = 1;
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_ASCII:
        value_size = 1;
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SHORT:
        value_size = 2;
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_LONG:
        value_size = 4;
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_RATIONAL:
        value_size = 8;
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_UNDEFINED:
        value_size = 1;
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SLONG:
        value_size = 4;
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SRATIONAL:
        value_size = 8;
        break;
    default:
        value_size = 0;
        break;
    }

    total_size = value_size * entry->count;
    return total_size;
}

int
exifget_ifd_entry_value_load(exifget_data_t *data, struct ifd_entry *entry)
{
    long current_offset;
    long data_offset;
    int err;

    err = EXIFGET_ENOERR;

    /* Skip the MakerNote proprietary extensions */
    if (entry->tag == EXIF_TAG_MAKER_NOTE) {
        entry->count = 0;
        return err;
    }
    /* Skip the user comment */
    if (entry->tag == EXIF_TAG_USER_COMMENT) {
        entry->count = 0;
        return err;
    }

    current_offset = ftell(data->fp);
    if (entry_value_size(entry) > BYTES_PER_VALUE_OFFSET) {
        data_offset = data->tiff_offset + entry->value_offset;
    } else {
        data_offset = current_offset
            + BYTES_PER_TAG
            + BYTES_PER_TYPE
            + BYTES_PER_COUNT;
    }
    fseek(data->fp, data_offset, SEEK_SET);

    switch(entry->type) {
    case EXIFGET_IFD_ENTRY_DATA_TYPE_BYTE:
        err = ifd_entry_value_load_byte(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_ASCII:
        err = ifd_entry_value_load_ascii(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SHORT:
        err = ifd_entry_value_load_short(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_LONG:
        err = ifd_entry_value_load_long(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_RATIONAL:
        err = ifd_entry_value_load_rational(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SBYTE:
        err = ifd_entry_value_load_sbyte(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_UNDEFINED:
        err = ifd_entry_value_load_undefined(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SSHORT:
        err = ifd_entry_value_load_sshort(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SLONG:
        err = ifd_entry_value_load_slong(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SRATIONAL:
        err = ifd_entry_value_load_srational(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_FLOAT:
        err = ifd_entry_value_load_float(data, entry);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_DOUBLE:
        err = ifd_entry_value_load_double(data, entry);
        break;
    default:
        err = EXIFGET_EDATATYPE;
#ifdef DEBUG
        fprintf(stderr, "ERROR: Unrecognized data type %d\n", entry->type);
        abort();
#endif /* DEBUG */
        break;
    }

done:
    fseek(data->fp, current_offset, SEEK_SET);
    return err;
}

void
exifget_ifd_entry_value_unload(struct ifd_entry *entry)
{
    switch (entry->type) {
    case EXIFGET_IFD_ENTRY_DATA_TYPE_BYTE:
        free(entry->value.value_byte);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_ASCII:
        free(entry->value.value_ascii);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_UNDEFINED:
        free(entry->value.value_undefined);
        break;
    default:
        break;
    }
}

const char
*exifget_tag_name(const exifget_data_t *data, const struct ifd_entry *entry)
{
    return exif_tag_name_r(entry->tag, data->exif_tags);
}

static const char *exifget_error_messages[] = {
    "No Error",
    "Out of memory",
    "Could not open file",
    "Unrecognized byte order",
    "Bad offset",
    "Bad magic number",
    "Could not seek to offset",
    "Could not read from file",
    "Unrecognized data type"
};

void
exifget_perror(int err)
{
#ifdef DEBUG
    if (err < 0 || err > EXIFGET_NUM_ERRORS) {
        fprintf(stderr, "Invalid error number: %d\n", err);
        abort();
    }
#endif /* DEBUG */
    const char *err_msg = exifget_error_messages[err];
    fprintf(stderr, "ERROR: %s\n", err_msg);
}

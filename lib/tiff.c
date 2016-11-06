#include "tiff.h"
#include "exifget_data.h"
#include "exif_tags.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHORT_LENGTH 2
#define LONG_LENGTH 4

static int
tiff_read_short(const struct exifget_data *data, uint16_t *data_short)
{
    uint16_t s;

    if (fread(&s, 1, 2, data->fp) == 0) {
        return -1;
    }

    if (data->system_byte_order == EXIFGET_LITTLE_ENDIAN
            && data->tiff_byte_order == EXIFGET_BIG_ENDIAN) {
        s = swap_btol16(s);
    } else if (data->system_byte_order == EXIFGET_BIG_ENDIAN
            && data->tiff_byte_order == EXIFGET_LITTLE_ENDIAN) {
        abort(); /* TODO: Implement this */
    }

    *data_short = s;
    return 0;
}

static int
tiff_read_long(const struct exifget_data *data, uint32_t *data_long)
{
    uint32_t l;

    if (fread(&l, 1, 4, data->fp) == 0) {
        return -1;
    }

    if (data->system_byte_order == EXIFGET_LITTLE_ENDIAN
            && data->tiff_byte_order == EXIFGET_BIG_ENDIAN) {
        l = swap_btol32(l);
    } else if (data->system_byte_order == EXIFGET_BIG_ENDIAN
            && data->tiff_byte_order == EXIFGET_LITTLE_ENDIAN) {
        abort(); /* TODO: Implement this */
    }

    *data_long = l;
    return 0;
}

int
tiff_read_header(const struct exifget_data *data, struct tiff_header *header)
{
    uint16_t data_short;
    uint32_t data_long;
    struct exifget_data tmpdata;

    if (fseek(data->fp, data->tiff_offset, SEEK_SET) != 0) {
        return -1;
    }
    if (fread(&data_short, 1, 2, data->fp) == 0) {
        return -1;
    }
    tmpdata = *data;
    if (data_short == TIFF_BIG_ENDIAN) {
        tmpdata.tiff_byte_order = EXIFGET_BIG_ENDIAN;
    } else {
        tmpdata.tiff_byte_order = EXIFGET_LITTLE_ENDIAN;
    }
    header->byte_order = data_short;

    if (tiff_read_short(&tmpdata, &data_short) != 0) {
        return -1;
    }
    header->magic_number = data_short;

    if (tiff_read_long(&tmpdata, &data_long) != 0) {
        return -1;
    }
    header->ifd_offset = data_long;

    return 0;
}

int
tiff_read_ifd_entries(FILE *fp,
                      struct ifd_entry **ifd_entries_ptr,
                      int tiff_offset)
{
    uint16_t num_entries;
    int i;
    size_t bytes_read;

    if (fread(&num_entries, 1, SHORT_LENGTH, fp) == 0) {
        fprintf(stderr, "ERROR: Could not read number of IFD entries\n");
        abort();
    }
    *ifd_entries_ptr = malloc(num_entries * sizeof(struct ifd_entry));
    if (*ifd_entries_ptr == NULL) {
        fprintf(stderr, "ERROR: Could not malloc() for ifd entries\n");
        abort();
    }
    for (i = 0; i < num_entries; i++) {
        bytes_read = fread(*ifd_entries_ptr + i,
                           1,
                           sizeof(struct ifd_entry),
                           fp);
        if (bytes_read < sizeof(struct ifd_entry)) {
            fprintf(stderr, "ERROR: Could not read IFD entry\n");
            abort();
        }
    }
    return (int)num_entries;
}

static void
print_byte(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    uint8_t data;
    size_t bytes_read;

    offset = entry->data_offset;
    if (fseek(fp, offset + tiff_offset, SEEK_SET) != 0) {
        fprintf(stderr, "ERROR: could not seek to data\n");
        abort();
    }
    bytes_read = fread(&data, 1, 1, fp);
    if (bytes_read < 1) {
        fprintf(stderr, "ERROR: Could not read byte data\n");
        abort();
    }
    printf("%hhu\n", data);
}

static void
print_string(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    char *str;
    size_t bytes_read;

    str = NULL;
    offset = entry->data_offset;
    if (offset > 0) {
        if (fseek(fp, offset + tiff_offset, SEEK_SET) != 0) {
            abort();
        }
        str = malloc(entry->count);
        bytes_read = fread(str, entry->count, 1, fp);
        if (bytes_read == 0) {
            fprintf(stderr, "ERROR: Could not read string data\n");
            abort();
        }
    }
    if (str != NULL) {
        printf("%s", str);
        free(str);
    }
    printf("\n");
}

static void
print_short(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    uint16_t data;
    size_t bytes_read;

    offset = entry->data_offset;
    if(fseek(fp, offset + tiff_offset, SEEK_SET) != 0) {
        fprintf(stderr, "ERROR: Could not seek to data (short)\n");
        abort();
    }
    bytes_read = fread(&data, 1, SHORT_LENGTH, fp);
    if (bytes_read < SHORT_LENGTH) {
        fprintf(stderr, "ERROR: Could not read data (short)\n");
        abort();
    }
    printf("%hu\n", data);
}

static void
print_long(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    uint32_t data;
    size_t bytes_read;

    offset = entry->data_offset;
    if (fseek(fp, offset + tiff_offset, SEEK_SET) != 0) {
        fprintf(stderr, "ERROR: Could not seek to data (long)\n");
        abort();
    }
    bytes_read = fread(&data, 1, LONG_LENGTH, fp);
    if (bytes_read < LONG_LENGTH) {
        fprintf(stderr, "ERROR: Could not read data (long)\n");
        abort();
    }
    printf("%u\n", data);
}

static void
print_rational(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    uint32_t numerator;
    uint32_t denominator;
    size_t bytes_read;

    offset = entry->data_offset;
    fseek(fp, offset + tiff_offset, SEEK_SET);
    bytes_read = fread(&numerator, 1, 4, fp);
    if (bytes_read < LONG_LENGTH) {
        fprintf(stderr, "ERROR: Could not read numerator of rational\n");
        abort();
    }
    bytes_read = fread(&denominator, 1, 4, fp);
    if (bytes_read < LONG_LENGTH) {
        fprintf(stderr, "ERROR: Could not read denominator of rational\n");
        abort();
    }
    printf("%u/%u\n", numerator, denominator);
}

void
print_undefined(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    uint8_t data;

    offset = entry->data_offset;
    if (fseek(fp, offset + tiff_offset, SEEK_SET) != 0) {
        fprintf(stderr, "ERROR: could not seek to data\n");
        abort();
    }
    if (fread(&data, 1, 1, fp) != 0) {
        printf("%hhu\n", data);
    } else {
        printf("\n");
    }
}

static void
print_srational(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    int32_t numerator;
    int32_t denominator;

    offset = entry->data_offset;
    if (fseek(fp, offset + tiff_offset, SEEK_SET) != 0) {
        fprintf(stderr, "ERROR: could not seek to data (srational) \n");
        abort();
    }
    if (fread(&numerator, 1, 4, fp) != 0
            && fread(&denominator, 1, 4, fp) != 0) {
        printf("%d/%d\n", numerator, denominator);
    }
}

void
print_ifd_entry(const struct ifd_entry *entry, FILE *fp, int tiff_offset)
{
    long curr_offset;
    const char *tag_name;

    tag_name = exif_tag_name(entry->tag);
    if (tag_name != NULL && strlen(tag_name) > 0) {
        printf("%s ", tag_name);
    } else {
        printf("%hu ", entry->tag);
    }

    curr_offset = ftell(fp);
    switch (entry->type) {
    case 1: /* BYTE */
        print_byte(fp, entry, tiff_offset);
        break;
    case 2: /* ASCII */
        print_string(fp, entry, tiff_offset);
        break;
    case 3: /* SHORT */
        print_short(fp, entry, tiff_offset);
        break;
    case 4: /* LONG */
        print_long(fp, entry, tiff_offset);
        break;
    case 5: /* RATIONAL */
        print_rational(fp, entry, tiff_offset);
        break;
    case 7: /* UNDEFINED */
        print_undefined(fp, entry, tiff_offset);
        break;
    case 10: /* SRATIONAL */
        print_srational(fp, entry, tiff_offset);
        break;
    default:
        printf("Unrecognized data type = %d\n", entry->type);
        break;
    }
    fseek(fp, curr_offset, SEEK_SET);
}

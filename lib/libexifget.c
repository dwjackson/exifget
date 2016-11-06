#include "exifget_data.h"
#include "libexifget.h"
#include "tiff.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BYTE_ORDER_TEST_NUMBER 0x12345678
#define LEAST_SIGNIFICANT_BYTE 0x78
#define MOST_SIGNIFICANT_BYTE 0x12

#define MAGIC_NUMBER_LENGTH 4
#define JPEG_TIFF_OFFSET 12
#define TIFF_TIFF_OFFSET 0

static int
file_tiff_offset(FILE *fp);

static enum exifget_byte_order
get_system_byte_order();

int
exifget_open(const char *file_name, exifget_data_t **data_ptr)
{
    FILE *fp;
    enum exifget_byte_order system_byte_order;
    int tiff_offset;
    struct tiff_header header;

    *data_ptr = malloc(sizeof(struct exifget_data));
    if (*data_ptr == NULL) {
        return -1;
    }

    fp = fopen(file_name, "rb");
    if (fp == NULL) {
        return -1;
    }
    (*data_ptr)->fp = fp;

    system_byte_order = get_system_byte_order();
    if (system_byte_order == EXIFGET_UNDEFINED_BYTE_ORDER) {
        goto fatal_error;
    }

    tiff_offset = file_tiff_offset(fp);
    if (tiff_offset < 0) {
        goto fatal_error;
    }

    tiff_read_header(*data_ptr, &header);
    if (header.magic_number != TIFF_MAGIC_NUMBER) {
        goto fatal_error;
    }
    if (header.byte_order == TIFF_LITTLE_ENDIAN) {
        (*data_ptr)->tiff_byte_order = EXIFGET_LITTLE_ENDIAN;
    } else if (header.byte_order == TIFF_BIG_ENDIAN) {
        (*data_ptr)->tiff_byte_order = EXIFGET_BIG_ENDIAN;
    } else {
        goto fatal_error;
    }
    (*data_ptr)->next_ifd_offset = header.ifd_offset;

    return 0;

fatal_error:
    fclose(fp);
    (*data_ptr)->fp = NULL;
    free(*data_ptr);

    return -1;
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
        fprintf(stderr, "ERROR: Could not read magic number\n");
        abort();
    }
    if (magic[0] == 0xFF
            && magic[1] == 0xD8
            && magic[2] == 0xFF
            && magic[3] == 0xE1) {
        offset = JPEG_TIFF_OFFSET;
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
    free(data);
}

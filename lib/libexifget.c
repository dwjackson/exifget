#include "exifget_data.h"
#include "libexifget.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BYTE_ORDER_TEST_NUMBER 0x12345678
#define LEAST_SIGNIFICANT_BYTE 0x78
#define MOST_SIGNIFICANT_BYTE 0x12

int
exifget_open(const char *file_name, exifget_data_t **data_ptr)
{
    FILE *fp;
    uint32_t byte_order_test;
    uint8_t *first_byte;

    *data_ptr = malloc(sizeof(struct exifget_data));
    if (*data_ptr == NULL) {
        return -1;
    }

    fp = fopen(file_name, "rb");
    if (fp == NULL) {
        return -1;
    }
    (*data_ptr)->fp = fp;
    
    byte_order_test = BYTE_ORDER_TEST_NUMBER;
    first_byte = (uint8_t *)(&byte_order_test);
    if (*first_byte == LEAST_SIGNIFICANT_BYTE) {
        (*data_ptr)->system_byte_order = EXIFGET_LITTLE_ENDIAN;
    } else if (*first_byte == MOST_SIGNIFICANT_BYTE) {
        (*data_ptr)->system_byte_order = EXIFGET_BIG_ENDIAN;
    } else {
        abort();
    }

    /* TODO */

    return 0;
}

void
exifget_close(exifget_data_t *data)
{
    fclose(data->fp);
    free(data);
}

#ifndef EXIFGET_DATA_H
#define EXIFGET_DATA_H

#include <stdio.h>
#include <stdint.h>

enum exifget_byte_order {
    EXIFGET_LITTLE_ENDIAN,
    EXIFGET_BIG_ENDIAN,
    EXIFGET_UNDEFINED_BYTE_ORDER
};

struct exifget_data {
    FILE *fp;
    enum exifget_byte_order system_byte_order;
    enum exifget_byte_order tiff_byte_order;
    long tiff_offset;
    uint32_t next_ifd_offset;
};

#endif /* EXIFGET_DATA_H */

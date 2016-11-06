#ifndef EXIFGET_DATA_H
#define EXIFGET_DATA_H

#include "byte_order.h"
#include <stdio.h>
#include <stdint.h>

struct exifget_data {
    FILE *fp;
    enum exifget_byte_order system_byte_order;
    enum exifget_byte_order tiff_byte_order;
    long tiff_offset;
    uint32_t next_ifd_offset;
};

#endif /* EXIFGET_DATA_H */

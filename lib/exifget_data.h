#ifndef EXIFGET_DATA_H
#define EXIFGET_DATA_H

#include "byte_order.h"
#include "exif_tags.h"
#include <stdio.h>
#include <stdint.h>

struct ifd {
    uint32_t offset;
    int current_entry_index;
    int num_entries;
};

struct exifget_data {
    FILE *fp;
    enum exifget_byte_order system_byte_order;
    enum exifget_byte_order tiff_byte_order;
    long tiff_offset;
    uint32_t next_ifd_offset;
    struct ifd ifd;
    struct exif_tag *exif_tags;
};

#endif /* EXIFGET_DATA_H */

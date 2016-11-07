#ifndef TIFF_EXIF_H
#define TIFF_EXIF_H

#include "libexifget.h"
#include "exifget_data.h"
#include <stdio.h>
#include <stdint.h>

#define TIFF_LITTLE_ENDIAN 0x4949
#define TIFF_BIG_ENDIAN 0x4D4D
#define TIFF_MAGIC_NUMBER 42

struct tiff_header {
    uint16_t byte_order;
    uint16_t magic_number;
    uint32_t ifd_offset;
};

int
tiff_read_short(const struct exifget_data *data, uint16_t *data_short);

int
tiff_read_long(const struct exifget_data *data, uint32_t *data_long);

int
tiff_read_header(const struct exifget_data *data, struct tiff_header *header);

#endif /* TIFF_EXIF_H */

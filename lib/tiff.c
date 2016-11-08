#include "tiff.h"
#include "exifget_data.h"
#include "exif_tags.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHORT_LENGTH 2
#define LONG_LENGTH 4

int
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

int
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
tiff_read_float(const struct exifget_data *data, float *data_float)
{
    float f;

    if (fread(&f, 1, 4, data->fp) == 0) {
        return -1;
    }

    if (data->system_byte_order == EXIFGET_LITTLE_ENDIAN
            && data->tiff_byte_order == EXIFGET_BIG_ENDIAN) {
        f = swap_btol32(f);
    } else if (data->system_byte_order == EXIFGET_BIG_ENDIAN
            && data->tiff_byte_order == EXIFGET_LITTLE_ENDIAN) {
        abort(); /* TODO: Implement this */
    }

    *data_float = f;
    return 0;
}

int
tiff_read_double(const struct exifget_data *data, double *data_double)
{
    double d;

    if (fread(&d, 1, 8, data->fp) == 0) {
        return -1;
    }

    if (data->system_byte_order == EXIFGET_LITTLE_ENDIAN
            && data->tiff_byte_order == EXIFGET_BIG_ENDIAN) {
        d = swap_btol_double(d);
    } else if (data->system_byte_order == EXIFGET_BIG_ENDIAN
            && data->tiff_byte_order == EXIFGET_LITTLE_ENDIAN) {
        abort(); /* TODO: Implement this */
    }

    *data_double = d;
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

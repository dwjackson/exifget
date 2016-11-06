#ifndef EXIFGET_H
#define EXIFGET_H

enum exifget_byte_order {
    EXIFGET_LITTLE_ENDIAN,
    EXIFGET_BIG_ENDIAN
};

struct exifget_data;
typedef struct exifget_data exif_data_t;

int
exifget_open(const char *file_name, exif_data_t **data_ptr);

void
exifget_close(exifget_data_t *data);

#endif /* EXIFGET_H */

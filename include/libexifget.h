#ifndef EXIFGET_H
#define EXIFGET_H

#include <stdint.h>

struct exifget_data;
typedef struct exifget_data exifget_data_t;

struct ifd_entry {
    uint16_t tag;
    uint16_t type;
    uint32_t count;
    uint32_t data_offset;
};

union ifd_entry_data {
    uint8_t data_byte;
    uint16_t data_short;
    uint32_t data_long;
    char *string;
};

int
exifget_open(const char *file_name, exifget_data_t **data_ptr);

void
exifget_close(exifget_data_t *data);

int
exifget_next_ifd_entry(exifget_data_t *data, struct ifd_entry *entry);

#define EXIFGET_ENOERR 0
#define EXIFGET_ENOMEM 1
#define EXIFGET_ECANTOPEN 2
#define EXIFGET_EBYTEORDER 3
#define EXIFGET_EBADOFFSET 4
#define EXIFGET_EBADMAGIC 5
#define EXIFGET_EOFFSET 6
#define EXIFGET_EREAD 7

void
exifget_perror(int err);

#endif /* EXIFGET_H */

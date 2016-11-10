#ifndef EXIFGET_H
#define EXIFGET_H

#include <stdint.h>

#define EXIFGET_IFD_ENTRY_DATA_TYPE_BYTE 1
#define EXIFGET_IFD_ENTRY_DATA_TYPE_ASCII 2
#define EXIFGET_IFD_ENTRY_DATA_TYPE_SHORT 3
#define EXIFGET_IFD_ENTRY_DATA_TYPE_LONG 4
#define EXIFGET_IFD_ENTRY_DATA_TYPE_RATIONAL 5
#define EXIFGET_IFD_ENTRY_DATA_TYPE_SBYTE 6
#define EXIFGET_IFD_ENTRY_DATA_TYPE_UNDEFINED 7
#define EXIFGET_IFD_ENTRY_DATA_TYPE_SSHORT 8
#define EXIFGET_IFD_ENTRY_DATA_TYPE_SLONG 9
#define EXIFGET_IFD_ENTRY_DATA_TYPE_SRATIONAL 10
#define EXIFGET_IFD_ENTRY_DATA_TYPE_FLOAT 11
#define EXIFGET_IFD_ENTRY_DATA_TYPE_DOUBLE 12

struct exifget_data;
typedef struct exifget_data exifget_data_t;

struct ifd_entry_value_rational {
    uint32_t numerator;
    uint32_t denominator;
};

struct ifd_entry_value_srational {
    int32_t numerator;
    int32_t denominator;
};

union ifd_entry_value {
    uint8_t *value_byte;
    uint16_t value_short;
    uint32_t value_long;
    char *value_ascii;
    struct ifd_entry_value_rational value_rational;
    int8_t value_sbyte;
    uint8_t *value_undefined;
    int16_t value_sshort;
    int32_t value_slong;
    struct ifd_entry_value_srational value_srational;
    float value_float;
    double value_double;
};

struct ifd_entry {
    uint16_t tag;
    uint16_t type;
    uint32_t count;
    uint32_t value_offset;
    union ifd_entry_value value;
};

int
exifget_open(const char *file_name, exifget_data_t **data_ptr);

void
exifget_close(exifget_data_t *data);

int
exifget_next_ifd_entry(exifget_data_t *data, struct ifd_entry *entry);

int
exifget_ifd_entry_value_load(exifget_data_t *data, struct ifd_entry *entry);

void
exifget_ifd_entry_value_unload(struct ifd_entry *entry);

const char
*exifget_tag_name(const exifget_data_t *data, const struct ifd_entry *entry);

#define EXIFGET_ENOERR 0
#define EXIFGET_ENOMEM 1
#define EXIFGET_ECANTOPEN 2
#define EXIFGET_EBYTEORDER 3
#define EXIFGET_EBADOFFSET 4
#define EXIFGET_EBADMAGIC 5
#define EXIFGET_EOFFSET 6
#define EXIFGET_EREAD 7
#define EXIFGET_EDATATYPE 9

void
exifget_perror(int err);

#endif /* EXIFGET_H */

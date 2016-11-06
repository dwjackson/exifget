#ifndef BYTE_ORDER_H
#define BYTE_ORDER_H

#include <stdint.h>

enum exifget_byte_order {
    EXIFGET_LITTLE_ENDIAN,
    EXIFGET_BIG_ENDIAN,
    EXIFGET_UNDEFINED_BYTE_ORDER
};

uint16_t
swap_btol16(uint16_t data);

#endif /* BYTE_ORDER_H */

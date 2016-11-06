#include "byte_order.h"
#include <stdint.h>

uint16_t
swap_btol16(uint16_t data)
{
    uint16_t swapped_data;
    
    swapped_data = (data >> 8) & 0x00FF; 
    swapped_data |= (data << 8) & 0xFF00;

    return swapped_data;
}

uint32_t
swap_btol32(uint32_t data)
{
    uint32_t swapped_data;
    /* TODO */
}

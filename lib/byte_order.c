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

    swapped_data = (data >> 24) & 0x000000FF;
    swapped_data |= (data >> 8) & 0x0000FF00;
    swapped_data |= (data << 8) & 0x00FF0000;
    swapped_data |= (data << 24) & 0xFF000000;

    return swapped_data;
}

double
swap_btol_double(double data)
{
    uint64_t swapped_data;
    uint64_t original_data;
    double *dp;

    original_data = (uint64_t) data;

    swapped_data = (original_data >> 56) & 0x00000000000000FF;
    swapped_data |= (original_data >> 40) & 0x000000000000FF00;
    swapped_data |= (original_data >> 24) & 0x0000000000FF0000;
    swapped_data |= (original_data >> 8) & 0x00000000FF000000;
    swapped_data |= (original_data << 8) & 0x000000FF00000000;
    swapped_data |= (original_data << 24) & 0x0000FF0000000000;
    swapped_data |= (original_data << 40) & 0x00FF000000000000;
    swapped_data |= (original_data << 56) & 0xFF00000000000000;

    dp = (double *)(&swapped_data);
    return *dp;
}

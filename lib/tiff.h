#ifndef TIFF_EXIF_H
#define TIFF_EXIF_H

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

struct ifd_entry {
    uint16_t tag;
    uint16_t type;
    uint32_t count;
    uint32_t data_offset;
};

void
tiff_read_header(FILE *fp, struct tiff_header *header);

int
tiff_read_ifd_entries(FILE *fp,
                      struct ifd_entry **ifd_entries_ptr,
                      int tiff_offset);

void
print_ifd_entry(const struct ifd_entry *entry, FILE *fp, int tiff_offset);

#endif /* TIFF_EXIF_H */

#include "tiff_exif.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define USAGE_FMT "Usage: %s [options] [photo_file]\n"

#define JPEG_TIFF_OFFSET 12
#define TIFF_TIFF_OFFSET 0

void
print_ifds(const char *file_name);

int
file_tiff_offset(FILE *fp);

int
main(int argc, char *argv[])
{
    char *file_name;

    if (argc < 2) {
        printf(USAGE_FMT, argv[0]);
        exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    print_ifds(file_name);
    
    return 0;
}

void
print_ifds(const char *file_name)
{
    FILE *fp;
    int tiff_offset;
    struct tiff_header tiff_header;
    long offset;
    int num_ifd_entries;
    struct ifd_entry *ifd_entries;
    uint32_t next_ifd_offset;
    int i;
    struct ifd_entry entry;

    fp = fopen(file_name, "rb");
    if (fp == NULL) {
        perror("Error opening photo file");
        exit(EXIT_FAILURE);
    }
    tiff_offset = file_tiff_offset(fp);
    if (tiff_offset < 0) {
        fprintf(stderr, "ERROR: Unrecognized file type\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fseek(fp, (long)tiff_offset, SEEK_SET);
    fread(&tiff_header, 1, sizeof(struct tiff_header), fp);
    next_ifd_offset = tiff_header.ifd_offset;
    while (next_ifd_offset != 0) {
        offset = (long)next_ifd_offset;
        fseek(fp, offset + tiff_offset, SEEK_SET);
        num_ifd_entries = tiff_read_ifd_entries(fp, &ifd_entries, tiff_offset);
        for (i = 0; i < num_ifd_entries; i++) {
            entry = ifd_entries[i];
            print_ifd_entry(&entry, fp, tiff_offset);
        }
        free(ifd_entries);
        fread(&next_ifd_offset, 1, 4, fp);
    }
    fclose(fp);
}

int
file_tiff_offset(FILE *fp)
{
    uint8_t magic[4];
    int offset;
    
    fread(magic, 4, 1, fp);
    if (magic[0] == 0xFF
            && magic[1] == 0xD8
            && magic[2] == 0xFF
            && magic[3] == 0xE1) {
        offset = JPEG_TIFF_OFFSET;
    } else if (magic[0] == 0x49
            && magic[1] == 0x49
            && magic[2] == 0x2A
            && magic[3] == 0x00) {
        offset = TIFF_TIFF_OFFSET;
    } else if (magic[0] == 0x4D
            && magic[1] == 0x4D
            && magic[2] == 0x00
            && magic[3] == 0x2A) {
        offset = TIFF_TIFF_OFFSET;
    } else {
        offset = -1;
    }

    fseek(fp, 0, SEEK_SET);

    return offset;
}

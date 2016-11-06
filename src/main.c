#include "libexifget.h"
#include <stdio.h>
#include <stdlib.h>

#define USAGE_FMT "Usage: %s [photo_file]\n"

/*
void
print_ifds(const char *file_name);

void
print_ifd(FILE *fp, long offset, int tiff_offset);
*/

int
main(int argc, char *argv[])
{
    char *file_name;
    exifget_data_t *data;

    if (argc < 2) {
        printf(USAGE_FMT, argv[0]);
        exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    if (exifget_open(file_name, &data) != 0) {
        fprintf(stderr, "ERROR: Could not read picture file: %s\n", file_name);
        exit(EXIT_FAILURE);
    }
    /* TODO: print_ifds(file_name); */
    exifget_close(data);
    
    return 0;
}

/*
void
print_ifds(const char *file_name)
{
    FILE *fp;
    int tiff_offset;
    size_t bytes_read;
    struct tiff_header tiff_header;
    long offset;
    uint32_t next_ifd_offset;
    int i;

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
    tiff_read_header(fp, &tiff_header);
    next_ifd_offset = tiff_header.ifd_offset;
    while (next_ifd_offset != 0 || bytes_read == 0) {
        offset = (long)next_ifd_offset;
        print_ifd(fp, offset, tiff_offset);
        bytes_read = fread(&next_ifd_offset, 1, 4, fp);
    }
    fclose(fp);
}

void
print_ifd(FILE *fp, long offset, int tiff_offset)
{
    int num_ifd_entries;
    struct ifd_entry *ifd_entries;
    struct ifd_entry entry;
    int i;

    fseek(fp, offset + tiff_offset, SEEK_SET);
    num_ifd_entries = tiff_read_ifd_entries(fp, &ifd_entries, tiff_offset);
    for (i = 0; i < num_ifd_entries; i++) {
        entry = ifd_entries[i];
        if (entry.tag != EXIF_TAG_EXIF_IFD) {
            print_ifd_entry(&entry, fp, tiff_offset);
        } else {
            print_ifd(fp, (long)(entry.data_offset), tiff_offset);
        }
    }
    free(ifd_entries);
}
*/

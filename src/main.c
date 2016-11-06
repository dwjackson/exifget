#include "libexifget.h"
#include <stdio.h>
#include <stdlib.h>

#define USAGE_FMT "Usage: %s [photo_file]\n"

/*
void
print_ifd(FILE *fp, long offset, int tiff_offset);
*/

int
main(int argc, char *argv[])
{
    char *file_name;
    exifget_data_t *data;
    int err;

    if (argc < 2) {
        printf(USAGE_FMT, argv[0]);
        exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    err = exifget_open(file_name, &data);
    if (err != EXIFGET_ENOERR) {
        exifget_perror(err);
        exit(EXIT_FAILURE);
    }
    /* TODO: print IFDs */
    exifget_close(data);
    
    return 0;
}

/*
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

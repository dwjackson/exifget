#include "libexifget.h"
#include "exif_print.h"
#include <stdio.h>
#include <stdlib.h>

#define USAGE_FMT "Usage: %s [photo_file]\n"

int
main(int argc, char *argv[])
{
    char *file_name;
    exifget_data_t *data;
    int err;
    struct ifd_entry entry;
    int retval;

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
    while ((retval = exifget_next_ifd_entry(data, &entry)) == 0) {
        retval = exifget_ifd_entry_data_load(data, &entry);
        if (retval != EXIFGET_ENOERR) {
            break;
        }
        print_ifd_entry(data, &entry);
        exifget_ifd_entry_data_unload(&entry);
    }
    if (retval > 0) {
        err = retval;
        exifget_perror(err);
        exit(EXIT_FAILURE);
    }
    exifget_close(data);
    
    return 0;
}

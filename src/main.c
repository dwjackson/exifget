#include "libexifget.h"
#include "exif_print.h"
#include "exifget_options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define USAGE_FMT "Usage: %s [photo_file]\n"

void
print_help();

int
main(int argc, char *argv[])
{
    char *file_name;
    exifget_data_t *data;
    int err;
    struct ifd_entry entry;
    int retval;
    extern char *optarg;
    extern int optind;
    int opt;
    struct exifget_options opts;
    char *delineated_tags;
    int i;
    const char *tag_name;

    if (argc < 2) {
        printf(USAGE_FMT, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    delineated_tags = NULL;

    exifget_options_init(&opts);
    while ((opt = getopt(argc, argv, "hlt:")) != -1) {
        switch(opt) {
        case 'h':
            print_help(argv);
            exit(EXIT_SUCCESS);
            break;
        case 'l':
            opts.flags |= EXIFGET_FLAG_LIST;
            break;
        case 't':
            delineated_tags = strdup(optarg);
            break;
        default:
            /* Do nothing */
            break;
        }
    }

    file_name = argv[optind];
    err = exifget_open(file_name, &data);
    if (err != EXIFGET_ENOERR) {
        exifget_perror(err);
        exit(EXIT_FAILURE);
    }

    /* Set up Options */
    if (delineated_tags != NULL) {
        exifget_options_set_tags(data, &opts, delineated_tags);
    }

    /* Read the picture file's Exif data */
    while ((retval = exifget_next_ifd_entry(data, &entry)) == 0) {
        retval = exifget_ifd_entry_value_load(data, &entry);
        if (retval != EXIFGET_ENOERR) {
            break;
        }
        if (opts.flags & EXIFGET_FLAG_TAGS) {
            for (i = 0; i < opts.num_tags; i++) {
                if (opts.tags[i] == entry.tag) {
                    print_ifd_entry(data, &entry);
                }
            }
        } else if (opts.flags & EXIFGET_FLAG_LIST) {
            tag_name = exifget_tag_name(data, &entry);
            printf("%s\n", tag_name);
        } else {
            print_ifd_entry(data, &entry);
        }
        exifget_ifd_entry_value_unload(&entry);
    }
    if (retval > 0) {
        err = retval;
        exifget_perror(err);
        exit(EXIT_FAILURE);
    }
    exifget_close(data);

    exifget_options_destroy(&opts);
    if (delineated_tags != NULL) {
        free(delineated_tags);
    }
    
    return 0;
}

void
print_help(char *argv[])
{
    printf(USAGE_FMT, argv[0]);
    printf("Options:\n");
    printf("\t-h Show this help text\n");
    printf("\t-l List tags in the file, do not print values\n");
    printf("\t-t Specify a comma-delimited list of Exif tags to print\n");
}

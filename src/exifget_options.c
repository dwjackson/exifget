#include "exifget_options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER_CHAR ','
#define DELIMITER_STR ","

void
exifget_options_init(struct exifget_options *opts)
{
    opts->flags = 0x0;
    opts->num_tags = 0;
    opts->tags = NULL;
}

void
exifget_options_destroy(struct exifget_options *opts)
{
    if (opts->tags != NULL) {
        free(opts->tags);
    }
}

void
exifget_options_set_tags(const exifget_data_t *data,
                         struct exifget_options *opts,
                         const char *tags_arg)
{
    size_t num_tags;
    int i;
    int ch;
    char *delineated_tags;
    char *tag;
    char *last;
    uint16_t tag_id;
    
    if (strlen(tags_arg) > 0) {
        num_tags = 1;
    } else {
        num_tags = 0;
    }
    for (i = 0; i < strlen(tags_arg); i++) {
        ch = tags_arg[i];
        if (ch == DELIMITER_CHAR) {
            num_tags++;
        }
    }

    opts->flags |= EXIFGET_FLAG_TAGS;
    opts->num_tags = num_tags;
    opts->tags = malloc(sizeof(uint32_t) * num_tags);
    if (opts->tags == NULL) {
        abort();
    }

    delineated_tags = strdup(tags_arg);
    if (delineated_tags == NULL) {
        abort();
    }
    tag = strtok_r(delineated_tags, DELIMITER_STR, &last);
    i = 0;
    while (tag != NULL) {
        tag_id = exifget_tag_from_tag_name(data, tag);
        if (tag_id == 0) {
            fprintf(stderr, "Unrecognized tag: %s\n", tag);
            exit(EXIT_FAILURE);
        }
        (opts->tags)[i] = tag_id;
        tag = strtok_r(NULL, DELIMITER_STR, &last);
        i++;
    }
    free(delineated_tags);
}

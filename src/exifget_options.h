#ifndef EXIFGET_OPTIONS_H
#define EXIFGET_OPTIONS_H

#include "libexifget.h"
#include <stdint.h>
#include <stdlib.h>

#define EXIFGET_FLAG_TAGS 0x1

struct exifget_options {
    uint32_t flags;
    size_t num_tags;
    uint16_t *tags;
};

void
exifget_options_init(struct exifget_options *opts);

void
exifget_options_destroy(struct exifget_options *opts);

void
exifget_options_set_tags(const exifget_data_t *data,
                         struct exifget_options *opts,
                         const char *tags_arg);

#endif /* EXIFGET_OPTIONS_H */

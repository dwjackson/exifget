#include "exifget_data.h"
#include "libexifget.h"
#include <stdio.h>

int
exifget_open(const char *file_name, exifget_data_t **data_ptr)
{
    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL) {
        return -1;
    }
    (*data_ptr)->fp = fp;
    
    /* TODO */
}

void
exifget_close(exifget_data_t *data)
{
    fclose(data->fp);
}

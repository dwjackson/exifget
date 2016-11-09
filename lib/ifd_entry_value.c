#include "libexifget.h"
#include "exifget_data.h"
#include <stdio.h>
#include <stdlib.h>
    
int
ifd_entry_value_load_byte(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;
    err = EXIFGET_ENOERR;

    if (fread(&(entry->value.value_byte), 1, 1, data->fp) == 0) {
        if (ferror(data->fp)) {
#ifdef DEBUG
            fprintf(stderr, "Could not read byte data\n");
            abort();
#endif /* DEBUG */
            err = EXIFGET_EREAD;
        }
    }
    return err;
}

int
ifd_entry_value_load_ascii(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;
    err = EXIFGET_ENOERR;
    size_t ascii_value_bufsize;
    int ret;

    ascii_value_bufsize = entry->count;
    entry->value.value_ascii = malloc(ascii_value_bufsize);
    ret = fread(entry->value.value_ascii, ascii_value_bufsize, 1, data->fp);
    if (ret == 0) {
        free(entry->value.value_ascii);
        err = ret;
    } else {
        (entry->value.value_ascii)[ascii_value_bufsize - 1] = '\0';
    }
    
    return err;
}
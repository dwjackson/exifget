#include "libexifget.h"
#include "exifget_data.h"
#include <stdio.h>
#include <stdlib.h>
    
int
ifd_entry_value_read_byte(exifget_data_t *data, struct ifd_entry *entry)
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

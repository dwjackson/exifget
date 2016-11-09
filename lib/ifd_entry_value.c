#include "libexifget.h"
#include "exifget_data.h"
#include "tiff.h"
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

int
ifd_entry_value_load_short(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;
    err = tiff_read_short(data, &(entry->value.value_short));
    return err;
}

int
ifd_entry_value_load_long(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;
    err = tiff_read_long(data, &(entry->value.value_long));
    return err;
}

int
ifd_entry_value_load_rational(exifget_data_t *data, struct ifd_entry *entry)
{
    int ret;
    int err;

    err = EXIFGET_ENOERR;
    ret = tiff_read_long(data, &(entry->value.value_rational.numerator));
    if (ret != 0) {
        err = ret;
        goto done;
    } else {
        ret = tiff_read_long(data, &(entry->value.value_rational.denominator));
        if (ret != 0) {
            err = ret;
        }
    }

done:
    return err;
}

int
ifd_entry_value_load_sbyte(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;

    err = EXIFGET_ENOERR;
    if (fread(&(entry->value.value_sbyte), 1, 1, data->fp) == 0) {
#ifdef DEBUG
        if (ferror(data->fp)) {
            fprintf(stderr, "Could not read sbyte data\n");
        } else if (feof(data->fp)) {
            fprintf(stderr, "Could not read sbyte data, unexpected EOF\n");
        }
        abort();
#endif /* DEBUG */
        err = EXIFGET_EREAD;
    }

    return err;
}

int
ifd_entry_value_load_undefined(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;
    err = EXIFGET_ENOERR;
    if (fread(&(entry->value.value_undefined), 1, 1, data->fp) == 0) {
        if (ferror(data->fp)) {
#ifdef DEBUG
            perror(NULL);
            fprintf(stderr, "Could not read undefined data\n");
            perror(NULL);
            abort();
#endif /* DEBUG */
            err = EXIFGET_EREAD;
        }
    }
    return err;
}

int
ifd_entry_value_load_sshort(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;
    err = tiff_read_short(data, &(entry->value.value_sshort));
    return err;
}

int
ifd_entry_value_load_slong(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;
    err = tiff_read_long(data, &(entry->value.value_slong));
    return err;
}

int
ifd_entry_value_load_srational(exifget_data_t *data, struct ifd_entry *entry)
{
    int ret;
    int err;

    err = EXIFGET_ENOERR;
    ret = tiff_read_long(data, &(entry->value.value_srational.numerator));
    if (ret != 0) {
        err = ret;
    } else {
        ret = tiff_read_long(data, &(entry->value.value_srational.denominator));
        if (ret != 0) {
            err = ret;
        }
    }
    return err;
}

int
ifd_entry_value_load_float(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;
    err = tiff_read_float(data, &(entry->value.value_float));
    return err;
}

int
ifd_entry_value_load_double(exifget_data_t *data, struct ifd_entry *entry)
{
    int err;
    err = tiff_read_double(data, &(entry->value.value_double));
    return err;
}

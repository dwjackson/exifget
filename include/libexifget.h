#ifndef EXIFGET_H
#define EXIFGET_H

struct exifget_data;
typedef struct exifget_data exifget_data_t;

int
exifget_open(const char *file_name, exifget_data_t **data_ptr);

void
exifget_close(exifget_data_t *data);

#define EXIFGET_ENOERR 0
#define EXIFGET_ENOMEM 1
#define EXIFGET_ECANTOPEN 2
#define EXIFGET_EBYTEORDER 3
#define EXIFGET_EBADOFFSET 4
#define EXIFGET_EBADMAGIC 5

void
exifget_perror(int err);

#endif /* EXIFGET_H */

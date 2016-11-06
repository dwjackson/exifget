#ifndef EXIFGET_H
#define EXIFGET_H

struct exifget_data;
typedef struct exifget_data exifget_data_t;

int
exifget_open(const char *file_name, exifget_data_t **data_ptr);

void
exifget_close(exifget_data_t *data);

#endif /* EXIFGET_H */

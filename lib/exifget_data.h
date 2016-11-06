#ifndef EXIFGET_DATA_H
#define EXIFGET_DATA_H

struct exifget_data {
    FILE *fp;
    enum exifget_byte_order system_byte_order;
    enum exifget_byte_order picture_byte_order;
    long tiff_offset;
};

#endif /* EXIFGET_DATA_H */

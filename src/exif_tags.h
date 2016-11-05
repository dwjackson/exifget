#ifndef EXIF_TAGS_H
#define EXIF_TAGS_H

#include <stdint.h>

#define NUM_EXIF_TAGS (0x1 << 16)
#define EXIF_TAG_NAME_BUFSIZE 40

struct exif_tag {
    uint16_t id;
    char name[EXIF_TAG_NAME_BUFSIZE];
};

/* Tag IDs */
#define EXIF_TAG_IMAGE_WIDTH                    256
#define EXIF_TAG_IMAGE_LENGTH                   257
#define EXIF_TAG_BITS_PER_SAMPLE                258
#define EXIF_TAG_COMPRESSION                    259
#define EXIF_TAG_PHOTOMETRIC_INTERPRETATION     262
#define EXIF_TAG_MAKE                           271
#define EXIF_TAG_MODEL                          272
#define EXIF_TAG_STRIP_OFFSETS                  273
#define EXIF_TAG_ORIENTATION                    274
#define EXIF_TAG_SAMPLES_PER_PIXEL              277
#define EXIF_TAG_ROWS_PER_STRIP                 278
#define EXIF_TAG_STRIP_BYTE_COUNTS              279
#define EXIF_TAG_X_RESOLUTION                   282
#define EXIF_TAG_Y_RESOLUTION                   283
#define EXIF_TAG_PLANAR_CONFIGURATION           284
#define EXIF_TAG_RESOLUTION_UNIT                296
#define EXIF_TAG_DATETIME                       306
#define EXIF_TAG_ARTIST                         315
#define EXIF_TAG_JPEG_INTERCHANGE_FORMAT        513
#define EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH 514
#define EXIF_TAG_COPYRIGHT                    33432
#define EXIF_TAG_EXPOSURE_TIME                33434
#define EXIF_TAG_FNUMBER                      33437
#define EXIF_TAG_EXIF_IFD                     34665
#define EXIF_TAG_EXPOSURE_PROGRAM             34850
#define EXIF_TAG_DATETIME_ORIGINAL            36867
#define EXIF_TAG_DATETIME_DIGITIZED           36868
#define EXIF_TAG_COMPONENTS_CONFIGURATION     37121

void
exif_tags_array_init(struct exif_tag **exif_tags_ptr);

char
*exif_tag_name_r(uint16_t tag, struct exif_tag *exif_tags);

char
*exif_tag_name(uint16_t tag);

#endif /* EXIF_TAGS_H */

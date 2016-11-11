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
#define EXIF_TAG_SOFTWARE                       305
#define EXIF_TAG_DATETIME                       306
#define EXIF_TAG_ARTIST                         315
#define EXIF_TAG_JPEG_INTERCHANGE_FORMAT        513
#define EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH 514
#define EXIF_TAG_YCBCR_POSITIONING                  531
#define EXIF_TAG_COPYRIGHT                    33432
#define EXIF_TAG_EXPOSURE_TIME                33434
#define EXIF_TAG_FNUMBER                      33437
#define EXIF_TAG_EXIF_IFD                     34665
#define EXIF_TAG_EXPOSURE_PROGRAM             34850
#define EXIF_TAG_PHOTOGRAPHIC_SENSITIVITY     34855
#define EXIF_TAG_EXIF_VERSION                 36864
#define EXIF_TAG_DATETIME_ORIGINAL            36867
#define EXIF_TAG_DATETIME_DIGITIZED           36868
#define EXIF_TAG_COMPONENTS_CONFIGURATION     37121
#define EXIF_TAG_COMPRESSED_BITS_PER_PIXEL    37122
#define EXIF_TAG_SHUTTER_SPEED                37377
#define EXIF_TAG_APERTURE                     37378
#define EXIF_TAG_EXPOSURE_BIAS                37380
#define EXIF_TAG_MAX_APERTURE_VALUE           37381
#define EXIF_TAG_METERING_MODE                37383
#define EXIF_TAG_LIGHT_SOURCE                 37384
#define EXIF_TAG_FLASH                        37385
#define EXIF_TAG_FOCAL_LENGTH                 37386
#define EXIF_TAG_MAKER_NOTE                   37500
#define EXIF_TAG_USER_COMMENT                 37510
#define EXIF_TAG_SUBSEC_TIME                  37520
#define EXIF_TAG_SUBSEC_TIME_ORIGINAL         37521
#define EXIF_TAG_SUBSEC_TIME_DIGITIZED        37522
#define EXIF_TAG_FLASHPIX_VERSION             40960
#define EXIF_TAG_COLOR_SPACE                  40961
#define EXIF_TAG_PIXEL_X_DIMENSION            40962
#define EXIF_TAG_PIXEL_Y_DIMENSION            40963
#define EXIF_TAG_INTEROPERABILITY_IFD         40965
#define EXIF_TAG_FOCAL_PLANE_X_RESOLUTION     41486
#define EXIF_TAG_FOCAL_PLANE_Y_RESOLUTION     41487
#define EXIF_TAG_FOCAL_PLANE_RESOLUTION_UNIT  41488
#define EXIF_TAG_SENSING_METHOD               41495
#define EXIF_TAG_FILE_SOURCE                  41728
#define EXIF_TAG_SCENE_TYPE                   41729
#define EXIF_TAG_CFA_PATTERN                  41730
#define EXIF_TAG_CUSTOM_RENDERED              41985
#define EXIF_TAG_EXPOSURE_MODE                41986
#define EXIF_TAG_WHITE_BALANCE                41987
#define EXIF_TAG_DIGITAL_ZOOM_RATIO           41988
#define EXIF_TAG_FOCAL_LENGTH_IN_35MM_FILM    41989
#define EXIF_TAG_SCENE_CAPTURE_TYPE           41990
#define EXIF_TAG_GAIN_CONTROL                 41991
#define EXIF_TAG_CONTRAST                     41992
#define EXIF_TAG_SATURATION                   41993
#define EXIF_TAG_SHARPNESS                    41994
#define EXIF_TAG_SUBJECT_DISTANCE_RANGE       41996
#define EXIF_TAG_OFFSET_SCHEMA                59933

void
exif_tags_array_init(struct exif_tag **exif_tags_ptr);

char
*exif_tag_name_r(uint16_t tag, struct exif_tag *exif_tags);

char
*exif_tag_name(uint16_t tag);

#endif /* EXIF_TAGS_H */

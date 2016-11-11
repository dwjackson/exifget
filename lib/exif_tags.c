#include "exif_tags.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
exif_tag_init(struct exif_tag *tags, uint16_t id, const char *name)
{
    struct exif_tag *tag;

    tag = &(tags[id]);
    tag->id = id;
    if (strlen(name) > EXIF_TAG_NAME_BUFSIZE) {
        fprintf(stderr, "EXIF tag name is too long: %s\n", name);
        abort();
    }
    strcpy(tag->name, name);
}

void
exif_tags_array_init(struct exif_tag **exif_tags_ptr)
{
    size_t size;

    size = NUM_EXIF_TAGS * sizeof(struct exif_tag);
    *exif_tags_ptr = malloc(size);
    if (*exif_tags_ptr == NULL) {
        fprintf(stderr, "ERROR: Could not allocate exif tags array\n");
        abort();
    }
    memset(*exif_tags_ptr, 0, size);

    exif_tag_init(*exif_tags_ptr, EXIF_TAG_IMAGE_WIDTH, "ImageWidth");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_IMAGE_LENGTH, "ImageLength");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_BITS_PER_SAMPLE, "BitsPerSample");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_COMPRESSION, "Compression");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_PHOTOMETRIC_INTERPRETATION, "PhotometricInterpretation");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_MAKE, "Make");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_MODEL, "Model");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_STRIP_OFFSETS, "StripOffsets");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_ORIENTATION, "Orientation");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SAMPLES_PER_PIXEL, "SamplesPerPixel");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_ROWS_PER_STRIP, "RowsPerStrip");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_STRIP_BYTE_COUNTS, "StripByteCounts");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_X_RESOLUTION, "XResolution");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_Y_RESOLUTION, "YResolution");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_PLANAR_CONFIGURATION, "PlanarConfiguration");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_RESOLUTION_UNIT, "ResolutionUnit");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SOFTWARE, "Software");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SENSING_METHOD, "SensingMethod");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_FILE_SOURCE, "FileSource");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SCENE_TYPE, "SceneType");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_CFA_PATTERN, "CFAPattern");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_DATETIME, "DateTime");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_ARTIST, "Artist");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_COPYRIGHT, "Copyright");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_EXIF_IFD, "ExifIFD");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_JPEG_INTERCHANGE_FORMAT, "JPEGInterchangeFormat");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH, "JPEGInterchangeFormatLength");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_YCBCR_POSITIONING, "YCbCrPositioning");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH, "JPEGInterchangeFormatLength"); exif_tag_init(*exif_tags_ptr, EXIF_TAG_EXPOSURE_TIME, "ExposureTime");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_PHOTOGRAPHIC_SENSITIVITY, "PhotographicSensitivity");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_EXIF_VERSION, "ExifVersion");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_FNUMBER, "FNumber");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_EXPOSURE_PROGRAM, "ExposureProgram");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_DATETIME_ORIGINAL, "DateTimeOriginal");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_DATETIME_DIGITIZED, "DateTimeDigitized");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_COMPONENTS_CONFIGURATION, "ComponentsConfiguration");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_COMPRESSED_BITS_PER_PIXEL, "CompressedBitsPerPixel");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SHUTTER_SPEED, "ShutterSpeed");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_APERTURE, "Aperture");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_EXPOSURE_BIAS, "ExposureBias");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_MAX_APERTURE_VALUE, "MaxApertureValue");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_METERING_MODE, "MeteringMode");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_LIGHT_SOURCE, "LightSource");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_FLASH, "Flash");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_FOCAL_LENGTH, "FocalLength");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_MAKER_NOTE, "MakerNote");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_USER_COMMENT, "UserComment");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SUBSEC_TIME, "SubsecTime");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SUBSEC_TIME_ORIGINAL, "SubsecTimeOriginal");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SUBSEC_TIME_DIGITIZED, "SubsecTimeDigitized");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_FLASHPIX_VERSION, "FlashpixVersion");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_COLOR_SPACE, "ColorSpace");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_PIXEL_X_DIMENSION, "PixelXDimension");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_PIXEL_Y_DIMENSION, "PixelYDimension");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_INTEROPERABILITY_IFD, "InterOperabilityIFD");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_FOCAL_PLANE_X_RESOLUTION, "FocalPlaneXResolution");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_FOCAL_PLANE_Y_RESOLUTION, "FocalPlaneYResolution");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_FOCAL_PLANE_RESOLUTION_UNIT, "FocalPlaneResolutionUnit");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_CUSTOM_RENDERED, "CustomRendered");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_EXPOSURE_MODE, "ExposureMode");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_WHITE_BALANCE, "WhiteBalance");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_DIGITAL_ZOOM_RATIO, "DigitalZoomRatio");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_FOCAL_LENGTH_IN_35MM_FILM, "FocalLengthIn35mmFilm");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SCENE_CAPTURE_TYPE, "SceneCaptureType");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_GAIN_CONTROL, "GainControl");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_CONTRAST, "Contrast");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SATURATION, "Saturation");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SHARPNESS, "Sharpness");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_SUBJECT_DISTANCE_RANGE, "SubjectDistanceRange");
    exif_tag_init(*exif_tags_ptr, EXIF_TAG_OFFSET_SCHEMA, "OffsetSchema");
}

char
*exif_tag_name_r(uint16_t tag, struct exif_tag *exif_tags)
{
    return exif_tags[tag].name;
}

char
*exif_tag_name(uint16_t tag)
{
    static struct exif_tag *exif_tags = NULL;
    if (exif_tags == NULL) {
        exif_tags_array_init(&exif_tags);
    }
    return exif_tag_name_r(tag, exif_tags);
}

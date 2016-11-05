#include "tiff_exif.h"
#include "exif_tags.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
tiff_read_ifd_entries(FILE *fp,
                      struct ifd_entry **ifd_entries_ptr,
                      int tiff_offset)
{
    uint16_t num_entries;
    int i;

    fread(&num_entries, 1, 2, fp);
    *ifd_entries_ptr = malloc(num_entries * sizeof(struct ifd_entry));
    if (*ifd_entries_ptr == NULL) {
        fprintf(stderr, "ERROR: Could not malloc() for ifd entries\n");
        abort();
    }
    for (i = 0; i < num_entries; i++) {
        fread(*ifd_entries_ptr + i, 1, sizeof(struct ifd_entry), fp);
    }
    return (int)num_entries;
}

static void
print_byte(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{

    long offset;
    uint8_t data;

    offset = entry->data_offset;
    fseek(fp, offset + tiff_offset, SEEK_SET);
    fread(&data, 1, 2, fp);
    printf("%hhu\n", data);
}

static void
print_string(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    char *str;
    int retval;

    str = NULL;
    offset = entry->data_offset;
    if (offset > 0) {
        retval = fseek(fp, offset + tiff_offset, SEEK_SET);
        if (retval != 0) {
            abort();
        }
        str = malloc(entry->count);
        fread(str, entry->count, 1, fp);
    }
    if (str != NULL) {
        printf("%s", str);
        free(str);
    }
    printf("\n");
}

static void
print_short(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    uint16_t data;

    offset = entry->data_offset;
    fseek(fp, offset + tiff_offset, SEEK_SET);
    fread(&data, 1, 2, fp);
    printf("%hu\n", data);
}

static void
print_long(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    uint32_t data;

    offset = entry->data_offset;
    fseek(fp, offset + tiff_offset, SEEK_SET);
    fread(&data, 1, 4, fp);
    printf("%u\n", data);
}

static void
print_rational(FILE *fp, const struct ifd_entry *entry, int tiff_offset)
{
    long offset;
    uint32_t numerator;
    uint32_t denominator;

    offset = entry->data_offset;
    fseek(fp, offset + tiff_offset, SEEK_SET);
    fread(&numerator, 1, 4, fp);
    fread(&denominator, 1, 4, fp);
    printf("%u/%u\n", numerator, denominator);
}

void
print_ifd_entry(const struct ifd_entry *entry, FILE *fp, int tiff_offset)
{
    long curr_offset;
    const char *tag_name;

    tag_name = exif_tag_name(entry->tag);
    if (tag_name != NULL && strlen(tag_name) > 0) {
        printf("%s ", tag_name);
    } else {
        printf("%hu ", entry->tag);
    }

    curr_offset = ftell(fp);
    switch (entry->type) {
    case 1: /* BYTE */
        print_byte(fp, entry, tiff_offset);
        break;
    case 2: /* ASCII */
        print_string(fp, entry, tiff_offset);
        break;
    case 3: /* SHORT */
        print_short(fp, entry, tiff_offset);
        break;
    case 4: /* LONG */
        print_long(fp, entry, tiff_offset);
        break;
    case 5: /* RATIONAL */
        print_rational(fp, entry, tiff_offset);
        break;
    default:
        printf("Unrecognized data type = %d\n", entry->type);
        break;
    }
    fseek(fp, curr_offset, SEEK_SET);
}

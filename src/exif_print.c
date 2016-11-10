#include "libexifget.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    
void
print_ifd_entry(const exifget_data_t *data, const struct ifd_entry *entry)
{
    const char *tag_name;
    int i;

    tag_name = exifget_tag_name(data, entry);
    if (tag_name != NULL && strlen(tag_name) > 0) {
        printf("%s: ", tag_name);
    } else {
        printf("%d: ", entry->tag);
    }

    switch(entry->type) {
    case EXIFGET_IFD_ENTRY_DATA_TYPE_BYTE:
        for (i = 0; i < entry->count; i++) {
            printf("0x%x", entry->value.value_byte);
            if (i + 1 < entry->count - 1) {
                printf(",");
            }
        }
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_ASCII:
        printf("%s", entry->value.value_ascii);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SHORT:
        printf("%hu", entry->value.value_short);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_LONG:
        printf("%u", entry->value.value_long);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_RATIONAL:
        printf("%u/%u",
               entry->value.value_rational.numerator,
               entry->value.value_rational.denominator);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SBYTE:
        printf("%hhd", entry->value.value_sbyte);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_UNDEFINED:
        printf("0x%X", entry->value.value_byte);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SSHORT:
        printf("%hd", entry->value.value_sshort);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SLONG:
        printf("%d", entry->value.value_slong);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_SRATIONAL:
        printf("%d/%d",
               entry->value.value_srational.numerator,
               entry->value.value_srational.denominator);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_FLOAT:
        printf("%f", entry->value.value_float);
        break;
    case EXIFGET_IFD_ENTRY_DATA_TYPE_DOUBLE:
        printf("%lf", entry->value.value_double);
        break;
    default:
        break;
    }
    printf("\n");
}

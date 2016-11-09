#ifndef IFD_ENTRY_VALUE_H
#define IFD_ENTRY_VALUE_H

int
ifd_entry_value_read_byte(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_ascii(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_short(exifget_data_t *data, struct ifd_entry *entry);

#endif /* IFD_ENTRY_VALUE_H */

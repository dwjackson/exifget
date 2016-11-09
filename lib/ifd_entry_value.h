#ifndef IFD_ENTRY_VALUE_H
#define IFD_ENTRY_VALUE_H

int
ifd_entry_value_read_byte(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_ascii(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_short(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_long(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_rational(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_sbyte(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_undefined(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_sshort(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_slong(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_srational(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_float(exifget_data_t *data, struct ifd_entry *entry);

int
ifd_entry_value_load_double(exifget_data_t *data, struct ifd_entry *entry);

#endif /* IFD_ENTRY_VALUE_H */

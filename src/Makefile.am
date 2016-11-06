AM_CFLAGS = -I$(top_srcdir)/include -L$(top_srcdir)/lib

bin_PROGRAMS = exifget 
exifget_SOURCES = main.c exif_tags.c exif_tags.h tiff_exif.c tiff_exif.h
exifget_LDADD = $(top_srcdir)/lib/libexifget.la

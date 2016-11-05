# ExifGet

ExifGet is a tool with which you can read EXIF data from picture files.

## Building

If you downloaded ExifGet from the Git repository, you will need to have the
GNU Autotools installed. To prepare the project for compilation:

```sh
autoreconf -iv
```

Once the `configure` file exists, ExifGet can be built and installed as
follows:

```sh
./configure
make
make install
```

The `make install` should be run as root if you are installing to a directory
that can only be written by root (e.g. `/usr/local`, which is the default
installation prefix).

## Usage

To read all the EXIF data that ExifGet can find in a picture file:

```sh
exifget [picture_file]
```

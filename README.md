# ExifGet

ExifGet is a tool with which you can read EXIF data from picture files.

## Building

ExifGet has few dependencies, but it does depend on having a C compiler that is
compliant with the C99 standard.

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

## Supported File Types

ExifGet has been tested on the following picture file formats:

* JPEG
* Canon CR2

## License

ExifGet is licensed under the
[MIT License](https://opensource.org/licenses/MIT).

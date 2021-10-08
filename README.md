# Tutorial on LED control using `C` with Raspberry pi zero

## Access the `gpio` pins without additional dependencies

Raspberry PI OS exposes a way to export interfaces to the `gpio` pins in `/sys/class/gpio/`. 
This is called the `sysfs` interface. It is deprecated so we'll use the new `libgpiod` library 
instead. Nevertheless you can find some references on how to use it [here](https://www.ics.com/blog/gpio-programming-using-sysfs-interface).

The exact underlying differences remain unexplored by me as of now.

## libgpiod

Some reference say it comes with Linux but this is not the case for the basic image of raspberry pi os. Therefore we need to install it.

### Install with `apt`

After learning all the below I also found out you can simply install it with `apt`: `sudo apt install gpiod`. Well...


### Install from source

Prerequestites

```
sudo apt-get install autoconf autoconf-archive libtool libkmod-dev pkg-config
```

Different from what the README in `libgpiod` says install it with

```
./autogen.sh --enable-tools=yes --host=arm-linux-gnueabi --prefix=/usr/local/ ac_cv_func_malloc_0_nonnull=yes 
make 
make install
```

[Reference](https://www.beyondlogic.org/an-introduction-to-chardev-gpio-and-libgpiod-on-the-raspberry-pi/)


Add the library path to the env variable:

```
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/lib"
```
(add to `.bashrc` for permanent change)


## Usage

To use a pin as output, e.g. to control a led see [led.c](led/led.c).

# termmanip

Termmanip is a library that enables you to manipulate the terminal with ease, and create Text user interfaces.
This project is not complete and a W.I.P so if you find a bug, drop an issue.

## BUILD AND INSTALL INSTRUCTIONS

This has been tested to work on Ubuntu.

To build and install you will need <strong>binutils</strong> and <strong>build-essential</strong>.
If you want to use your own compiler set it in the Makefile.

Run these commands in your shell:

<code>git clone https://github.com/8086ware/termmanip
cd termmanip
make BUILD_TYPE=release
sudo make install BUILD_TYPE=release</code>


By default the build type is debug so we need to set it to release.


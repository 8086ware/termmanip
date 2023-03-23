# termmanip

Termmanip is a library that enables you to manipulate the terminal with ease, and create Text user interfaces.
This project is not complete and a W.I.P so if you find a bug, drop an issue.

## Build and install instructions

This has been tested to work on Ubuntu.

To build and install you will need <strong>binutils</strong> and <strong>build-essential</strong>.
If you want to use your own compiler set it in the Makefile.

### Run these commands in your shell:

<code>$ git clone https://github.com/8086ware/termmanip
</code>
<code>$ cd termmanip
</code>
<code>$ make release
</code>
<code>$ sudo make install
</code>


By default the build type is debug so we need to set it to release.

### Windows Building

To build on windows, you will need MSYS2, it has only been tested to work on that. Run the same commands in the MSYS2 terminal after installing <strong>make</strong> and <strong>mingw-w64-x86_64-toolchain</strong>.

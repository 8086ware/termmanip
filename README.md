# termmanip

Termmanip is a library that enables you to manipulate the terminal with ease, and create Text user interfaces.
This project is not complete and a W.I.P so if you find a bug, drop an issue.

## Build and install instructions

This has been tested to work on Ubuntu.

To build and install you will need <strong>binutils</strong>, <strong>cmake</strong> and <strong>build-essential</strong>.

### Run these commands in your shell:

<code>$ git clone https://github.com/8086ware/termmanip
</code>
<code>$ cd termmanip
</code>
<code>$ mkdir build/
</code>
<code>$ cmake -B build/ -G"(Generator Here)"
</code>
<code>$ cd build/
</code>
<code>$ (Command for generated build files like make, or ninja)
</code>

### Windows Building

To build on windows, you will need MSYS2 or Cygwin, it has only been tested to work on those. Run the same commands in the MSYS2/Cygwin terminal after installing <strong>make</strong>, <strong>mingw-w64-x86_64-cmake/cmake</strong> and <strong>mingw-w64-x86_64-toolchain</strong>for MSYS2 or <strong>gcc-core</strong> for Cygwin.
I recommend Cygwin if you want a POSIX building experience with a POSIX compatibility layer.

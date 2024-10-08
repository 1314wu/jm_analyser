How to build JM
===============

The software uses CMake to create platform-specific build files. 

Build instructions for plain CMake (suggested)
----------------------------------------------

**Note:** A working CMake installation is required for building the software.

CMake generates configuration files for the compiler environment/development environment on each platform. 
The following is a list of examples for Windows (MS Visual Studio), macOS (Xcode) and Linux (make).

Open a command prompt on your system and change into the root directory of this project.

Create a build directory in the root directory:
```bash
mkdir build 
```

Use one of the following CMake commands, based on your platform. Feel free to change the commands to satisfy
your needs.

**Windows Visual Studio 2017/19 64 Bit:**

Use the proper generator string for generating Visual Studio files, e.g. for VS 2019:

```bash
cd build
cmake .. -G "Visual Studio 16 2019"
```

Then open the generated solution file in MS Visual Studio.

For VS 2017 use "Visual Studio 15 2017 Win64".

Visual Studio 2019 also allows you to open the CMake directory directly. Choose "File->Open->CMake" for this option.

**macOS Xcode:**

For generating an Xcode workspace type:
```bash
cd build
cmake .. -G "Xcode"
```
Then open the generated work space in Xcode.

For generating Makefiles with optional non-default compilers, use the following commands:

```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc-11 -DCMAKE_CXX_COMPILER=g++-11
```
In this example the brew installed GCC 9 is used for a release build.

**Linux**

For generating Linux Release Makefile:
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
```
For generating Linux Debug Makefile:
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

Then type
```bash
make -j
```

For more details, refer to the CMake documentation: https://cmake.org/cmake/help/latest/

Build instructions for make
---------------------------

**Note:** The build instructions in this section require the make tool and Python to be installed, which are
part of usual Linux and macOS environments. See below for installation instruction for Python and GnuWin32 
on Windows.

Open a command prompt on your system and change into the root directory of this project.

To use the default system compiler simply call:
```bash
make all
```
For MSYS2 and MinGW: Open an MSYS MinGW 64-Bit terminal and change into the root directory of this project.

Call:
```bash
make all toolset=gcc
```


Tool Installation on Windows
----------------------------
Download CMake: http://www.cmake.org/ and install it.

Python and GnuWin32 are not mandatory, but they simplify the build process for the user.

python:    https://www.python.org/downloads/release/python-371/

gnuwin32:  https://sourceforge.net/projects/getgnuwin32/files/getgnuwin32/0.6.30/GetGnuWin32-0.6.3.exe/download

To use MinGW, install MSYS2: http://repo.msys2.org/distrib/msys2-x86_64-latest.exe

Installation instructions: https://www.msys2.org/

Install the needed toolchains:
```bash
pacman -S --needed base-devel mingw-w64-i686-toolchain mingw-w64-x86_64-toolchain git subversion mingw-w64-i686-cmake mingw-w64-x86_64-cmake
```

analyse  the bits distribution of h264 bitstream 
===============
````
support format yuv420 only now
````
usage 
-----
```
1. build ldeode.exe with visual studio
2. run params like blow:
  ldecod.exe -p InputFile="C:\work\testseq\foreman_cif_352x288.h264" -p OutputFile="C:\work\testseq\foreman_cif_352x288_dec.yuv"
3. it will generate a csv file "h264_stream_analysis.csv" under current execute directory, which contians bits distribution of input bitstream
 the csv file info contain:
 "poc, totalmbs, frame_len, coeff_len, coeff_percent, intra_nums, intra_len, intra_percent"
4. if you want to show more info about bitstream , please turn "TRACE" flag in defines.h to "1" or "2"
```


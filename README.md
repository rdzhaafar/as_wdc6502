# Description:
`as_wdc6502` is a portable assembler for the WDC65c02 microprocessor with support
for the full ISA, relocations, and other features.

# Why?

Mostly for fun.

# Installing:

No binary destribution is provided at this point, you'll need to build from
source.

Special care was taken to make the code as portable and easy to compile as
possible. All of code is written in C99 with `-pedantic-errors` turned on. On
macOS and Linux the assembler can be compiled by simply cloning this repository
and running `make`. Note, that on macOS you will need `clang`, which can be
installed by running `xcode-select --install`. On Windows, source files can be 
imported into an empty Visual Studio C/C++ project and compiled that way.

# Documentation:

Usage:
```
usage: as_wdc6502 [options] SOURCE...
options:
 -h --help          print this help and exit
 -o --output OUT    write output to OUT
```
For more information about the syntax/directives, read [the main documentation](./doc/README.md)

# License:

[GPLv2](./LICENSE)
# basenumconvert

# Amiga Base Conversion Utilities

## Overview

This repository contains a set of command-line utilities for the Amiga Operating System, designed to perform base conversions between different numeral systems. The utilities support conversions for Base 62, Base 36, Base 16 (Hexadecimal), Base 7, and Base 2 (Binary).

## Installation

To install these utilities on your Amiga system:

1. Clone the repository or download the source files.
2. Compile each source file using SAS/C or a compatible C compiler for AmigaOS.
3. Place the compiled binaries in a directory that is in your system's command path, such as `C: `.

## Usage

Each utility can be invoked from the Amiga Shell. The following commands are supported:

### Base62
Base62 is a case sensitive variant of base 36 where instead of 0-9 and A-Z with the letters
being the same as a-z (as in base 36), in base 62 case sensitivity is a thing.

`base62 from62 <Base62String>` - Converts a Base 62 string to its decimal equivalent.
`base62 number <DecimalNumber>` - Converts a decimal number to its Base 62 string representation.

### Base36
Similar to hexadecimal with the exception that instead of stopping at F (15), the letters go
all the way to Z (36).

`base36 from36 <Base36String>` - Converts a Base 36 string to its decimal equivalent.
`base36 number <DecimalNumber>` - Converts a decimal number to its Base 36 string representation.

### Base16

`base16 from16 <HexadecimalString>` - Converts a hexadecimal string to its decimal equivalent.
`base16 number <DecimalNumber>` - Converts a decimal number to its hexadecimal string representation.

### Base7

`base7 from7 <Base7String>` - Converts a Base 7 string to its decimal equivalent.
`base7 number <DecimalNumber>` - Converts a decimal number to its Base 7 string representation.

### Base2

`base2 from2 <BinaryString>` - Converts a binary string to its decimal equivalent.
`base2 number <DecimalNumber>` - Converts a decimal number to its binary string representation.

## Files

- `base62.c`, `base36.c`, `base16.c`, `base7.c`, `base2.c`:
  Source files for each base conversion utility.

- `strnumconvert.h`, `strnumconvert.c`:
  Header and implementation for the string-to-number and number-to-string conversion functions.

- `strnumconvert_test.c`:
  Test suite for the conversion functions.

## Testing

To run the test suite, compile `strnumconvert_test.c` and execute the binary. Ensure all tests pass to verify the correct functionality of the conversion functions.

# Contributing
Contributions to this repository are welcome. Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Implement your changes.
4. Submit a pull request with a clear description of your changes.

# License
This project is released under the MIT License. Please see the LICENSE file for more details.

# Contact
For any queries or issues, please open an issue on the GitHub repository.
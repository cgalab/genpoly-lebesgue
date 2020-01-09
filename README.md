The code `make_lebesgue` generates instances of (closed) Lebesgue curves. All
vertices have integer coordinates.

# Compilation:

Any standard C compiler will do. E.g.: 

    gcc -O2 -Wall -o make_lebesgue make_lebesgue.c

# Usage

    make_lebesgue --number <N> --output <OUTPUTFILE>

where N is a positive integer and OUTPUTFILE is the name of the output file.

# Generating polygonal data

The runtime-option "--number N" specifies the order of the Lebesgue curve.
The curve is written to the file named XYZ, as specified in "--output XYZ".

Please direct bug reports or suggestions to Martin Held at held@cs.sbg.ac.at.

# License

This is free software.  You may redistribute it and/or modify
it under the terms of the GNU General Public License (v3).

# NAME
`cipher` - A program for reading files, shifting text, and printing files with included line numbers.

# SYNOPSIS
`cipher` \[-n\] \[-s num\] \[-r num\] file.txt

# DESCRIPTION
`cipher` is a simple command-line utility for reading the contents of a file, optionally shifting the text using a Caesar cipher or reverse shifting, and printing line numbers. The program can either modify the file in place or just display the contents with line numbers.

## OPTIONS

**-n**
: Prints line numbers along with the content of the file without modifying the file.

**-s num**
: Shifts alphabetic characters forward by `num` positions using a Caesar cipher. The shift is only applied to alphabetic characters and wraps around at the end of the alphabet.

**-r num**
: Reverse shifts alphabetic characters by `num` positions using a reverse Caesar cipher. This also wraps around at the end of the alphabet.

**file.txt**
: The input file to read, process, and optionally modify.

## OVERVIEW

- **Line Numbers**: When using the `-n` option, the program will print each line from the file prefixed with a line number. No changes will be written to the file in this case.

- **Shifting Text**: The `-s` option applies a forward Caesar cipher to all alphabetic characters, shifting them by the specified number of positions. This modifies the file in place.

- **Reverse Shifting Text**: The `-r` option applies a reverse Caesar cipher to all alphabetic characters, shifting them backward by the specified number of positions. This also modifies the file in place.

- **Modifying Files**: The file is only modified if the `-s` or `-r` options are used. If only the `-n` option is used, the program outputs the content with line numbers but does not modify the file.

## EXAMPLES

1. **Print File with Line Numbers**:
   ```bash
   ./cipher -n file.txt
2. **Shift Characters by 3 Positions**:
   ```bash
   ./cipher -s 3 file.txt
3. **Reverse Shift Characters by 2 Positions**:
   ```bash
   ./cipher -r 2 file.txt
## Author
Written by Marvin Mays.
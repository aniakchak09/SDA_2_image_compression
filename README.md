# Image Compression and Decompression Project

This project is a C-based application that performs image compression and decompression using a custom algorithm. The application reads an image file, compresses it into a smaller size, and can also decompress the compressed image back to its original form.

## Features

1. **Image Compression**: The application reads an image file and compresses it into a smaller size using a custom algorithm. The compressed image is then saved to a file.

2. **Image Decompression**: The application can also decompress a previously compressed image back to its original form.

3. **Image Statistics**: The application can calculate and display various statistics about the image such as the number of levels, the number of nodes containing RGB data, and the side length of the largest block of a single color.

## Usage

The application is run from the command line with the following syntax: 
"./quadtree [-c1 factor | -c2 factor | -d] [input_file] [output_file]" where:
- `-c1 factor` indicates that the program will solve requirement 1 (factor = the threshold imposed for the compression tree).
- `-c2 factor` indicates that the program will solve requirement 2 (factor = the threshold imposed for the compression tree).
- `-d` indicates that the program will solve requirement 3.
- `file_input` represents the name of the first input file (which contains the image).
- `file_output` represents the name of the output file, in which the result of the program execution will be written, depending on the received command.

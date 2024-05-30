# TemaAd Algorithm

## Overview

This project demonstrates an algorithm to partition a shelf of books among three employees such that the workload is balanced. The goal is to minimize the difference between the maximum and minimum loads assigned to the employees.

## Files

- `main.c`: Contains the main function and it takes user input for the amount of books and pages for each book, which runs the algorithm on the respective dataset and returns the results.
- `README.md`: Provides instructions for compiling and running the code.
- `TESTDATASET.c`: Contains the main function (needs to be compiled separately to `main.c`), which automatically creates a dataset of 10 books, with a random number of pages between $10^3$ and $10^8$ ; also prints the execution time of the algorithm.

## Compilation Instructions

To compile the code, you need a C compiler such as `gcc`. Follow these steps:

1. Open a terminal.
2. Navigate to the directory containing the source code files.
3. Run the following command to compile the code:
`gcc main.c -o TemaAd.exe`

This will generate an executable file named `TemaAd.exe`.

## Running the Program

After compiling the code, run the executable with the following command:
`TemaAd.exe`

This program will take user input for the amount of books and number of pages for each book to create a dataset, then it will run the algorithm on the respective dataset and will return the results for it.

## Code Quality

The code is well-organized into modules with clear interfaces. It follows good practices such as:
- Proper indentation and naming conventions.
- Comprehensive comments to explain the code.
- Clear separation of functionality into different files.

## Contact

For any questions or suggestions, please contact the author.

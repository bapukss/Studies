# Concordance

## Project Structure
```
repository/
├── DynamicArray.h  # Header file for the dynamic array implementation 
├── DynamicArray.c  # Source file for the dynamic array implementation
├── Skorowidz.h     # Header file for the concordance implementation
├── Skorowidz.c     # Source file for the concordance implementation
├── main.c          # Main program
├── Makefile        # Build instructions
└── README.md       # Project documentation
```

## Building the Project
This project includes a `Makefile` for building and running the program.

Build the program using `make`:
   ```bash
   make
   ```
   This will compile the source files and generate an executable named `prog`.

Clean the build (remove executable files) using `make clean`:
   ```bash
   make clean
   ```

## Usage
To execute the program manually, run:
```bash
./prog
```
- **Input:** Provide a text file and words to search for.
- **Output:** The program will find all occurrences of the given words and display a list of their positions.

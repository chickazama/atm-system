# ATM Management System

ATM Management System repo, in C, adapted by Matthew Hope.

## Design

### Header Files

The variables, structs and function prototypes for use throughout the project
are defined in a number of header files, each with a different responsibility.

- "atm.h" - defines the core structs, 'user' and 'record'.
- "auth.h" - defines functions responsible for authentication and authorisation.
- "input.h" - defines functions responsible for retrieving user input and converting
the information into program structures.
- "data.h" - defines functions responsible for read/write operations between program
structures and database files.
- "system.h" - defines the system functions through which the program runs


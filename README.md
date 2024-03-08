# ATM Management System

ATM Management System repo, in C, by Matthew Hope.

## How-To Build & Run

N.B. Don't use Windows (obviously). The 'gcc' compiler and 'make' utility must be installed on your machine.
Instructions for setup of these tools may be found online.

This project has a dependency on the C sqlite3 API, but due to file size constraints on Gitea,
the dependency must be manually installed prior to attempting to build the program.

To install the necessary SQLite header and source files:

1. Download the 'sqlite-amalgamation-3420000.zip' file from https://www.sqlite.org/download.html
2. Extract the contents (shell.c, sqlite3.c, sqlite3.h and sqlite3ext.h) into the folder 'src/include'

To build and run the program:

1. Open a terminal from within the project root directory
2. Execute the command 'make'
3. Execute the command 'bin/atm'

## Source and Header Files

The variables, structs and function prototypes for use throughout the project
are defined in a number of header files (.h), each with a different responsibility. The
function implementations are defined in corresponding source files (.c).

- "atm.h" - defines the core structs, 'user' and 'record'.
- "auth.h" - defines functions responsible for authentication and authorisation.
- "data.h" - defines functions responsible for read/write operations between program
structures and database files.
- "input.h" - defines functions responsible for retrieving user input and converting
the information into program structures.
- "print.h" - defines functions responsible for printing menus & their options
- "system.h" - defines the system functions through which the program runs

## SQLite Databases

This project makes use of two SQLite databases, to store Identity information
and Account Records. The SQLite databases are authoritative, and their contents
are written to relevant .txt files as required for audit.

## Password Encryption

Passwords are encrpyted with a basic aphine cipher. This encryption algorithm is sufficient
for the audit, but should definitely NOT be used in any production implementation, as it is
incredibly insecure and trivial to crack.



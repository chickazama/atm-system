# ATM Management System

ATM Management System repo, in C, by Matthew Hope.

## Project Outline

This project is a simple simulation of an ATM Bank Account Management system. Users have the ability to:

- Register a new user account.
- Login to an existing user account.
- Create a bank account of various types (current, savings, fixed01, fixed02, fixed03)
- Deposit and withdraw funds from their bank accounts.
- Transfer funds to other accounts.
- Transfer ownership of their accounts to another user.
- Close existing bank accounts.
- Update details associated with a bank account (phone number, country, etc.)

Since this is not a real-world application, the details a user may change may not be 'allowed' in production. For example,
a user may change his/her country to an arbitrary string. To demonstrate interest rates, the user may decide on the creation date for
the account and their initial deposit. Of course, the money is also (sadly) not real. This project is for demonstration purposes of the C
programming language and software architecture ONLY.

## How-To Build & Run

N.B. This program is designed to run on Linux machines. The 'gcc' compiler and 'make' utility must be installed on your machine.
Instructions for setup of these tools may be found online.

Update! - For ease of building and running the program, I have included the SQLite3 dependencies in the upstream repository. Previously,
I had it ignored from the Git repo, and I included instructions on how to install relevant SQLite3 files and configure the databases, but
for simplicity's sake, all of the relevant files and folders now may be cloned directly. 

1. Change into the 'atm-system' project directory.
2. Run 'make' to build the program.
3. Run 'bin/atm' to run the program.


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

Passwords are encrypted with a basic aphine cipher. This encryption algorithm is sufficient
for the audit, but should definitely NOT be used in any production implementation, as it is
incredibly insecure and trivial to crack.

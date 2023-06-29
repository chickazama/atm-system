#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atm.h"
#include "input.h"

#define BUF_LEN 20
#define MENU_SELECTION_LEN 2

const char* err_msg = "Invalid menu selection. Press enter to try again. ";

// Takes a parameter of type 'int' corresponding to the number of options.
// Returns an 'int' which represents the number of the menu option selected.
// Returns -1 upon error.
int input_menu_selection(int option_count)
{
    // Print prompt
    printf("\nEnter menu selection: ");
    // Get input from stdin
    char buf[BUF_LEN];
    if ( fgets(buf, BUF_LEN, stdin) == NULL )
    {
        // Print out error message
        perror("fgets");
        return -1;
    }

    if (strlen(buf) != MENU_SELECTION_LEN)
    {
        printf("\n%s", err_msg);
        while (getchar() != '\n') ;
        return -1;
    }
    int selection = atoi(buf);
    if (selection <= 0 || selection > option_count)
    {
        printf("\n%s", err_msg);
        while (getchar() != '\n') ;
        return -1;
    }
}

// Takes a pointer to to a user struct as parameter. Prompts the
// user to enter their username and password.
// Returns 0 upon success.
// Returns -1 upon an fgets error (prints out error message).
int input_user(struct user* u)
{
    printf("\nPlease note: Username and Password must contain between 5-18 characters.");
    printf("\nValid characters: a-z, A-Z, _ (underscore)\n");
    // Define buffer, prompt user for input
    char buf[BUF_LEN];
    printf("\nUsername: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL )
    {
	    // perror("fgets");
	    return -1;
    }
    if (buf[strlen(buf)-1] != '\n')
    {
        while (getchar() != '\n') ;
        printf("\nUsername has a maximum of 18 characters in length.\n");
        return -1; 
    }
    buf[strlen(buf)-1] = '\0';
    strncpy(u->username, buf, strlen(buf));
    memset(buf, 0, strlen(buf));
    printf("\nPassword: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL )
    {
	    // perror("fgets");
	    return -1;
    }
    if (buf[strlen(buf)-1] != '\n')
    {
        while (getchar() != '\n') ;
        printf("\nPassword has a maximum of 18 characters in length.\n");
        return -1; 

    }
    buf[strlen(buf)-1] = '\0';
    strncpy(u->password, buf, strlen(buf));
    return 0;
}

// Takes two parameters, a pointer to the user struct, and a pointer to a record struct.
// Prompts the user to enter all account details for new account creation.
// The function short-circuits and returns an error status code upon incorrect input
// or an 'fgets' error.
// Returns 0 upon success.
// Returns -1 upon error.
int input_create_account(struct user* u, struct record* r)
{
    system("clear");
    printf("=== 01Founders ATM System ===\n");
    strncpy(r->owner, u->username, strlen(u->username));
    char buf[BUF_LEN];
    printf("\nAccount Number: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL )
    {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    int accountNumber = atoi(buf);
    if (accountNumber <= 0) {
        return -1;
    }
    r->accountNumber = accountNumber;
    // clear buffer
    memset(buf, 0, strlen(buf));
    printf("\nCreation Date: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL )
    {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    int creationDate = atoi(buf);
    if (creationDate <= 0)
    {
        return -1;
    }
    r->creationDate = creationDate;
    memset(buf, 0, strlen(buf));
    printf("\nCountry: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL )
    {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    strncpy(r->country, buf, strlen(buf));
    // clear buffer
    memset(buf, 0, strlen(buf));
    printf("\nPhone Number: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL )
    {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    int phoneNumber = atoi(buf);
    if (phoneNumber <= 0)
    {
        return -1;
    }
    r->phoneNumber = phoneNumber;
    // clear buffer
    memset(buf, 0, strlen(buf));
    printf("\nInitial Deposit (£): ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL )
    {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    double balance = atof(buf);
    if (balance <= 0)
    {
        return -1;
    }
    r->balance = (int)(balance*100);
    // clear buffer
    memset(buf, 0, strlen(buf));
    printf("\nAccount Type (current, fixed01, fixed02, fixed03): ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL )
    {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    if ( ! (strcmp(buf, "current") == 0 || strcmp(buf, "fixed01") == 0 || strcmp(buf, "fixed02") == 0 || strcmp(buf, "fixed03") == 0) )
    {
        printf("'%s' is not a valid account type.\n", buf);
        return -1;
    }
    strncpy(r->type, buf, strlen(buf));
    return 0;
}

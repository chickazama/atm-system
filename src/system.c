#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"
#include "auth.h"
#include "data.h"
#include "input.h"
#include "system.h"

const char* TITLE = "=== 01Founders ATM System ===";

// Run Menus
int main_menu(void) {
    int ret;
    do
    {
        system("clear");
        printf("%s\n", TITLE);
        printf("\nWelcome to the 01Founders ATM.\n");
        printf("\n[1] - Register\n");
        printf("\n[2] - Login\n");
        printf("\n[3] - Exit\n");
        ret = input_menu_selection(MAIN_MENU_OPTS);
    } while (ret <= 0);

    switch (ret)
    {
        case 1:
            return REGISTER_MENU;
        case 2:
            return LOGIN_MENU;
        case 3:
            return EXIT_SUCCESS;
    }
    return -1;
}

int profile_menu(struct user* u)
{
    int ret;

    do
    {
        system("clear");
        printf("%s\n", TITLE);
        printf("\n=== Welcome '%s' ===\n", u->username);
        printf("\n[1] - View Accounts\n");
        printf("\n[2] - Open New Account\n");
        printf("\n[3] - Log Out\n");
        ret = input_menu_selection(PROFILE_MENU_OPTS);
    } while (ret <= 0);

    switch (ret)
    {
        case 1:
            return VIEW_ACCOUNTS_MENU;
        case 2:
            return OPEN_NEW_ACCOUNT_MENU;
        case 3:
            logout_user(u);
            printf("\nYou have successfully logged out. Press enter to return to the main menu. ");
            while (getchar() != '\n') ;
            return MAIN_MENU;
    }

    return -1;
}

int view_accounts_menu(struct user* u, struct record* r)
{
    system("clear");
    printf("%s\n", TITLE);
    printf("\n=== Accounts - '%s' ===\n", u->username);
    if (get_user_records(u) != 0)
    {
        printf("error with getting records. Press enter to return to profile. ");
        while (getchar() != '\n') ;
        return PROFILE_MENU;
    }
    printf("\nPlease enter the number of the account you wish to view: ");
    char buf[20];
    if (fgets(buf, 20, stdin) == NULL)
    {
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    int acct_no = atoi(buf);
    if (acct_no <= 0)
    {
        printf("Invalid account number. Press enter to return to profile. ");
        while (getchar() != '\n');
        return PROFILE_MENU;
    }
    r->accountNumber = acct_no;
    if (get_record(r) != 0)
    {
        printf("Problem retrieving account");
        return -1;
    }
    if (r->ownerId != u->id)
    {
        printf("Not authorized.\n");
        return -1;
    }
    return ACCOUNT_MENU;
}

int account_menu(struct user* u, struct record* r)
{
    int ret;
    do {
        system("clear");
        printf("%s\n", TITLE);
        printf("\n=== Account #%d ===\n", r->accountNumber);
        printf("Balance: £%.2f\n", (double)(r->balance)/100);
        printf("Country: %s\n", r->country);
        printf("\n[1] - Withdraw\n");
        printf("\n[2] - Deposit\n");
        printf("\n[3] - Transfer Ownership\n");
        printf("\n[4] - Close Account\n");
        printf("\n[5] - Return to 'View Accounts'\n");
        printf("\n[6] - Return To Profile\n");
        ret = input_menu_selection(ACCOUNT_MENU_OPTS);
    } while (ret <= 0) ;

    switch (ret)
    {
        case 1:
            return WITHDRAW;
        case 2:
            return DEPOSIT;
        case 3:
            return TRANSFER_OWNERSHIP;
        case 5:
            return VIEW_ACCOUNTS_MENU;
        case 6:
            return PROFILE_MENU;
        default:
            printf("Account menu option not implemented\n");
            break;
    }
    return -1;
}

// User registration/login
int register_user(struct user* u)
{
    system("clear");
    printf("%s\n", TITLE);
    printf("\n=== Register ===\n");

    if ( input_user(u) == -1 )
    {
        printf("\nSorry, there was a problem with the registration. Press enter to return to main menu. ");
        logout_user(u);
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }

    if ( get_user(u) )
    {
        printf("\nA user with the name '%s' already exists. Press enter to return to main menu. ", u->username);
        logout_user(u);
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }

    // Validate username and password here
    if (validate_user(u) != 0)
    {
        printf("\nInvalid username or password. Press enter to return to main menu. ");
        logout_user(u);
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }
    create_user(u);
    get_user(u);
    // printf("ID: %d\tName: %s\tPassword: %s\n", u->id, u->username, u->password);
    // while (getchar() != '\n') ;
    return PROFILE_MENU;
}

int login_user(struct user* u)
{
    system("clear");
    printf("%s\n", TITLE);
    printf("\n=== Login ===\n");

    if ( input_user(u) == -1 ) 
    {
        printf("\nSorry, there was a problem with logging in. Press enter to return to main menu. ");
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }
    struct user comp;
    memset(comp.username, 0, 20);
    memset(comp.password, 0, 20);
    strncpy(comp.username, u->username, strlen(u->username));
    // Try to get user from file
    if (get_user(&comp) != 1)
    {
        printf("\nThe user '%s' does not exist. Please check spelling, or register a new account.\n", u->username);
        printf("Press enter to return to main menu. ");
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }
    // Check Correct Password
    if ( strcmp(u->password, comp.password) != 0 )
    {
        printf("\nIncorrect password. Press enter to return to main menu. ");
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }
    u->id = comp.id;
    return PROFILE_MENU;
}

void logout_user(struct user* u)
{
    u->id = 0;
    memset(u->username, 0, strlen(u->username));
    memset(u->password, 0, strlen(u->password));
}

// Data Access Wrapper
int create_account(struct user* u, struct record* r)
{
    if ( input_create_account(u, r) == -1 )
    {
        printf("Input problem. Press enter to return to your profile. ");
        while (getchar() != '\n') ;
        return PROFILE_MENU;
    }
    // Write account to file
    if (create_record(u, r) != 0)
    {
        printf("Problem creating account. Press enter to return to your profile. ");
        while (getchar() != '\n') ;
        return PROFILE_MENU;
    }
    printf("Account created successfully. Press enter to return to your profile. ");
    while (getchar() != '\n') ;
    return PROFILE_MENU;
}

int withdraw(struct user* u, struct record* r)
{
    system("clear");
    printf("%s\n", TITLE);
    printf("\n=== %s ===\n", u->username);
    printf("\n=== Account #%d ===\n", r->accountNumber);
    printf("Balance: £%.2f\n", (double)(r->balance)/100);
    printf("\nPlease enter the amount you wish to withdraw (£): ");
    char buf[20];
    if ( fgets(buf, 20, stdin) == NULL)
    {
        perror("fgets");
        return -1;
    }
    double amount = atof(buf);
    if (amount <= 0)
    {
        printf("invalid amount.\n");
        return -1;
    }
    if (amount > r->balance)
    {
        printf("too much.\n");
        return -1;
    }
    double balance = (double)r->balance;
    double nBp = balance/100 - amount;
    int nB = (int)(nBp*100);   
    r->balance = nB;
    if (update_balance(r) != 0)
    {
        printf("problem updating balance\n");
        return -1;
    }
    int ret;
    do {
        system("clear");
        printf("\nYou have withdrawn £%.2f from Account #%d.\nAccount Balance: £%.2f\n", amount, r->accountNumber, (double)(r->balance)/100);
        printf("\n[1] - Return to Account #%d Menu\n", r->accountNumber);
        printf("\n[2] - Return to 'View Accounts'\n");
        printf("\n[3] - Return to your profile\n");
        ret = input_menu_selection(WITHDRAW_COMPLETE_OPTS);
    } while (ret <= 0);
    switch (ret)
    {
        case 1:
            return ACCOUNT_MENU;
        case 2:
            return VIEW_ACCOUNTS_MENU;
        case 3:
            return PROFILE_MENU;
        default:
            printf("Invalid\n");
            break;
    }
    return -1;
}

int deposit(struct user* u, struct record* r)
{
    system("clear");
    printf("%s\n", TITLE);
    printf("\n=== %s ===\n", u->username);
    printf("\n=== Account #%d ===\n", r->accountNumber);
    printf("Balance: £%.2f\n", (double)(r->balance)/100);
    printf("\nPlease enter the amount you wish to deposit (£): ");
    char buf[20];
    if ( fgets(buf, 20, stdin) == NULL)
    {
        perror("fgets");
        return -1;
    }
    double amount = atof(buf);
    if (amount <= 0)
    {
        printf("invalid amount.\n");
        return -1;
    }
    double balance = (double)r->balance;
    double nBp = balance/100 + amount;
    int nB = (int)(nBp*100);
    r->balance = nB;
    if (update_balance(r) != 0)
    {
        printf("problem updating balance\n");
        return -1;
    }
    int ret;
    do {
        system("clear");
        printf("\nYou have deposited £%.2f into Account #%d.\nAccount Balance: £%.2f\n", amount, r->accountNumber, (double)(r->balance)/100);
        printf("\n[1] - Return to Account #%d Menu\n", r->accountNumber);
        printf("\n[2] - Return to 'View Accounts'\n");
        printf("\n[3] - Return to your profile\n");
        ret = input_menu_selection(WITHDRAW_COMPLETE_OPTS);
    } while (ret <= 0);
    switch (ret)
    {
        case 1:
            return ACCOUNT_MENU;
        case 2:
            return VIEW_ACCOUNTS_MENU;
        case 3:
            return PROFILE_MENU;
        default:
            printf("Invalid\n");
            break;
    }
    return -1;
}

int transfer_ownership(struct user* u, struct record* r)
{
    system("clear");
    printf("%s\n", TITLE);
    printf("\n=== %s ===\n", u->username);
    printf("\n=== Account #%d ===\n", r->accountNumber);
    printf("Balance: £%.2f\n", (double)(r->balance)/100);
    printf("\nPlease enter the name of the user to whom you wish to transfer ownership of this account: ");
    char buf[20];
    if ( fgets(buf, 20, stdin) == NULL)
    {
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    struct user rec;
    rec.id = 0;
    memset(rec.username, 0, 20);
    memset(rec.password, 0, 20);
    strncpy(rec.username, buf, strlen(buf));
    if (!get_user(&rec))
    {
        printf("The user '%s' does not exist. Press enter to go back. ", buf);
        while (getchar() != '\n') ;
        return ACCOUNT_MENU;
    }
    memset(buf, 0, 20);
    printf("\nAre you sure you wish to transfer ownership of this account? (y/n): ");
    if ( fgets(buf, 20, stdin) == NULL)
    {
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    if (strcmp(buf, "y") != 0)
    {
        printf("Transfer cancelled. Press enter to return to Account #%d. ", r->accountNumber);
        while (getchar() != '\n') ;
        return ACCOUNT_MENU;
    }
    if (update_owner(&rec, r) != 0)
    {
        printf("error transferring ownership\n");
        return -1;
    }
    printf("\nOwnership of Account #%d transferred from '%s' to '%s.\n", r->accountNumber, u->username, rec.username);
    printf("\nPress enter to return to your profile. ");
    while (getchar() != '\n') ;
    return PROFILE_MENU;
}
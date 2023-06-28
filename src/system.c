#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"
#include "auth.h"
#include "input.h"
#include "system.h"

const char* TITLE = "=== 01Founders ATM System ===";

// Run Menus
int main_menu(void) {
    int ret;
    do {
        system("clear");
        printf("%s\n", TITLE);
        printf("\nWelcome to the 01Founders ATM.\n");
        printf("\n[1] - Register\n");
        printf("\n[2] - Login\n");
        printf("\n[3] - Exit\n");
        ret = input_menu_selection(MAIN_MENU_OPTS);
    } while (ret <= 0);
    switch (ret) {
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

    do {
        system("clear");
        printf("%s\n", TITLE);
        printf("\n=== Welcome '%s' ===\n", u->username);
        printf("\n[1] - View Accounts\n");
        printf("\n[2] - Open New Account\n");
        printf("\n[3] - Log Out\n");
        ret = input_menu_selection(PROFILE_MENU_OPTS);
    } while (ret <= 0);

    switch (ret) {
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

int view_accounts_menu(struct user* u)
{
    // system("clear");
    // print_view_accounts_menu(u);
    // return input_menu_selection(PROFILE_MENU_OPTS);
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
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }

    if ( user_exists(u) )
    {
        printf("\nA user with the name '%s' already exists. Press enter to return to main menu. ", u->username);
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }

    // Validate username and password here
    
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
    // Try to get user from file
    if (!user_exists(u))
    {
        printf("\nThe user '%s' does not exist. Please check spelling, or register a new account.\n", u->username);
        printf("Press enter to return to main menu. ");
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }
    // Check Correct Password
    if ( !check_password(u) )
    {
        printf("\nIncorrect password. Press enter to return to main menu. ");
        while (getchar() != '\n') ;
        return MAIN_MENU;
    }

    return PROFILE_MENU;
}

void logout_user(struct user* u)
{
    memset(u->username, 0, 20);
    memset(u->password, 0, 20);
}

// Data Access Wrapper
int create_account(struct user* u, struct record* r)
{
    if ( input_create_account(u, r) == -1 )
        return -1;
    // Write account to file
    return 0;
}



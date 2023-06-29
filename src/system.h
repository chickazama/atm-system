#ifndef SYSTEM_H
#define SYSTEM_H

#include "atm.h"

// Menu Enumeration
#define MAIN_MENU 1
#define REGISTER_MENU 2
#define LOGIN_MENU 3
#define PROFILE_MENU 4
#define VIEW_ACCOUNTS_MENU 5
#define OPEN_NEW_ACCOUNT_MENU 6

// Menu Option Counts
#define MAIN_MENU_OPTS 3
#define PROFILE_MENU_OPTS 3

// Menu functions
int main_menu(void);
int profile_menu(struct user*);
int view_accounts_menu(struct user*);

// User registration/login/logout
int register_user(struct user*);
int login_user(struct user*);
void logout_user(struct user*);

// Data access wrappers
int create_account(struct user*, struct record*);

#endif

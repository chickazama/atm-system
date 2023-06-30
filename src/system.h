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
#define ACCOUNT_MENU 7
#define WITHDRAW 8
#define DEPOSIT 9
#define TRANSFER_OWNERSHIP 10
#define CLOSE_ACCOUNT 11

// Menu Option Counts
#define MAIN_MENU_OPTS 3
#define PROFILE_MENU_OPTS 3
#define ACCOUNT_MENU_OPTS 6
#define WITHDRAW_COMPLETE_OPTS 3

// Menu functions
int main_menu(void);
int profile_menu(struct user*);
int view_accounts_menu(struct user*, struct record*);
int account_menu(struct user*, struct record*);
// User registration/login/logout
int register_user(struct user*);
int login_user(struct user*);
void logout_user(struct user*);

// Data access wrappers
int create_account(struct user*, struct record*);
int withdraw(struct user*, struct record*);
int deposit(struct user*, struct record*);
int transfer_ownership(struct user*, struct record*);
int close_account(struct user*, struct record*);

#endif

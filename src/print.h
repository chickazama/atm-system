#ifndef PRINT_H
#define PRINT_H

#include "atm.h"

void print_main_menu(void);
void print_profile_menu(struct user*);
void print_account_menu(struct record*);
void print_account_details(struct record*);
void print_edit_details(struct record*);

#endif
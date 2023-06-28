#ifndef INPUT_H
#define INPUT_H

#include "atm.h"

int input_menu_selection(int);
int input_user(struct user*);
int input_create_account(struct user*, struct record*);

#endif

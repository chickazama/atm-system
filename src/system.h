#ifndef SYSTEM_H
#define SYSTEM_H

#include "atm.h"

int get_menu_selection(int);
int main_menu(void);
int get_user(struct user*);
int register_menu(struct user*);
int login_menu(struct user*);
int profile_menu(struct user*);
#endif



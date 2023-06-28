#ifndef AUTH_H
#define AUTH_H

#include "atm.h"

int user_exists(struct user*);
int check_password(struct user*);

#endif



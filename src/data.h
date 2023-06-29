#ifndef DATA_H
#define DATA_H

#include "atm.h"
#include "include/sqlite3.h"

int create_users_table(void);
int create_records_table(void);
int get_all_users(void);
int get_user(struct user*);
int create_user(struct user*);

#endif
#ifndef DATA_H
#define DATA_H

#include "atm.h"
#include "include/sqlite3.h"

int create_users_table(void);
int create_records_table(void);
int drop_users_table(void);
int get_all_users(void);
int get_user(struct user*);
int create_user(struct user*);
int delete_user(struct user*);
int create_record(struct user*, struct record*);
int get_user_records(struct user*);
int get_record(struct record*);
int update_balance(struct record*);
int update_owner(struct user*, struct record*);
int delete_account(struct record*);

#endif
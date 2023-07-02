#ifndef DATA_H
#define DATA_H

#include "atm.h"
#include "include/sqlite3.h"

int init_db(void);
int drop_users_table(void);
int get_user(struct user*);
int create_user(struct user*);
int delete_user(struct user*);
int create_record(struct user*, struct record*);
int get_user_records(struct user*);
int get_record(struct record*);
int update_balance(struct record*);
int update_owner(struct user*, struct record*);
int delete_account(struct record*);
int update_phone_number(struct user*, struct record*);
int update_country(struct user*, struct record*);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"
#include "data.h"
#include "system.h"

#define MAIN_MENU 1
#define REGISTER_MENU 2
#define LOGIN_MENU 3
#define PROFILE_MENU 4
#define VIEW_ACCOUNTS_MENU 5
#define OPEN_NEW_ACCOUNT_MENU 6
#define ACCOUNT_MENU 7

int run(int);
void reset_user(struct user*);
void reset_record(struct record*);

struct user u;
struct record r;

int main(int argc, char* argv[])
{
    reset_user(&u);
    reset_record(&r);
    create_users_table();
    create_records_table();
    // drop_users_table();
    // while (getchar() != '\n') ;
    int opt = MAIN_MENU;

    do
    {
        opt = run(opt);
    } while (opt > 0);

    switch (opt)
    {
        case 0:
            printf("\nThank you for using the 01Founders ATM. Goodbye.\n");
        default:
            exit(EXIT_FAILURE);
    }

    return opt;
}

int run(int opt)
{
    switch (opt)
    {
        case MAIN_MENU:
            reset_user(&u);
            return main_menu();
        case REGISTER_MENU:
            return register_user(&u);
        case LOGIN_MENU:
            return login_user(&u);
        case PROFILE_MENU:
            reset_record(&r);
            return profile_menu(&u);
        case VIEW_ACCOUNTS_MENU:
            reset_record(&r);
            return view_accounts_menu(&u, &r);
        case OPEN_NEW_ACCOUNT_MENU:
            reset_record(&r);
            return create_account(&u, &r);
        case ACCOUNT_MENU:
            return account_menu(&u, &r);
        default:
            printf("not implemented.\n");
            break;
    }

    return -1;
}

void reset_user(struct user* u)
{
    u->id = 0;
    memset(u->username, 0, 20);
    memset(u->password, 0, 20);
}

void reset_record(struct record* r)
{
    r->id = 0;
    r->ownerId = 0;
    memset(r->owner, 0, 20);
    r->creationDate = 0;
    r->accountNumber = 0;
    memset(r->country, 0, 20);
    r->phoneNumber = 0;
    r->balance = 0;
    memset(r->type, 0, 20);
}
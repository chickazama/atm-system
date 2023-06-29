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

int run(int opt);

struct user u;
struct record r;

int main(int argc, char* argv[])
{
    create_users_table();
    create_records_table();
    
    int opt = MAIN_MENU;

    do
    {
        opt = run(opt);
    } while (opt > 0);

    switch (opt)
    {
        case 0:
            printf("\nThank you for using ATM. Goodbye.\n");
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
            return main_menu();
        case REGISTER_MENU:
            return register_user(&u);
        case LOGIN_MENU:
            return login_user(&u);
        case PROFILE_MENU:
            return profile_menu(&u);
        // case VIEW_ACCOUNTS_MENU:
        //     return run_view_accounts_menu(&u);
        // case OPEN_NEW_ACCOUNT_MENU:
        //     return run_create_account_menu(&u, &r);
        default:
            printf("not implemented.\n");
            break;
    }

    return -1;
}

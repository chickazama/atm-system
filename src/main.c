#include <stdio.h>
#include <stdlib.h>
#include "atm.h"
#include "menu.h"
#include "system.h"

#define MAIN_MENU 1
#define REGISTER_MENU 2
#define LOGIN_MENU 3
#define PROFILE_MENU 4
#define ACCOUNTS_MENU 5

struct user u;

int run(int opt);
int run_main_menu(void);
int run_register_menu(struct user*);
int run_login_menu(struct user*);
int run_profile_menu(struct user*);

int main(int argc, char* argv[]) {
    int opt = MAIN_MENU;

    do {
        opt = run(opt);
    } while (opt > 0);

    switch (opt) {
        case 0:
            printf("\nThank you for using ATM. Goodbye.\n");
        default:
            exit(EXIT_FAILURE);
    }

    return opt;
}

int run(int opt) {
    switch (opt) {
        case MAIN_MENU:
            return run_main_menu();
        case REGISTER_MENU:
            return run_register_menu(&u);
        case LOGIN_MENU:
            return run_login_menu(&u);
        case PROFILE_MENU:
            return run_profile_menu(&u);
        default:
            printf("not implemented.\n");
    }
    return -1;
}

int run_main_menu(void) {
    int selection;
    do {
	    selection = main_menu();
    } while (selection <= 0);
    switch (selection) {
        case 1:
            return REGISTER_MENU;
        case 2:
            return LOGIN_MENU;
        case 3:
            return EXIT_SUCCESS;
    }
    return -1;
}

int run_register_menu(struct user* u) {
    switch (register_menu(u)) {
        case 0:
            return PROFILE_MENU;
        default:
            printf("\nA user with the name '%s' already exists. Press enter to return to main menu. ", u->username);
            while (getchar() != '\n') ;
            return MAIN_MENU;
    }
}

int run_login_menu(struct user* u) {
    switch (login_menu(u)) {
        case 0:
            return PROFILE_MENU;
        default:
            printf("\nIncorrect username or password. Press enter to return to main menu. ");
            while (getchar() != '\n') ;
            return MAIN_MENU;
    }
}

int run_profile_menu(struct user* u) {
    int selection;
    do {
        selection = profile_menu(u);
    } while (selection <= 0);
    switch (selection) {
        case 1:
            return ACCOUNTS_MENU;
        case 2:
            return MAIN_MENU;
    }
    return -1;
}

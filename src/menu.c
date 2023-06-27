#include <stdio.h>
#include "atm.h"
#include "menu.h"

const char* title = "=== 01Founders ATM System ===";

void print_main_menu(void) {
    printf("%s\n", title);
    printf("\nWelcome to the 01Founders ATM.\n");
    printf("\n[1] - Register\n");
    printf("\n[2] - Login\n");
    printf("\n[3] - Exit\n");
}

void print_profile_menu(struct user* u) {
    printf("%s\n", title);
    printf("\n=== Welcome '%s' ===\n", u->username);
    // printf("\n[1] - Withdraw\n");
    // printf("\n[2] - Deposit\n");
    printf("\n[1] - My Accounts\n");
    printf("\n[2] - Open New Account\n");
    printf("\n[3] - Log Out\n");
}

void print_accounts_menu(struct user* u) {
    printf("%s\n", title);
    printf("\n=== '%s' - Accounts ===\n", u->username);
    // loop through and retrieve
    printf("\n123456789\tcurrent\n");
}

#include <stdio.h>
#include "menu.h"

const char* title = "=== 01Founders ATM System ===";

void main_menu(void) {
    printf("%s\n", title);
    printf("\nWelcome to the 01Founders ATM.\n");
    printf("\n[1] - Register\n");
    printf("\n[2] - Login\n");
    printf("\n[3] - Exit\n");
}

void profile_menu(char* user_name) {
    printf("%s\n", title);
    printf("\nProfile - %s\n", user_name);
    printf("\n[1] - My Accounts\n");
    printf("\n[2] - Log Out\n");
}

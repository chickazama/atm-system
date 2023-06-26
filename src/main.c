#include <stdio.h>
#include <stdlib.h>
#include "atm.h"
#include "system.h"

struct user u;

int main(int argc, char* argv[]) {
    int selection;
    do {
	    selection = main_menu();
    } while (selection <= 0);

    switch (selection) {
        case 1:
            printf("\nLoading register menu...\n");
            break;
        case 2:
            //printf("\nLoading login menu...\n");
            int res = login_menu(&u);
            printf("Username: %s\n", u.username);
            printf("Password: %s\n", u.password);
            printf("%d\n", res);
            break;
        case 3:
            printf("\nThank you for using the ATM. Goodbye!\n");
            break;
        default:
            exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

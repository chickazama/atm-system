#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"
#include "auth.h"
#include "menu.h"
#include "system.h"

#define BUF_LEN 64
#define MAIN_MENU_OPTS 3

const char* err_msg = "Invalid menu selection. Press enter to try again. ";

int main_menu(void) {
    system("clear");
    // Print out Main Menu Display
    print_main_menu();
    // Print prompt
    printf("\n> ");
    // Get input from stdin
    char buf[BUF_LEN];
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
        // Print out error message
        perror("fgets");
        return -1;
    }
    if (strlen(buf) != 2) {
        printf("\n%s", err_msg);
        while (getchar() != '\n') ;
        return -1;
    }
    int selection = atoi(buf);
    if (selection <= 0 || selection > MAIN_MENU_OPTS) {
        printf("\n%s", err_msg);
        while (getchar() != '\n') ;
        return -1;
    }
    return selection;
}

int login_menu(struct user* u) {
    system("clear");
    printf("Username: ");
    char buf[BUF_LEN];
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
	    perror("fgets");
	    return -1;
    }
    buf[strlen(buf)-1] = '\0';
    strcpy(u->username, buf);
    for (int i = 0; i < strlen(buf); i++) {
        buf[i] = '\0';
    }
    printf("Password: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
	    perror("fgets");
	    return -1;
    }
    buf[strlen(buf)-1] = '\0';
    strcpy(u->password, buf);
    if ( user_exists(u) == 1 && check_password(u) == 1)
	    return 0;
    return 1;
}

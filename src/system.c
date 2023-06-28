#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"
#include "auth.h"
#include "menu.h"
#include "system.h"

#define BUF_LEN 64
#define MAIN_MENU_OPTS 3
#define PROFILE_MENU_OPTS 3

const char* err_msg = "Invalid menu selection. Press enter to try again. ";

int get_menu_selection(int opts) {
    // Print prompt
    printf("\nEnter menu selection: ");
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
    if (selection <= 0 || selection > opts) {
        printf("\n%s", err_msg);
        while (getchar() != '\n') ;
        return -1;
    }
}

int main_menu(void) {
    system("clear");
    print_main_menu();
    return get_menu_selection(MAIN_MENU_OPTS);
}

int set_user(struct user* u) {
    char buf[BUF_LEN];
    printf("\nUsername: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
	    perror("fgets");
	    return -1;
    }
    buf[strlen(buf)-1] = '\0';
    strcpy(u->username, buf);
    for (int i = 0; i < strlen(buf); i++) {
        buf[i] = '\0';
    }
    printf("\nPassword: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
	    perror("fgets");
	    return -1;
    }
    buf[strlen(buf)-1] = '\0';
    strcpy(u->password, buf);
    return 0;
}

int register_menu(struct user* u) {
    system("clear");
    printf("=== 01Founders ATM System ===\n");
    printf("\n=== Register ===\n");
    // Check error on this
    set_user(u);

    if ( user_exists(u) != 0 )
	    return -1;
    
    return 0;
}

int login_menu(struct user* u) {
    system("clear");
    printf("=== Login ===\n");
    // Check error on this
    set_user(u);
    if ( user_exists(u) == 1 && check_password(u) == 1)
	    return 0;
    return -1;
}

int profile_menu(struct user* u) {
    system("clear");
    print_profile_menu(u);
    return get_menu_selection(PROFILE_MENU_OPTS);
}

int view_accounts_menu(struct user* u) {
    system("clear");
    print_view_accounts_menu(u);
    return get_menu_selection(PROFILE_MENU_OPTS);
}

int get_account_info(struct user* u, struct record* r) {
    strcpy(r->owner, u->username);
    char buf[BUF_LEN];
    printf("Account Number: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    int accountNumber = atoi(buf);
    if (accountNumber <= 0) {
        return -1;
    }
    r->accountNumber = accountNumber;
    // clear buffer
    for (int i = 0; i < strlen(buf); i++) {
        buf[i] = '\0';
    }
    printf("Country: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    strcpy(r->country, buf);
    // clear buffer
    for (int i = 0; i < strlen(buf); i++) {
        buf[i] = '\0';
    }
    printf("Phone Number: ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    int phoneNumber = atoi(buf);
    if (phoneNumber <= 0) {
        return -1;
    }
    r->phoneNumber = phoneNumber;
    // clear buffer
    for (int i = 0; i < strlen(buf); i++) {
        buf[i] = '\0';
    }
    printf("Initial Deposit (£): ");
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
        // Print out error message
        perror("fgets");
        return -1;
    }
    buf[strlen(buf)-1] = '\0';
    double balance = atof(buf);
    if (balance <= 0) {
        return -1;
    }
    r->balance = balance;
    printf("%s\n%d\n%s\n%d\n%.2f\n", r->owner, r->accountNumber, r->country, r->phoneNumber, r->balance);
    return 0;
}
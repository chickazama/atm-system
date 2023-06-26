#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "system.h"

#define BUF_LEN 64
#define MAIN_MENU_OPTS 3

int run_main_menu(void) {
    // Print out Main Menu Display
    main_menu();
    // Print prompt
    printf("\n> ");
    // Get input from stdin
    char buf[BUF_LEN];
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
	// Print out error message
	perror("fgets");
	return -1;
    }
    if (strlen(buf) != 2)
	return -1;
    int selection = atoi(buf);
    if (selection <= 0 || selection > MAIN_MENU_OPTS)
	return -1;
    return selection;
}

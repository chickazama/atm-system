#include <stdio.h>
#include "menu.h"
#include "system.h"

#define BUF_LEN 64

int run_main_menu(void) {
    main_menu();
    printf("\n> ");
    char buf[BUF_LEN];
    if ( fgets(buf, BUF_LEN, stdin) == NULL ) {
	perror("fgets");
	return -1;
    }
    printf("%s\n", buf);
    return 0;
}

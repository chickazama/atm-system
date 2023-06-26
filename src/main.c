#include <stdio.h>
#include <stdlib.h>
#include "system.h"

int main(int argc, char* argv[]) {
    int selection;
    do {
	selection = run_main_menu();
    } while (selection <= 0);
    switch (selection) {
	case 1:
	printf("\nLoading register menu...\n");
	break;
	case 2:
	printf("\nLoading login menu...\n");
	break;
	case 3:
	printf("\nThank you for using the ATM. Goodbye!\n");
	break;
	default:
	exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

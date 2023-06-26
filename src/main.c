#include <stdio.h>
#include <stdlib.h>
#include "system.h"

int main(int argc, char* argv[]) {
    int selection;
    do {
	selection = run_main_menu();
    } while (selection <= 0);
    return EXIT_SUCCESS;
}

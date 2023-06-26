#include <stdio.h>
#include <string.h>
#include "auth.h"

int username_exists(char* username) {
    printf("Username submitted: %s\n", username);
    if ( strcmp(username, "test") == 0 )
	    return 1;
    return 0;
}



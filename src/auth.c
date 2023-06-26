#include <stdio.h>
#include <string.h>
#include "atm.h"
#include "auth.h"

int user_exists(struct user* u) {
    printf("Username submitted: %s\n", u->username);
    if ( strcmp(u->username, "test") == 0 )
	    return 1;
    return 0;
}



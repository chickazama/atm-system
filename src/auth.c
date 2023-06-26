#include <stdio.h>
#include <string.h>
#include "atm.h"
#include "auth.h"

int user_exists(struct user* u) {
    if ( strcmp(u->username, "test") == 0 )
	    return 1;
    return 0;
}



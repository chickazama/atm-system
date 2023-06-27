#include <stdio.h>
#include <string.h>
#include "atm.h"
#include "auth.h"

int user_exists(struct user* u) {
    if ( strcmp(u->username, "test") == 0 )
	    return -1;
    return 0;
}

int check_password(struct user* u) {
    if ( strcmp(u->password, "password") == 0 )
	    return -1;
    return 0;
}



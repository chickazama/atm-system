#include <stdio.h>
#include <string.h>
#include "atm.h"
#include "auth.h"

int check_password(struct user* u, struct user* comp)
{
    if ( strcmp(u->password, comp->password) == 0 )
	    return 1;
    return 0;
}

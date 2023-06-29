#include <stdio.h>
#include <string.h>
#include "atm.h"
#include "auth.h"

int validate_chars(char*);

int validate_user(struct user* u)
{
    if (validate_chars(u->username) != 0)
        return -1;
    if (validate_chars(u->password) != 0)
        return -1;
    return 0;
}

int validate_chars(char* str)
{
    if (strlen(str) < 5) {
        return -1;
    }
    for (int i = 0; i < strlen(str); i++)
    {
        if ( !( (str[i] >= 30 && str[i] <= 39) || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || str[i] == 95 ) ) 
            return -1;
    }
    return 0;
}

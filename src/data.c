#include <stdio.h>
#include <stdlib.h>
#include "atm.h"
#include "data.h"
#include "include/sqlite3.h"

const char* CREATE_USERS_STMT = "CREATE TABLE IF NOT EXISTS \"users\" (\"id\" INTEGER PRIMARY KEY AUTOINCREMENT, \"username\" nvarchar(20) UNIQUE NOT NULL, \"password\" nvarchar(20) NOT NULL);";

int my_func(void) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("TestDB.db", &db); 
    return create_users_table(db);
}

int create_users_table(sqlite3* db)
{
    char* err;
    int rc = sqlite3_exec(db, CREATE_USERS_STMT, NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        printf("%s\n", err);
        return rc;
    }
    return rc;
}

// int create_records_table(sqlite3* db)
// {
//     char* err_msg;
//     int rc = sqlite3
// }
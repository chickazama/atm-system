#include <stdio.h>
#include <stdlib.h>
#include "atm.h"
#include "data.h"
#include "include/sqlite3.h"

const char* CREATE_USERS_STMT = "CREATE TABLE IF NOT EXISTS \"users\" (\
\"id\" INTEGER PRIMARY KEY AUTOINCREMENT, \
\"username\" NVARCHAR(20) UNIQUE NOT NULL, \
\"password\" NVARCHAR(20) NOT NULL);";

const char* CREATE_RECORDS_STMT = "CREATE TABLE IF NOT EXISTS \"records\" (\
\"id\" INTEGER PRIMARY KEY AUTOINCREMENT, \
\"ownerId\" INTEGER NOT NULL, \
\"username\" NVARCHAR(20) NOT NULL, \
\"accountNumber\" INTEGER UNIQUE NOT NULL, \
\"creationDate\" INTEGER NOT NULL, \
\"country\" NVARCHAR(20) NOT NULL, \
\"phoneNumber\" INTEGER NOT NULL, \
\"balance\" INTEGER NOT NULL, \
\"type\" NVARCHAR(8) NOT NULL);";

sqlite3* identity_db;
sqlite3* records_db;

int create_users_table(void)
{
    sqlite3_open("data/Identity.db", &identity_db);
    char* err_msg;
    int rc = sqlite3_exec(identity_db, CREATE_USERS_STMT, NULL, NULL, &err_msg);
    if (rc != SQLITE_OK)
        printf("%s\n", err_msg);
    return rc;
}

int create_records_table(void)
{
    sqlite3_open("data/Records.db", &records_db);;
    char* err_msg;
    int rc = sqlite3_exec(records_db, CREATE_RECORDS_STMT, NULL, NULL, &err_msg);
    if (rc != SQLITE_OK)
        printf("%s\n", err_msg);
    return rc;
}
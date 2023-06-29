#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"
#include "data.h"
#include "include/sqlite3.h"

const char* CREATE_USERS_STMT = "CREATE TABLE IF NOT EXISTS \"users\" (\
\"id\" INTEGER PRIMARY KEY AUTOINCREMENT, \
\"username\" TEXT UNIQUE NOT NULL, \
\"password\" TEXT NOT NULL);";

const char* CREATE_RECORDS_STMT = "CREATE TABLE IF NOT EXISTS \"records\" (\
\"id\" INTEGER PRIMARY KEY AUTOINCREMENT, \
\"ownerId\" INTEGER NOT NULL, \
\"username\" TEXT NOT NULL, \
\"accountNumber\" INTEGER UNIQUE NOT NULL, \
\"creationDate\" INTEGER NOT NULL, \
\"country\" TEXT NOT NULL, \
\"phoneNumber\" INTEGER NOT NULL, \
\"balance\" INTEGER NOT NULL, \
\"type\" TEXT NOT NULL);";

sqlite3* identity_db;
sqlite3* records_db;

int callback(void *NotUsed, int argc, char **argv, char **azColName);

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

int get_all_users(void)
{
    char* err_msg;
    char* sql = "SELECT * FROM \"users\";";
    int rc = sqlite3_exec(identity_db, sql, callback, NULL, &err_msg);
    if (rc != SQLITE_OK)
        printf("%s\n", err_msg);
    return rc;
}

int get_user(struct user* u)
{
    sqlite3_stmt* stmt;
    char* err_msg;
    char sql[255];
    sprintf(sql, "SELECT * FROM \"users\" WHERE \"username\" = \"%s\";", u->username);
    int rc = sqlite3_prepare_v2(identity_db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("error preparing stmt\n");
        return -1;
    }
    int step = sqlite3_step(stmt);
    int user_set = 0;
    while (step == SQLITE_ROW)
    {
        u->id = sqlite3_column_int(stmt, 0);
        strcpy(u->username, sqlite3_column_text(stmt, 1));
        strcpy(u->password, sqlite3_column_text(stmt, 2));
        user_set = 1;
        step = sqlite3_step(stmt);
    }
    if (step != SQLITE_DONE)
    {
        printf("error stepping through rows\n");
        return -1;
    }
    rc = sqlite3_finalize(stmt);
    if (rc != SQLITE_OK) {
        printf("error finalising\n");
        return -1;
    }
    return user_set;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    
    NotUsed = 0;
    for (int i = 0; i < argc; i++)
    {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    
    return 0;
}
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

int drop_users_table(void)
{
    sqlite3_stmt* stmt;
    char* err_msg;
    char* sql = "DROP TABLE \"users\";";
    int rc = sqlite3_prepare_v2(identity_db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("problem preparing drop: %d\n", rc);
        return rc;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        printf("problem executing delete: %d\n", rc);
        return rc;
    }
    sqlite3_finalize(stmt);
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

int create_user(struct user* u)
{
    sqlite3_stmt* stmt;
    char* err_msg;
    char sql[255];
    sprintf(sql, "INSERT INTO \"users\" VALUES(?, \"%s\", \"%s\");", u->username, u->password);
    int rc = sqlite3_prepare_v2(identity_db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("problem preparing insert: %d\n", rc);
        return rc;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        printf("problem executing insert: %d\n", rc);
        return rc;
    }
    rc = sqlite3_finalize(stmt);
    if (rc != SQLITE_OK) {
        printf("problem finalising stmt: %d\n", rc);
    }
    return rc;
}

int delete_user(struct user* u)
{
    sqlite3_stmt* stmt;
    char* err_msg;
    char sql[255];
    sprintf(sql, "DELETE FROM \"users\" WHERE \"username\" = \"%s\";", u->username);
    int rc = sqlite3_prepare_v2(identity_db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("problem preparing delete: %d\n", rc);
        return rc;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        printf("problem executing delete: %d\n", rc);
        return rc;
    }
    rc = sqlite3_finalize(stmt);
    if (rc != SQLITE_OK) {
        printf("problem finalising stmt: %d\n", rc);
    }
    return rc;
}

int create_record(struct user* u, struct record* r)
{
    sqlite3_stmt* stmt;
    char* err_msg;
    char sql[255];
    sprintf(sql, "INSERT INTO \"records\" VALUES (\
?, \
\"%d\", \
\"%s\", \
\"%d\", \
\"%d\", \
\"%s\", \
\"%d\", \
\"%d\", \
\"%s\");", u->id, u->username, r->accountNumber, r->creationDate, r->country, r->phoneNumber, r->balance, r->type);
    int rc = sqlite3_prepare_v2(records_db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("problem preparing insert: %d\n", rc);
        return rc;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        printf("problem executing insert: %d\n", rc);
        return rc;
    }
    rc = sqlite3_finalize(stmt);
    if (rc != SQLITE_OK) {
        printf("problem finalising stmt: %d\n", rc);
    }
    return rc;
}

int get_user_records(struct user* u)
{
    // int i = 0;
    sqlite3_stmt* stmt;
    char* err_msg;
    char sql[255];
    sprintf(sql, "SELECT * FROM \"records\" WHERE \"ownerId\" = \"%d\";", u->id);
    int rc = sqlite3_prepare_v2(records_db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("error preparing stmt\n");
        return -1;
    }
    int step = sqlite3_step(stmt);
    int user_set = 0;
    while (step == SQLITE_ROW)
    {
        int acct_no = sqlite3_column_int(stmt, 3);
        const char* type = sqlite3_column_text(stmt, 8);
        printf("\nAccount: %d\tType: %s\n", acct_no, type);
        // struct record* r = records[i];
        // r->id = sqlite3_column_int(stmt, 0);
        // r->ownerId = sqlite3_column_int(stmt, 1);
        // strcpy(r->owner, sqlite3_column_text(stmt, 2));
        // r->accountNumber = sqlite3_column_int(stmt, 3);
        // r->creationDate = sqlite3_column_int(stmt, 4);
        // strcpy(r->country, sqlite3_column_text(stmt, 5));
        // r->phoneNumber = sqlite3_column_int(stmt, 6);
        // r->balance = sqlite3_column_int(stmt, 7);
        // strcpy(r->type, sqlite3_column_text(stmt, 8));
        // i++;
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
    return rc;
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
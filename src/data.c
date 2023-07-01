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

int run_single_stmt(sqlite3*, const char*);

int init_db(void)
{
    sqlite3_open("data/Identity.db", &identity_db);
    sqlite3_open("data/Records.db", &records_db);
    if (run_single_stmt(identity_db, CREATE_USERS_STMT) != SQLITE_OK)
        return -1;
    if (run_single_stmt(records_db, CREATE_RECORDS_STMT) != SQLITE_OK)
        return -1;
    return 0;
}

int run_single_stmt(sqlite3* db, const char* queryStr)
{
    sqlite3_stmt* stmt;
    char* err_msg;
    if (sqlite3_exec(db, queryStr, NULL, NULL, &err_msg) != SQLITE_OK)
    {
        printf("%s\n", err_msg);
        return -1;
    }
    return 0;
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
    char sql[255];
    sprintf(sql, "INSERT INTO \"users\" VALUES(?, \"%s\", \"%s\");", u->username, u->password);
    if (run_single_stmt(identity_db, sql) != SQLITE_OK)
        return -1;
    return 0;
}

int delete_user(struct user* u)
{
    sqlite3_stmt* stmt;
    char* err_msg;
    char sql[255];
    sprintf(sql, "DELETE FROM \"users\" WHERE \"username\" = \"%s\";", u->username);
    if (run_single_stmt(identity_db, sql) != SQLITE_OK)
        return -1;
    return 0;
}

int create_record(struct user* u, struct record* r)
{
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
    if (run_single_stmt(records_db, sql) != SQLITE_OK)
        return -1;
    return 0;
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

int get_record(struct record* r)
{
    sqlite3_stmt* stmt;
    char* err_msg;
    char sql[255];
    sprintf(sql, "SELECT * FROM \"records\" WHERE \"accountNumber\" = \"%d\";", r->accountNumber);
    int rc = sqlite3_prepare_v2(records_db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("error preparing stmt\n");
        return -1;
    }
    int step = sqlite3_step(stmt);
    while (step == SQLITE_ROW)
    {
        r->id = sqlite3_column_int(stmt, 0);
        r->ownerId = sqlite3_column_int(stmt, 1);
        strcpy(r->owner, sqlite3_column_text(stmt, 2));
        r->accountNumber = sqlite3_column_int(stmt, 3);
        r->creationDate = sqlite3_column_int(stmt, 4);
        strcpy(r->country, sqlite3_column_text(stmt, 5));
        r->phoneNumber = sqlite3_column_int(stmt, 6);
        r->balance = sqlite3_column_int(stmt, 7);
        strcpy(r->type, sqlite3_column_text(stmt, 8));
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
    return 0;
}

int update_balance(struct record* r) {
    char sql[255];
    sprintf(sql, "UPDATE \"records\" SET \"balance\" = \"%d\" WHERE \"accountNumber\" = \"%d\";", r->balance, r->accountNumber);
    if (run_single_stmt(records_db, sql) != SQLITE_OK)
        return -1;
    return 0;
}

int update_owner(struct user* u, struct record* r)
{
    char sql[255];
    sprintf(sql, "UPDATE \"records\" SET \"ownerId\" = \"%d\", \"username\" = \"%s\" WHERE \"accountNumber\" = \"%d\";", u->id, u->username, r->accountNumber);
    if (run_single_stmt(records_db, sql) != SQLITE_OK)
        return -1;
    return 0;
}

int delete_account(struct record* r)
{
    char sql[255];
    sprintf(sql, "DELETE FROM \"records\" WHERE \"accountNumber\" = \"%d\";", r->accountNumber);
    if (run_single_stmt(records_db, sql) != SQLITE_OK)
        return -1;
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atm.h"
#include "print.h"

const char* TITLE = "=== 01Founders ATM System ===";

void print_main_menu(void)
{
    system("clear");
    printf("%s\n", TITLE);
    printf("\nWelcome to the 01Founders ATM.\n");
    printf("\n[1] - Register\n");
    printf("\n[2] - Login\n");
    printf("\n[3] - Exit\n");
}

void print_profile_menu(struct user* u)
{
    system("clear");
    printf("%s\n", TITLE);
    printf("\n=== Welcome '%s' ===\n", u->username);
    printf("\n[1] - View Accounts\n");
    printf("\n[2] - Open New Account\n");
    printf("\n[3] - Log Out\n");
}

void print_account_menu(struct record* r)
{
    print_account_details(r);
    printf("\n[1] - Withdraw\n");
    printf("\n[2] - Deposit\n");
    printf("\n[3] - Edit Details\n");
    printf("\n[4] - Transfer Ownership\n");
    printf("\n[5] - Close Account\n");
    printf("\n[6] - Return to 'View Accounts'\n");
    printf("\n[7] - Return To Profile\n");
}

void print_account_details(struct record* r)
{
    system("clear");
    printf("%s\n", TITLE);
    printf("\n=== Account #%d ===\n", r->accountNumber);
    printf("Type: %s\n", r->type);
    printf("Creation Date: %s\n", r->creationDate);
    printf("Country: %s\n", r->country);
    printf("Phone Number: %d\n", r->phoneNumber);
    printf("Balance: £%.2f\n", (double)(r->balance)/100);
    char year[5];
    char yearStart[6];
    strncpy(yearStart, r->creationDate, 6);
    yearStart[5] = '\0';
    int interestYear;
    double interest;
    int idx = 0;
    for (int i = 6; i < 10; i++) {
        year[idx] = r->creationDate[i];
        idx++;
    }
    year[idx] = '\0';
    int yr = atoi(year);
    if (strcmp(r->type, "savings") == 0)
    {
        interest = (double)(r->balance)/10000*(7.0/12.0);
        char dayStart[3];
        strncpy(dayStart, r->creationDate, 3);
        dayStart[2] = '\0';
        printf("\nYou will gain £%.2f interest on day %s of each month.\n", interest, dayStart);
    } else if (strcmp(r->type, "fixed01") == 0)
    {
        interestYear = yr+1;
        interest = (double)(4 * r->balance)/10000;
        printf("\nInterest gained on %s/%d: £%.2f\n", yearStart, interestYear, interest); 
    } else if (strcmp(r->type, "fixed02") == 0)
    {
        interestYear = yr+2;
        interest = (double)(10 * r->balance)/10000;
        printf("\nInterest gained on %s/%d: £%.2f\n", yearStart, interestYear, interest); 
    } else if (strcmp(r->type, "fixed03") == 0)
    {
        interestYear = yr+3;
        interest = (double)(24 * r->balance)/10000;
        printf("\nInterest gained on %s/%d: £%.2f\n", yearStart, interestYear, interest);
    } else {
        printf("\nCurrent accounts do not gain interest.\n");
    }
}

void print_edit_details(struct record* r)
{
    print_account_details(r);
    printf("\n[1] - Update Phone Number\n");
    printf("\n[2] - Update Country\n");
    printf("\n[3] - Return to Account #%d Menu\n", r->accountNumber);
    printf("\n[4] - Return to 'View Accounts'\n");
    printf("\n[5] - Return to My Profile\n");
}

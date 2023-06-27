#ifndef ATM_H
#define ATM_H

struct user {
	// long long id;
	char username[20];
	char password[20];
};

struct record {
	int id;
	//date
	char country[20];
	int accountNumber;
	double balance;
	char type[20];
};

#endif



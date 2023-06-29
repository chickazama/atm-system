#ifndef ATM_H
#define ATM_H

// Represents a user object.
// Contains properties corresponding to a unique ID, username, and password.
struct user {
	__INT16_C id;
	char username[20];
	char password[20];
};

struct record {
	int id;
	char owner[20];
	//date
	int accountNumber;
	char country[20];
	int phoneNumber;
	double balance;
	char type[20];
};

#endif

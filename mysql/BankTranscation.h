#ifndef BANKTRANSACTION_H
#define BANKTRANSACTION_H

#include<bits/stdc++.h>

#include "/usr/local/include/mysql/mysql.h"

using namespace std;

class BankAccount;

class BankTransaction
{
public:
	BankTransaction	(const string="localhost",const string="",
	const string="",const string="");
	~BankTransaction();
	void createAccount(BankAccount*);
	void closeAccount(int);
	void deposit(int, double);
	void withdraw(int, double);
	BankAccount* getAccount(int);
	void printAllAccounts();
	void message(string);
	
private:
	MYSQL* db_conn;
};

#endif // BANKTRANSACTION_H
	


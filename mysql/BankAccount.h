#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include<bits/stdc++.h>
using namespace std;

class BankAccount
{
public:
	static const int MAX_SIZE=30;
	
	BankAccount(int =0,string ="",string="",double=0.0);
	~BankAccount();
	
	void setAccountNumber(int);
	void setFirstName(string);
	void setLastName(string);
	void setBalance(double);
	
	int getAccountNumber() const;
	string getFirstName() const;
	string getLastName() const;
	double getBalance() const;
	
private:
	int accountNumber;
	char firstName[MAX_SIZE];
	char lastName[MAX_SIZE];
	double balance;
};
#endif // BANKACCOUNT_H

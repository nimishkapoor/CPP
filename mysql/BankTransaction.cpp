#include<bits/stdc++.h>
using namespace std;
#include "BankTranscation.h"
#include "BankAccount.h"

BankTransaction::BankTransaction(const string HOST, const string USER, 
	const string PASSWORD,const string DATABASE)
	{
		db_conn=mysql_init(NULL);
		if(!db_conn)
		{
			message("MySQL initialisaton Failed!");
		}
		db_conn=mysql_real_connect(db_conn, HOST.c_str(),
		USER.c_str(),PASSWORD.c_str(), DATABASE.c_str(),0,NULL,0);
		if(!db_conn)
		{
			message("Connection Error!");
		}
	}
BankTransaction::~BankTransaction()
{
	mysql_close(db_conn);
}

BankAccount* BankTransaction::getAccount(int acno)
{
	BankAccount* b=NULL;
	MYSQL_RES* rset=NULL;
	MYSQL_ROW row;
	stringstream sql;
	sql<<"Select * FROM bank_account WHERE acc_no="<<acno;
	if(!mysql_query(db_conn,sql.str().c_str()))
	{
		b=new BankAccount();
		rset=mysql_use_result(db_conn);
		row=mysql_fetch_row(rset);
		b->setAccountNumber(atoi(row[0]));
		b->setFirstName(row[1]);
		b->setLastName(row[2]);
		b->setBalance(atof(row[3]));
	}
	mysql_free_result(rset);
	return b;
}

void BankTransaction::withdraw(int acno,double amount)
{
	BankAccount* b=getAccount(acno);
	if(b!=NULL)
	{
		if(b->getBalance()<amount)
		{
			message("Cant withdraw, try lower amount.");
		}
		else
		{
			b->setBalance(b->getBalance()-amount);
			stringstream sql;
			sql<<"UPDATE bank_account SET balance="<<b->getBalance()<<
			"WHERE acc_no="<<acno;
			if(!mysql_query(db_conn,sql.str().c_str()))
			{
				message("Cash withdraw Sucessfull. Balance updated.");
			}
			else
			{
				message("Cash Deposit Unsucessful. Update failed.");
			}
		}
	}
}

void BankTransaction::deposit(int acno,double amount)
{
	stringstream sql;
	sql<<"UPDATE bank_account SET balance=balance+"<<amount<<
	"WHERE acc_no=<<acno";
	if(!mysql_query(db_conn,sql.str().c_str()))
	{
		message("CashDeposit sucessful.Balance update.");
	}
	else
	{
		message("CashDeposit unsucessful.Update fail.");
	}
}

void BankTransaction::createAccount(BankAccount* ba)
{
	stringstream sql;
	sql<<"INSERT INTO bank_account(acc_no,fname,lname,balance)"<<
	"values ("<<ba->getAccountNumber() <<","
	<<ba->getFirstName()<<","
	<<ba->getLastName()<<","
	<<ba->getBalance()<<")";
	if(!mysql_query(db_conn,sql.str().c_str()))
	{
		message("Account creation sucessful.");
	}
	else
	{
		message("Failed to create account.");
	}
}

void BankTransaction::closeAccount(int acno)
{
	stringstream sql;
	sql<<"DELETE FROM bank_account WHERE acc_no="
	<< acno;
	if(!mysql_query(db_conn,sql.str().c_str()))
	{
		message("Account Deleted Sucessfully");
	}
	else
	{
		message("Failed to Delete Account");
	}
}

void BankTransaction::message(string msg)
{
	cout<<msg<<endl;
}

void BankTransaction::printAllAccounts()
{
	MYSQL_RES* rset=NULL;
	MYSQL_ROW rows;
	string sql="SELECT * FROM bank_account";
	if(mysql_query(db_conn,sql.c_str()))
	{
		message("Error printing all accounts.");
	}
	else
	{
		rset=mysql_use_result(db_conn);
		
		cout << left << setw(10) << setfill('-') << left << '+'
        << setw(21) << setfill('-') << left << '+'
        << setw(21)
        << setfill('-') << left << '+' << setw(21)
        << setfill('-')
        << '+' << '+' << endl;
   cout << setfill(' ') << '|' << left << setw(9)
        << "Account"
        << setfill(' ') << '|' << setw(20) << "First Name"
        << setfill(' ') << '|' << setw(20) << "Last Name"
        << setfill(' ') << '|' << right << setw(20)
        << "Balance" << '|' << endl;
 
   cout << left << setw(10) << setfill('-') << left
       << '+' << setw(21) << setfill('-') << left << '+'
       << setw(21)
       << setfill('-') << left << '+' << setw(21) << setfill('-')
       << '+' << '+' << endl;
      
      
      if(rset)
      {
		  while((rows=mysql_fetch_row(rset)))
		  {
			   cout << setfill(' ') << '|' << left << setw(9) << rows[0]
              << setfill(' ') << '|' << setw(20) << rows[1]
              << setfill(' ') << '|' << setw(20) << rows[2]
              << setfill(' ') << '|' << right << setw(20)
              << rows[3] << '|' << endl;
		  }
		  cout << left << setw(10) << setfill('-') << left
           << '+' << setw(21) << setfill('-') << left << '+'
           << setw(21)
           << setfill('-') << left << '+' << setw(21)
           << setfill('-')
           << '+' << '+' << endl;
	  }
	}
	mysql_free_result(rset);
}



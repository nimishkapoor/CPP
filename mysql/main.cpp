#include<bits/stdc++.h>
using namespace std;

#include "/usr/local/include/mysql/mysql.h"

#include "BankAccount.h"
#include "BankTranscation.h"

enum Options{PRINT=1,NEW,WITHDRAW,DEPOSIT,CLOSE,END};

int mainMenu()
{
	 cout << "\nMenu Options" << endl
        << "1 - Print All Account"
        << endl << "2 - Open New Account" << endl
        << "3 - Withdraw" << endl << "4 - Deposit"
        << endl << "5 - Close Account" << endl
        << "6 - End Transaction" << endl;
        
     int ch;
     cin>>ch;
     return ch;
}

int main(int argc,char** argv)
{
	BankTransaction* bt=new BankTransaction("localhost","root",
	"passwd123","mybank");
	
	int choice;
	int acno;
	string fname,lname;
	double bal;
	while(1)
	{
		choice=mainMenu();
		if(choice==END)
			break;
		switch(choice)
		{
			case PRINT:
				bt->printAllAccounts();
				break;
			case NEW:
				cout<<"\nEnter account no,first name,last name, balance:"
				<<endl<<'?';
				cin>>acno;
				cin>>fname;
				cin>>lname;
				cin>>bal;
				if(acno<1)
				{
					cout<<"Invalid account number."<<endl;
					break;
				}
				bt->createAccount(new BankAccount(acno,fname,lname,bal));
				break;
			
			case WITHDRAW:
				cout<<"Enter account no, amount to withdraw:"<<endl
				<<"?";
				cin>>acno;
				cin>>bal;
				if(bal<0)
				{
					cout<<"Invalid Amount."<<endl;
					break;
				}
				bt->deposit(acno,bal);
				break;
			case CLOSE:
				cout<<"\Enter account number to close:"<<endl<<"?";
				cin>>acno;
				bt->closeAccount(acno);
				break;
			default:
				cerr<<"Invalid choice"<<endl;
				break;
		}
	}
	return 0;
}

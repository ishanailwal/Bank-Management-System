#include<fstream>
#include<ctype.h>
#include<iomanip>
#include<conio.h>
#include<cstdio>
#include<stdlib.h>
#include<iostream>

using namespace std;


//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
	int password;
public:
	void create_account();	//function to get data from user
	void show_account();	//function to show data on screen
	void modify();   //function to get new data from user
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report();	//function to show data in tabular format
	int retacno();	//function to return account number
	int retpassword();  //function to return password
	int retdeposit();	//function to return balance amount
	char rettype();	//function to return type of account

};         



void account::create_account()
{
	cout << "\n\tEnter The account No.";
	cin >> acno;
	cout << "\tEnter Password(only number): ";
	cin >> password;
	cout << "\n\n\tEnter The Name of The account Holder : ";
	fgets(name, sizeof(50), stdin);
	cout << "\n\tEnter Type of The account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\n\tEnter The Initial amount: ";
	cin >> deposit;
	cout << "\n\n\n\tAccount Created..";
}

void account::show_account()
{
	cout << "\n\tAccount No. : " << acno;
	cout << "\n\tAccount Holder Name : ";
	cout << name;
	cout << "\n\tType of Account : " << type;
	cout << "\n\tBalance amount : " << deposit;
}


void account::modify()
{
	cout << "\n\tThe account No." << acno;
	cout << "\n\n\tEnter The Name of The account Holder : ";
	fgets(name, sizeof(50), stdin);
	cout << "\n\tEnter Type of The account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\n\tEnter The amount : ";
	cin>> deposit;
}


void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report()
{
	cout << " " << acno << setw(10) << " " << name << setw(8) << " " << type << setw(11) << deposit << endl;
}

int account::retacno()
{
	return acno;
}
int account::retpassword()
{
	return password;
}

int account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}


//***************************************************************
//    	        function declaration
//****************************************************************

void write_account();	              //function to write record in binary file
void display_sp(int, int);	      //function to display account details given by user
void modify_account(int);             //function to modify record of file
void delete_account(int);	      //function to delete record of file
void display_all();		      //function to display all account details
void deposit_withdraw(int, int, int); // function to desposit/withdraw amount for given account
void intro();	                      //introductory screen function
int extra();


//***************************************************************
//    	     THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	system("CLS");
	intro();
	system("CLS");
	extra();
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write((char*)&ac, sizeof(account));
	outFile.close();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n, int x)
{
	int found = 0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (File.read((char*)&ac, sizeof(account)) && found == 0)
	{
		if (ac.retacno() == n && ac.retpassword() == x)
		{
			ac.show_account();
			found = 1;
		}
	}
	File.close();
	if (found == 0)
		cout << "\n\n\tAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
	int found = 0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "\tFile could not be open !! Press any Key...";
		return;
	}
	while (File.read((char*)&ac, sizeof(account)) && found == 0)
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\n\tEnter The New Details of account" << endl;
			ac.modify();
			int pos = (-1) * sizeof(account);
			File.seekp(pos, ios::cur);
			File.write((char*)&ac, sizeof(account));
			cout << "\n\n\t Record Updated";
			found = 1;
		}
	}
	File.close();
	if (found == 0)
		cout << "\n\n\tRecord Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read((char*)&ac, sizeof(account)))
	{
		if (ac.retacno() != n)
		{
			outFile.write((char*)&ac, sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << " ====================================================\n";
	cout << " A/c no.        NAME      Type    Balance\n";
	cout << " ====================================================\n";
	while (inFile.read((char*)&ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option, int x)
{
	int amt;
	int found = 0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (File.read((char*)&ac, sizeof(account)) && found == 0)
	{
		if (ac.retacno() == n && ac.retpassword() == x)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\t\tTO DEPOSITE AMOUNT ";
				cout << "\n\n\tEnter The amount to be deposited: ";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\t\tTO WITHDRAW AMOUNT ";
				cout << "\n\n\tEnter The amount to be withdraw: ";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "\tInsufficience balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * sizeof(ac);
			File.seekp(pos, ios::cur);
			File.write((char*)&ac, sizeof(account));
			cout << "\n\n\t Record Updated";
			found = 1;
		}
	}
	File.close();
	if (found == 0)
		cout << "\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout << "\n\n\n\n\n\n\n\n\n\t\t\t  BANK MANAGEMENT SYSTEM";
	_getch();
}


//***************************************************************
//    	FUNCTION TO DISPLAY LOGIN OPTIONS
//****************************************************************

int extra()
{
	char ch;
	int num;
	int choice;
	int pass;
	int x;
	system("CLS");
	cout << "\n\n\n\n\n\n\t\t\t Select: ";
	cout << endl << "\t\t\t\t1. Admin" << endl << "\t\t\t\t2. User";
	cout << endl << "\t\t\t\t3. Exit";
	cout << endl << endl << "\t\t\t      ";
	cin >> choice;
	if (choice == 1)
	{
		system("CLS");
		cout << "\n\n\n\n\n\n\t\t\t Enter Passcode: " << endl;
		cout << "\n\n\t\t\t\t";
		cin >> x;
		if (x == 1234)
		{
			do
			{
				system("CLS");
				cout << "\n\n\n\tMAIN MENU";
				cout << "\n\n\t01. NEW ACCOUNT";
				cout << "\n\n\t02. ALL ACCOUNT HOLDER LIST";
				cout << "\n\n\t03. CLOSE AN ACCOUNT";
				cout << "\n\n\t04. MODIFY AN ACCOUNT";
				cout << "\n\n\t05. BACK TO MAIN MENU";
				cout << "\n\n\t06. EXIT";
				cout << "\n\n\tSelect Your Option (1-6) ";
				cin >> ch;
				system("CLS");
				switch (ch)
				{
				case '1':
					write_account();
					break;
				case '2':
					display_all();
					break;
				case '3':
					cout << "\n\n\tEnter The account No. : "; cin >> num;
					delete_account(num);
					break;
				case '4':
					cout << "\n\n\tEnter The account No. : "; cin >> num;
					modify_account(num);
					break;
				case '5':
					extra();
					break;
				case '6':
					cout << "\n\n\t\t\tThanks for using bank managemnt system...";
					_getch();
					exit(0);
				default:cout << "\n\n\n\t\t\t Invalid Entry!!" << "\a";
				}
				_getch();
			} while (ch != '6');
			return 0;
		}
		else
		{
			cout << "\n\n\t\t\tWrong Passcode!!!";
		}
	}
	else if (choice == 2)
	{
		do
		{
			system("CLS");
			cout << "\n\n\n\tMAIN MENU";
			cout << "\n\n\t01. DEPOSIT AMOUNT";
			cout << "\n\n\t02. WITHDRAW AMOUNT";
			cout << "\n\n\t03. BALANCE ENQUIRY";
			cout << "\n\n\t04. BACK TO MAIN MENU";
			cout << "\n\n\t05. EXIT";
			cout << "\n\n\tSelect Your Option (1-4) ";
			cin >> ch;
			system("CLS");
			switch (ch)
			{
			case '1':
				cout << "\n\n\tEnter The account No. : "; cin >> num;
				cout << "\n\tEnter password: "; cin >> pass;
				deposit_withdraw(num, 1, pass);
				break;
			case '2':
				cout << "\n\n\tEnter The account No. : "; cin >> num;
				cout << "\n\tEnter password: "; cin >> pass;
				deposit_withdraw(num, 2, pass);
				break;
			case '3':
				cout << "\n\n\tEnter The account No. : "; cin >> num;
				cout << "\n\tEnter password: "; cin >> pass;
				display_sp(num, pass);
				break;
			case '4':
				extra();
				break;
			case '5':
				cout << "\n\n\t\t\tThanks for using bank managemnt system";
				_getch();
				exit(0);
			default:cout << "\n\n\n\t\t\t  Invalid Entry!!" << "\a";
			}
			_getch();
		} while (ch != '5');
		return 0;
	}
	else if (choice == 3)
	{
	system("CLS");
		cout << "\n\n\t\t\tThanks for using bank managemnt system";
	}
	else {
		cout << "\n\n\n\t\t\t  Invalid Entry!!" << "\a";
	}
	_getch();
}


//***************************************************************
//    		END OF PROJECT
//***************************************************************

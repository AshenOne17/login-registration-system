#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <utility>
#include <vector>

// Declaring using std:: statements separately to avoid conflicts in namespaces with std namespace
using std::cout; using std::cin;
using std::cerr; using std::ios;
using std::getline; using std::endl; // '\n' is preferred over std::endl
using std::fstream; using std::ofstream;
using std::string; using std::ifstream;
using std::vector;
// ...

int main(int argc, char** argv) 
{
	cout << "Sign up (1) or log in (2): ";
	int choice;

	string registerUsername;
	string registerPassword;

	string::size_type usernameLength = 0;
	string::size_type passwordLength = 0;

	try 
	{
		cin >> choice;
		if (choice != 1 && choice != 2) { throw - 1; }
	}
	catch (...) 
	{
		cerr << "Wrong operation has been chosen!\n";
		exit(1);
	}
	// Choice between registering or logging
	if (choice == 1) // sign up
	{
		ofstream outf("Login_Info.txt", ios::app); // Opening an output stream into info file
		
		if (!outf) 
		{
			cerr << "Error while opening the file!\n";
			outf.close();
			exit(1);
		}

		cin.ignore();

		cout << "Enter your username (3 to 16 latin char., numbers, or symbols): ";
		
		try 
		{
			getline(cin, registerUsername);

			usernameLength = registerUsername.size();
			if (usernameLength < 3 || usernameLength > 16) { throw - 1; }
		}
		catch (...) 
		{
			cerr << "Wrong username length!\n";
			outf.close();
			exit(1);
		}
		
		cout << "Enter your password (4 to 32 latin char., numbers, or symbols): ";
		
		try 
		{
			getline(cin, registerPassword);

			passwordLength = registerPassword.size();
			if (passwordLength < 4 || passwordLength > 32) { throw - 1; }
			
		}
		catch (...) 
		{
			cerr << "Wrong password length!\n";
			outf.close();
			exit(1);
		}

		ifstream read("Login_Info.txt", ios::in);
		string strInput;

		while (read)
		{
			getline(read, strInput);
			if (strInput == registerUsername) 
			{
				cout << "Username is already taken!\n";
				outf.close();
				read.close();
				exit(1);
			}
			
		}

		outf << registerUsername << '\n';
		outf << registerPassword << '\n';
		cout << "\nWelcome, " << registerUsername << "!\n"
			<< "Your login password: " << registerPassword << "\n\n";

		cout << "*Your login info has been saved*\n\n";

		outf.close();
		read.close();
		return 0;
	}
	else if (choice == 2) 
	{
		ifstream read("Login_Info.txt", ios::in);

		if (!read) {
			cerr << "Error while opening the file!\n";
			read.close();
			exit(1);
		}

		cin.ignore();

		cout << "Enter your username: ";
		
		try
		{
			getline(cin, registerUsername);

			usernameLength = registerUsername.size();
			if (usernameLength < 3 || usernameLength > 16) { throw - 1; }
		}
		catch (...)
		{
			cerr << "Wrong username length!\n";
			read.close();
			exit(1);
		}

		cout << "Enter your password: ";

		try
		{
			getline(cin, registerPassword);

			passwordLength = registerPassword.size();
			if (passwordLength < 4 || passwordLength > 32) { throw - 1; }

		}
		catch (...)
		{
			cerr << "Wrong password length!\n";
			read.close();
			exit(1);
		}

		string strInput;
		int count = 0;

		while (read)
		{
			if (count == 2) { break; }

			getline(read, strInput);

			if (registerUsername == strInput) { count++; }
			if (registerPassword == strInput) { count++; }

			if (read.eof()) 
			{
				cout << "Username or password is incorrect!\n";
				read.close();
				exit(1);
			}
		}

		cout << "\nWelcome, " << registerUsername << "!\n";
		read.close();
		return 0;
	}
	
}
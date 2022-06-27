#include "Password.h"
#include "User.h"
#include "StoredData.h"
#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <filesystem>
#include <fstream>

using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::vector;
using std::wstring;
using std::endl;

Password::Password()
{
}

/*Standard caesar cypher encryption*/
string Password::EncryptPassword(string password)
{
	for (int i = 0; i < password.size(); i++)
	{
		password[i] = (char)((int)password[i] + 15); 
	}

	return password;
}

/*Reverse caesar cypher*/
string Password::DecryptPassword(string password)
{
	for (int i = 0; i < password.size(); i++)
	{
		password[i] = (char)((int)password[i] - 15);
	}

	return password;
}

bool Password::CheckPassword(User user, string enteredPassword)
{
	ifstream fin;
	fin.open(user.GetUserInfoPath());

	if (fin.is_open())
	{
		string userPassword;
		getline(fin, userPassword);

		if (DecryptPassword(userPassword) == enteredPassword)
		{
			fin.close();
			return true;
		}
		else
		{
			fin.close();
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Password::ChangeAccountPassword(User user, string newAccountPassword)
{
	fstream file;
	file.open(user.GetUserInfoPath());

	if (file.is_open())
	{
		file << EncryptPassword(newAccountPassword);
		file.close();
		cout << "Password Changed." << endl;
		return true;
	}
	else
	{
		cout << "User Info File Could Not Be Opened. Password Not Changed." << endl;
		return false;
	}
}

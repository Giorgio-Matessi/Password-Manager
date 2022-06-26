#include "Password.h"
#include "User.h"
#include "StoredData.h"
#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <filesystem>
#include <fstream>

using namespace std;

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
	fin.open(user.GetUserInfoDir());

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
	file.open(user.GetUserInfoDir());

	if (file.is_open())
	{
		file << EncryptPassword(newAccountPassword);
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

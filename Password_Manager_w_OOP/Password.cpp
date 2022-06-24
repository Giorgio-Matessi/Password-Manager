#include "Password.h"
#include <iostream>

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

bool Password::ChangeAccountPassword(string newAccountPassword)
{

	return false;
}

string Password::GenerateRandomPassowrd(int passwordLength)
{
	return string();
}

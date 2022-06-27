#pragma once

/*
 *  Name:		 Password.h
 *  Purpose:     Declarations for all password functions and data
 *  Author:      Giorgio Matessi
 *  Created:     06/24/22
 */

#include <iostream>
#include "User.h"
#include "StoredData.h"

using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;
using std::wstring;
using std::endl;

#ifndef PASSWORD_H
#define PASSWORD_H
class Password 
{
public:
	Password(); //Default constuctor for password object
 
	static string EncryptPassword(string password); //Encrypts password before file storage *** Returns encrypted string 
	static string DecryptPassword(string password); //Decrypts password when reading from file *** Returns decrypted string

	static bool CheckPassword(User user, string enteredPassword); //Checks if user password is same as entered password

	static bool ChangeAccountPassword(User user, string newAccountPassword); //Changes account password and stores *** Returns true if successful 
};

#endif
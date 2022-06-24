#pragma once

/*
 *  Name:		 Password.h
 *  Purpose:     Declarations for all password functions and data
 *  Author:      Giorgio Matessi
 *  Created:     06/24/22
 */

#include <iostream>

using namespace std;

#ifndef PASSWORD_H
#define PASSWORD_H
class Password
{
public:
	Password(); //Default constuctor for password object
 
	static string EncryptPassword(string password); //Encrypts password before file storage *** Returns encrypted string 
	static string DecryptPassword(string password); //Decrypts password when reading from file *** Returns decrypted string

	static bool ChangeAccountPassword(string newAccountPassword); //Changes account password and stores *** Returns true if successful 

	static string GenerateRandomPassowrd(int passwordLength); //Creates random password of given length *** Returns generated password
};

#endif
#pragma once

/*
 *  Name:        User.h
 *  Purpose:     Declarations for all user data and functions
 *  Author:      Giorgio Matessi
 *  Created:     06/20/22
 */

#include <iostream>

#ifndef USER_H
#define USER_H

using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;
using std::wstring;
using std::endl;

class User
{
public:
	User(string inputUserName); //Constructor for a user instance **** Defines specific user file directories where data is stored and read

	//Getters for User:
	string GetUsername();
	string GetUserInfoPath();
	string GetUserFolderPath();
	

private:

	string username; //Defined once logged in/account made
	string userInfoPath; //Path of User-System-Password/Stored Passwords ***** Initialized in User Constructor 
	string userFolderPath; //Path of User Folder ***** Initialized in User Constructor

};

#endif USER_H




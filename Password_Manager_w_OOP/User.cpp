/*
 *  Name:        User.cpp
 *  Purpose:     Definitions for all user data and functions
 *  Author:      Giorgio Matessi
 *  Created:     06/20/22
 */

#include "User.h"

User::User(string inputUserName)
{
	username = inputUserName;
	userInfoDir = "C:\\Users\\giorg\\Documents\\Password_Manager\\Users\\" + username + "\\" + "Info"; //Stored in Documents Folder 
}

string User::GetUsername()
{
	return username;
}

string User::GetUserInfoDir()
{
	return userInfoDir;
}

vector<string> User::GetSiteNames()
{
	return siteNames;
}

vector<string> User::GetPasswords()
{
	return passwords;
}

/*
 *  Name:        User.cpp
 *  Purpose:     Definitions for all user data and functions
 *  Author:      Giorgio Matessi
 *  Created:     06/20/22
 */

#include "User.h"
#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <fstream>


//Get Documents Path on current computer using Windows API Function
string GetDocumentsPath()
{
	//Get Documents Path on current computer using Windows API Function
	char pathChar[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathChar);

	string documentsPath(pathChar);

	if (result != S_OK) {
		cout << "Error: " << result << endl;
	}

	return documentsPath;
}

User::User(string inputUserName)
{
	username = inputUserName;

	userInfoDir = GetDocumentsPath() + "\\" + "Password_Manager" + "\\" + "Users" + username + "\\" + "Info.txt"; //Stored in Documents Folder 
}

string User::GetUsername()
{
	return username;
}

string User::GetUserInfoDir()
{
	return userInfoDir;
}



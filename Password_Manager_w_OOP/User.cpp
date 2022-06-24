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
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

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

	string documentsPath = GetDocumentsPath();
	userInfoDir = documentsPath + "\\" + "Password_Manager" + "\\" + "Users" + username + "\\" + "Info"; //Stored in Documents Folder 
}

string User::GetUsername()
{
	return username;
}

string User::GetUserInfoDir()
{
	return userInfoDir;
}



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
#include <iostream>
#include "Knownfolders.h"

using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;
using std::wstring;
using std::endl;


//Get Documents Path on current computer using Windows API Function
string GetDocumentsPath()
{
	//Get Documents Path on current computer using Windows API Function
	PWSTR ppszPath;    // variable to receive the path memory block pointer.

	HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &ppszPath);

	wstring myPath;
	if (SUCCEEDED(hr)) {
		myPath = ppszPath;      // make a local copy of the path
	}

	string path = std::filesystem::path(myPath).string();

	return path;
}

User::User(string inputUserName)
{
	username = inputUserName;

	userInfoPath = GetDocumentsPath() + "\\Password_Manager\\Users\\" + inputUserName + "\\Info.txt"; 

	userFolderPath = GetDocumentsPath() + "\\Password_Manager\\Users\\" + inputUserName; 
}

string User::GetUsername()
{
	return username;
}

string User::GetUserInfoPath()
{
	return userInfoPath;
}

string User::GetUserFolderPath()
{
	return userFolderPath;
}





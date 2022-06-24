#include "StoredData.h"
#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

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

StoredData::StoredData()
{
	allUsersFilePath = GetDocumentsPath() + "\\Password_Manager\\users.txt";
}

bool StoredData::FirstTimeOpen()
{
	string path = GetDocumentsPath() + "\\Password_Manager";

	if (!fs::exists(path))
	{
		//Create Folders
		fs::create_directory(path);
		fs::create_directory(path + "\\Users");
		ofstream fout;
		
		//Create users file
		fout.open(path + "\\users.txt");
		fout << endl;
		fout.close();

	}
	//Checks if Application has all folders
	if (fs::exists(path) && fs::exists(path + "\\Users"))
	{
		cout << "Application Successfully Loaded." << endl;
		return true;
	}
	else
	{
		cout << "Application Loaded Incorrectly." << endl;
		return false;
	}
}

int StoredData::SearchSite(string siteName)
{
	return 0;
}

string StoredData::GetSiteNameAt(int index)
{
	return string();
}

string StoredData::GetPasswordAt(int index)
{
	return string();
}

bool StoredData::CheckUserExist(string User)
{
	return false;
}

bool StoredData::CreateNewUser(string newUsername)
{
	string documentsPath = GetDocumentsPath();

	string tempPath; //Path to User Folder
	tempPath = documentsPath + "\\Password_Manager\\Users\\" + newUsername;

	//Creates Directory
	if (fs::create_directory(tempPath) != true){
		return false;
	}

	return true;
}

bool StoredData::StoreNewPassword(string siteName, string password)
{

}

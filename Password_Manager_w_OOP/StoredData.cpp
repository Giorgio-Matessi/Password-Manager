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
}

int StoredData::GetSiteIndex(string siteName)
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
	tempPath = documentsPath + "\\" + "Password_Manager" + "\\" + "Users" + newUsername;

	if (fs::create_directory(tempPath) != true){
		return false;
	}

	return true;
}

bool StoredData::StoreNewPassword(string siteName, string password)
{

}

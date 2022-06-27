/*
 *  Name:        StoredData.cpp
 *  Purpose:     Definitions for all data related functions and data members
 *  Author:      Giorgio Matessi
 *  Created:     06/25/22
 */


#include "StoredData.h"
#include "Password.h"
#include "User.h"
#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <filesystem>
#include <fstream>

using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;
using std::wstring;
using std::endl;

StoredData::StoredData()
{
	allUsersFilePath = GetDocumentsPath() + "\\Password_Manager\\users.txt";
	passwordsStored = 0;
}

bool StoredData::FirstTimeOpen()
{
	string path = GetDocumentsPath() + "\\Password_Manager";

	if (!std::filesystem::exists(path))
	{
		//Create Folders
		std::filesystem::create_directory(path);
		std::filesystem::create_directory(path + "\\Users");
		ofstream fout;
		
		//Create users file
		fout.open(path + "\\users.txt");
		fout << endl;
		fout.close();

	}
	//Checks if Application has all folders
	if (std::filesystem::exists(path) && std::filesystem::exists(path + "\\Users") && std::filesystem::exists(path + "\\users.txt"))
	{
		cout << "Application Successfully Loaded." << endl;
		return true;
	}
	else
	{
		cout << "Program Did Not Fully Load. Repairing..." << endl;
		if (!std::filesystem::exists(path + "\\Users"))
		{
			std::filesystem::create_directory(path + "\\Users");	
		}
		if (!std::filesystem::exists(path + "\\users.txt"))
		{
			ofstream fout;
			fout.open(path + "\\users.txt");
			fout << endl;
			fout.close();
		}
		cout << "Repaired." << endl;
	}
	return true;
}

void StoredData::GetSitePassword(string siteName)
{
	int index = SearchForSite(siteName);

	if (index != -1)
	{
		cout << "Site Name: " << siteNames[index] << endl;
		cout << "Site Password: " << passwords[index] << endl;
		return;
	}
	else
	{
		cout << "Could Not Find Site." << endl;
		return;
	}
}

int StoredData::GetNumPasswordsStored()
{
	return passwordsStored;
}

bool StoredData::ChangeSpecificPassword(string siteName, string newPassword)
{
	int index = SearchForSite(siteName);

	if (index != -1)
	{
		passwords[index] = newPassword;
		cout << "Password Was Changed." << endl;
		return true;
	}
	else
	{
		cout << "Site Could Not Be Found. Password Was Not Changed." << endl;
		return false;
	}
}

bool StoredData::CheckUserExists(string username)
{
	string temp = "";
	ifstream fin;
	fin.open(allUsersFilePath);

	//Scan file to find matching username
	while (!fin.eof())
	{
		getline(fin, temp);
		if (temp == username)
		{
			return true;
		}
	}
	return false;
}

bool StoredData::CreateNewUser(string newUsername, string accountPassword)
{
	if (CheckUserExists(newUsername))
	{
		cout << "\nUser Already Exists." << endl;
		return false;
	}

	string tempPath; //Path to User Folder
	tempPath = GetDocumentsPath() + "\\Password_Manager\\Users\\" + newUsername;

	//Creates User Folder 
	if (std::filesystem::create_directory(tempPath) != true){
		return false;
	}

	//Create Info.txt file in User Folder and Store Account Password
	User User(newUsername);
	ofstream fout;
	fout.open(GetDocumentsPath() + "\\Password_Manager\\Users\\" + newUsername + "\\Info.txt");
	fout << Password::EncryptPassword(accountPassword) << endl;
	fout.close();

	//Add users name to the end of users.txt file
	fout.open(allUsersFilePath, std::ios::app);
	fout << newUsername << endl;
	fout.close();

	cout << "Account Created." << endl;
	return true;
}

bool StoredData::StoreNewPassword(string siteName, string password)
{
	int exists = SearchForSite(siteName);

	if (exists == -1)
	{
		siteNames.push_back(siteName);
		passwords.push_back(password);
		passwordsStored++;
		cout << "Site Name: " << siteName << endl;
		cout << "Site Password: " << password << endl;
		cout << "Password Stored." << endl;
		return true;
	}
	else
	{
		cout << "Site Already Exists. Did Not Store." << endl;
		return false;
	}
}

bool StoredData::GenerateAndStoreRandomPassword(string siteName, int passwordLength)
{


	char lowerCase[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char upperCase[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	char special[] = { '!', '”', '#', '$', '%', '&', '’', '(',  ')', '*', '+', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '~', '{', '|', '}' };

	srand(time(NULL));
	string newPassword = "";
	int rLowerUpper;
	int rSpecial;
	int rRan;

	for (int i = 0; i < passwordLength; i++)
	{
		rRan = rand() % 300;

		//lowerCase
		if (rRan < 100)
		{
			rLowerUpper = rand() % sizeof(lowerCase);

			newPassword = newPassword + lowerCase[rLowerUpper];
		}
		//upperCase
		else if (rRan >= 100 && rRan < 200)
		{
			rLowerUpper = rand() % sizeof(upperCase);;
			newPassword = newPassword + upperCase[rLowerUpper];
		}
		//special
		else if (rRan >= 200 && rRan < 300)
		{
			rSpecial = rand() % 25;
			newPassword = newPassword + special[rSpecial];
		}
	}

	return StoreNewPassword(siteName, newPassword);
}

void StoredData::LoadUserData(User user)
{
	cout << "\nLoading User Data...." << endl;
	string tempString = "";
	string arr[2];
	ifstream fin;
	fin.open(user.GetUserInfoPath());
	int passwordCount = 0;

	if (fin.is_open())
	{
		getline(fin, tempString); //Skip First line since the first line is dedicated to the system password
		
		//Read file and store passowords and site names in respective vectors
		while (!fin.eof())
		{
			getline(fin, tempString);
			if (tempString != "")
			{
				Split(tempString, ',', arr, 2);
				siteNames.push_back(arr[0]);
				passwords.push_back(Password::DecryptPassword(arr[1]));
				passwordCount++;
			}

		}
	}
	fin.close();

	passwordsStored = passwordCount;

	cout << "Successfully Loaded." << endl;
	return;
}

int StoredData::SaveUserData(User user , int flag = 0, string newAccountPassword= "")
{
	if (flag == 0)
	{
		cout << "\nSaving User Data...." << endl;
		//Store system password before rewriting file
		ifstream fin;
		fin.open(user.GetUserInfoPath());
		string tempSysPass;
		getline(fin,tempSysPass);
		fin.close();
	
		//Write system password and all other passwords and site names to file
		int passwordCount=0; //Counts how many passwords were stored
	
		ofstream fout;
		fout.open(user.GetUserInfoPath());
		fout << tempSysPass << endl; //write system password at the top of the file

		//Run through vectors while storing their values
		for (int i = 0; i < siteNames.size(); i++)
		{
			fout << siteNames[i] << "," << Password::EncryptPassword(passwords[i]) << endl;
			passwordCount++;
		}
		fout.close();

		cout << "User Data Saved." << endl;
		return passwordCount;
	}
	else
	{
		cout << "\nSaving User Data...." << endl;
		string tempSysPass = newAccountPassword;
		
		//Write system password and all other passwords and site names to file
		int passwordCount = 0; //Counts how many passwords were stored

		ofstream fout;
		fout.open(user.GetUserInfoPath());
		fout << Password::EncryptPassword(tempSysPass) << endl; //write system password at the top of the file

		//Run through vectors while storing their values
		for (int i = 0; i < siteNames.size(); i++)
		{
			fout << siteNames[i] << "," << Password::EncryptPassword(passwords[i]) << endl;
			passwordCount++;
		}
		fout.close();

		cout << "User Data Saved." << endl;
		return passwordCount;
	}

}

void StoredData::BackupUserData(User user)
{
	SaveUserData(user);
	
	cout << "\nCreating Backup File...." << endl;
	//Store system password before rewriting file
	ifstream fin;
	fin.open(user.GetUserInfoPath());
	string tempSysPass;
	getline(fin, tempSysPass);
	fin.close();

	ofstream fout;
	string path = GetDocumentsPath() + "\\Password_Manager\\Users\\" + user.GetUsername() + "\\Backup_File.txt";
	fout.open(path);

	

	fout << tempSysPass << endl; //write system password at the top of the file

	//Run through vectors while storing their values
	for (int i = 0; i < siteNames.size(); i++)
	{
		fout << siteNames[i] << "," << Password::EncryptPassword(passwords[i]) << endl;
	}

	cout << "Backup File Created In: " << user.GetUserFolderPath() << endl;
	return;
}



//Private Member Functions:
string StoredData::ToLow(string inputString, int stringLength)
{
	for (int i = 0; i < stringLength; i++)
	{
		inputString[i] = tolower(inputString[i]);
	}

	return inputString;
}
 									     
int StoredData::Split(string inputString, char separator, string arr[], int size) {
	//check for length 0 array
	if (inputString.length() == 0) {
		return 0;
	}
	int arrPosition = 0, splitPiece = 0;
	string substring = "";

	//add seperator to the end of inputString
	inputString += separator;
	for (int i = 0; i < inputString.length(); i++) {
		// check for seperator 
		if (inputString[i] == separator) {
			if (arrPosition < size) {
				splitPiece++;
				arr[arrPosition] = substring;
				arrPosition++;
				substring = "";
			}
			else {
				return -1;
			}
		}
		else {
			// add character to substring
			substring += inputString[i];
		}
	}
	return splitPiece;
}      //

int StoredData::SearchForSite(string siteName)
{
	for (int i = 0; i < siteNames.size(); i++)
	{
		if (ToLow(siteName, siteName.length()) == ToLow(siteNames[i], siteNames[i].length()))
		{
			return i;
		}
	}

	return -1;
}

string StoredData::GetDocumentsPath()
{

	//Get Documents Path on current computer using Windows API Function
	PWSTR ppszPath;    // variable to receive the path memory block pointer.

	HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &ppszPath);

	std::wstring myPath;
	if (SUCCEEDED(hr)) {
		myPath = ppszPath;      // make a local copy of the path
	}

	string path = std::filesystem::path(myPath).string();

	return path;
}


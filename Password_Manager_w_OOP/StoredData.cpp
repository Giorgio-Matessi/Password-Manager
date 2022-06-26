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

namespace fs = std::filesystem;
using namespace std;

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

string StoredData::GetSiteName(string siteName)
{
	int index = SearchForSite(siteName);

	if (index != -1)
	{
		return siteNames[index];
	}
	else
	{
		return " ";
	}
}

string StoredData::GetSitePassword(string siteName)
{
	int index = SearchForSite(siteName);

	if (index != -1)
	{
		return passwords[index];
	}
	else
	{
		return " ";
	}
}

bool StoredData::ChangeSpecificPassword(string siteName, string newPassword)
{
	int index = SearchForSite(siteName);

	if (index != -1)
	{
		passwords[index] = newPassword;
		return true;
	}
	else
	{
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

bool StoredData::CreateNewUser(string newUsername)
{

	string tempPath; //Path to User Folder
	tempPath = GetDocumentsPath() + "\\Password_Manager\\Users\\" + newUsername;

	//Creates User Folder 
	if (fs::create_directory(tempPath) != true){
		return false;
	}

	//Create Info.txt file in User Folder
	User User(newUsername);
	ofstream fout;
	fout.open(User.GetUserInfoDir());
	fout << endl;
	fout.close();

	//Add users name to the end of users.txt file
	fout.open(allUsersFilePath, ios::app);
	fout << newUsername << endl;
	fout.close();

	return true;
}

bool StoredData::StoreNewPassword(string siteName, string password)
{
	int exists = SearchForSite(siteName);

	if (exists == -1)
	{
		siteNames.push_back(siteName);
		passwords.push_back(password);
		return true;
	}
	else
	{
		return false;
	}
}

bool StoredData::GenerateAndStoreRandomPassword(string siteName, int passwordLength)
{


	char lowerCase[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char upperCase[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	char special[] = { '!', '”', '#', '$', '%', '&', '’', '(',  ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '~', '{', '|', '}' };

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
			rLowerUpper = rand() % 25 + 1;

			newPassword = newPassword + lowerCase[rLowerUpper];
		}
		//upperCase
		else if (rRan >= 100 && rRan < 200)
		{
			rLowerUpper = rand() % 25 + 1;
			newPassword = newPassword + upperCase[rLowerUpper];
		}
		//special
		else if (rRan >= 200 && rRan < 300)
		{
			rSpecial = rand() % 31;
			newPassword = newPassword + special[rSpecial];
		}
	}

	return StoreNewPassword(siteName, newPassword);
}

int StoredData::LoadUserData(User user)
{
	string tempString = "";
	string arr[2];
	ifstream fin;
	fin.open(user.GetUserInfoDir());
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
				split(tempString, ',', arr, 2);
				siteNames.push_back(arr[0]);
				passwords.push_back(Password::DecryptPassword(arr[1]));
				passwordCount++;
			}

		}
	}
	fin.close();
	return passwordCount;
}

int StoredData::SaveUserData(User user)
{
	//Store system password before rewriting file
	ifstream fin;
	fin.open(user.GetUserInfoDir());
	string tempSysPass;
	getline(fin,tempSysPass);
	fin.close();
	
	//Write system password and all other passwords and site names to file
	int passwordCount=0; //Counts how many passwords were stored
	
	ofstream fout; 
	fout.open(user.GetUserInfoDir());
	fout << tempSysPass << endl; //write system password at the top of the file

	//Run through vectors while storing their values
	for (int i = 0; i < siteNames.size(); i++)
	{
		fout << siteNames[i] << "," << Password::EncryptPassword(passwords[i]) << endl;
		passwordCount++;
	}
	fout.close();

	return passwordCount;
}

void StoredData::BackupUserData(User user)
{
	//Store system password before rewriting file
	ifstream fin;
	fin.open(user.GetUserInfoDir());
	string tempSysPass;
	getline(fin, tempSysPass);
	fin.close();

	ofstream fout;
	string path = GetDocumentsPath() + "\\Password_Manager\\Users" + user.GetUsername() + "Backup_File.txt";
	fout.open(path);

	fout << tempSysPass << endl; //write system password at the top of the file

	//Run through vectors while storing their values
	for (int i = 0; i < siteNames.size(); i++)
	{
		fout << siteNames[i] << "," << Password::EncryptPassword(passwords[i]) << endl;
	}

	return;
}


//Private Member Functions:
string StoredData::toLow(string inputString, int stringLength)
{
	for (int i = 0; i < stringLength; i++)
	{
		inputString[i] = tolower(inputString[i]);
	}

	return inputString;
}
 									     
int StoredData::split(string inputString, char separator, string arr[], int size) {
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
		if (toLow(siteName, siteName.length()) == toLow(siteNames[i], siteNames[i].length()))
		{
			return i;
		}
	}

	return -1;
}

string StoredData::GetDocumentsPath()
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

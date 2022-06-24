#pragma once


#ifndef STOREDDATA_H
#define STOREDDATA_H

#include <vector>
#include <iostream>

using namespace std;

class StoredData
{

public:
	StoredData();

	int GetSiteIndex(string siteName);
	string GetSiteNameAt(int index);
	string GetPasswordAt(int index);

	static bool CheckUserExist(string User); //Checks if user is stored and exists *** Returns true if user exists
	static bool CreateNewUser(string newUsername); //Stores user and creates all files for specific user

	static bool StoreNewPassword(string siteName, string password);
private:
	/* 
		* Initialzed once user has logged in
		* A site and its password have the same index in siteNames and password vectors, respectivly
	*/
	vector<string> siteNames; //Vector of all sites stored				
	vector<string> passwords; //Vector of all stored passwords 
	string allUsersFilePath; //Path to all users.txt File
	string userInfo; //Path to all users.txt
};

#endif


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

	int SearchSite(string siteName); //Returns Index of sitename (-1 if site could not be found)
	string GetSiteNameAt(int index);
	string GetPasswordAt(int index);

	static bool FirstTimeOpen(); //Checks if all folders have been created for the program to run

	bool CheckUserExist(string username); //Checks if user is stored and exists *** Returns true/false if user exists/does-not
	bool CreateNewUser(string newUsername); //Stores user and creates all files for specific user

	bool StoreNewPassword(string siteName, string password);
private:
	/* 
		* Initialzed once user has logged in
		* A site and its password have the same index in siteNames and password vectors, respectivly
	*/
	vector<string> siteNames; //Vector of all sites stored				
	vector<string> passwords; //Vector of all stored passwords 

	string allUsersFilePath; //Path to all users.txt File
};

#endif


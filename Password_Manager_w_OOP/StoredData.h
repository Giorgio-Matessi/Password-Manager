#pragma once

/*
 *  Name:        StoredData.h
 *  Purpose:     Declarations for all data related functions and data members
 *  Author:      Giorgio Matessi
 *  Created:     06/25/22
 */


#ifndef STOREDDATA_H
#define STOREDDATA_H

#include <vector>
#include <iostream>
#include "User.h"

using namespace std;

class StoredData
{

public:
	StoredData();

	string GetSiteName(string siteName); //Gets Specific Site Name **** Returns site name or ' ' if site could not be found
	string GetSitePassword(string siteName); //Gets Specific Site Password **** Returns password or ' ' if site could not be found

	bool ChangeSpecificPassword(string siteName, string newPassword); //Changes a site password ****** Returns true if successful/false if site was not found

	static bool FirstTimeOpen(); //Checks if all folders have been created for the program to run

	bool CheckUserExists(string username); //Checks if user is stored and exists *** Returns true/false if user exists/does-not
	bool CreateNewUser(string newUsername); //Stores user and creates all files for specific user

	bool StoreNewPassword(string siteName, string password); //Add new site and password into vector
	bool GenerateAndStoreRandomPassword(string siteName, int passwordLength); //Creates random password of given length *** Returns false if site already exists; true if successful

	int LoadUserData(User user); //Load both stored site names and passwords from the file into vector **** Returns # of passwords loaded
	int SaveUserData(User user); //Write both stored site names and passwords from the vector into file **** Returns # of passwords written to file

	void BackupUserData(User user); //Copy password file into new file under User folder

private:

	int SearchForSite(string siteName); //Returns Index of sitename (-1 if site could not be found)
	string toLow(string inputString, int stringLength); //Takes string and makes all lowercase
	int split(string inputString, char separator, string arr[], int size); //Takes a line and splits into array based of delimiter
	static string GetDocumentsPath(); //Gets Computer Document Folder Path

	/* 
		* Initialzed once user has logged in
		* A site and its password have the same index in siteNames and password vectors, respectivly
	*/
	vector<string> siteNames; //Vector of all sites stored				
	vector<string> passwords; //Vector of all stored passwords 
	
	string allUsersFilePath; //Path to users.txt File
};

#endif


#pragma once

/*
 *  Name:        User.h
 *  Purpose:     Declarations for all user data and functions
 *  Author:      Giorgio Matessi
 *  Created:     06/20/22
 */


#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>

using namespace std;

class User
{
public:
	User(string inputUserName); //Constructor for a user instance **** Defines specific user file directories where data is stored and read

	//Getters for User:
	string GetUsername();
	string GetUserInfoDir();
	vector<string> GetSiteNames();
	vector<string> GetPasswords();

private:

	string username; //Defined once logged in/account made
	string userInfoDir; //Directory Address of User-System-Password/Stored Passwords ***** Initialized in User Constructor 

	/* 
		* Initialzed once user has logged in
		* A site and its password have the same index in siteNames and password vectors, respectivly
	*/
	vector<string> siteNames; //Vector of all sites stored				
	vector<string> passwords; //Vector of all stored passwords 
};

#endif USER_H




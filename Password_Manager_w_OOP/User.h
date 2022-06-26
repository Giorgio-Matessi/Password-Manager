#pragma once

/*
 *  Name:        User.h
 *  Purpose:     Declarations for all user data and functions
 *  Author:      Giorgio Matessi
 *  Created:     06/20/22
 */

#include <iostream>

#ifndef USER_H
#define USER_H

using namespace std;

class User
{
public:
	User(string inputUserName); //Constructor for a user instance **** Defines specific user file directories where data is stored and read

	//Getters for User:
	string GetUsername();
	string GetUserInfoDir(); 

private:

	string username; //Defined once logged in/account made
	string userInfoDir; //Path of User-System-Password/Stored Passwords ***** Initialized in User Constructor 

};

#endif USER_H




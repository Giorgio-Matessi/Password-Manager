/*
 *  Name:        main.cpp
 *  Purpose:     Password Manager Entry Point
 *  Author:      Giorgio Matessi
 *  Created:     06/20/22
 */

#include <iostream>
#include <string>
#include "User.h"
#include "Password.h"
#include "StoredData.h"


using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::vector;
using std::wstring;
using std::endl;

int main(int argc, char* argv[])
{
	StoredData StoredData;
	
	string introBanner = "\n----------------------PASSWORD MANAGER-----------------------\n-------------------------------------------------------------\n-------------------------------------------------------------\n";
	string mainBanner = "\n----------------------PASSWORD MANAGER-----------------------\n------------------- Stored Passwords: " + std::to_string(StoredData.GetNumPasswordsStored()) + "----------------------\n-------------------------------------------------------------\n";
	string mainMenuOptions = "1. Store New Password\n2. View Stored Password\n3. Change Specific Password\n4. Settings\n5. Save Data\n6. Exit";
	string storeNewPasswordOptions = "1. Generate Random Password\n2. Enter Custom Password";
	string settingsOptions = "1. Change System Password\n2. Backup Passwords\n3. Go Back";

	cout << introBanner;
	StoredData::FirstTimeOpen();
	
	cout << "\n1. Login\n2. Create Account\n3. Exit Program" << endl;
	int choice;
	string enteredUsername;
	cin >> choice;
	switch (choice)
	{
		case 1:
		{
			cout << "Please Enter Username: ";
			cin >> enteredUsername;
			while (!StoredData.CheckUserExists(enteredUsername))
			{
				//Create a New Account Option:
				char charChoice;
				cout << "Could Not Find User. Would You Like To Create An Account? [y/n]: ";
				cin >> charChoice;
				if (charChoice == 'y' || charChoice == 'Y')
				{
					cout << "Please Enter a New Username: ";
					cin >> enteredUsername;

					string enterAccountPassword;
					cout << "\nPlease Enter a System Password: ";
					cin >> enterAccountPassword;

					while (!StoredData.CreateNewUser(enteredUsername, enterAccountPassword))
					{
						cout << "Please Enter a New Username: ";
						cin >> enteredUsername;

						cout << "\nPlease Enter a System Password: ";
						cin >> enterAccountPassword;
					}
					break;
				}

				cin >> enteredUsername;
			}

			User foundUser(enteredUsername);

			string enteredPassword = "";
			cout << "Please Enter Account Password: ";
			cin >> enteredPassword;

			while (!Password::CheckPassword(foundUser, enteredPassword))
			{
				cout <<  "\nPassword Not Correct. Please Enter Correct Password: ";
				cin >> enteredPassword;
			}

			break;
		}

		case 2:
		{
			
			cout << "Please Enter a New Username: ";
			cin >> enteredUsername;

			string enterAccountPassword;
			cout << "\nPlease Enter a System Password: ";
			cin >> enterAccountPassword;

			while (!StoredData.CreateNewUser(enteredUsername, enterAccountPassword))
			{
				cout << "Please Enter a New Username: ";
				cin >> enteredUsername;

				cout << "\nPlease Enter a System Password: ";
				cin >> enterAccountPassword;
			}
			break;
		}
		case 3:
		{
			return 0;
		}
	}

	User loggedInUser(enteredUsername);
	StoredData.LoadUserData(loggedInUser);

	

	while (1)
	{
		mainBanner = "\n----------------------PASSWORD MANAGER-----------------------\n------------------- Stored Passwords: " + std::to_string(StoredData.GetNumPasswordsStored()) + "----------------------\n-------------------------------------------------------------\n";
		cout << mainBanner << mainMenuOptions << endl;
		cin >> choice; 

		switch (choice)
		{
			case 1:
			{
				cout << mainBanner << storeNewPasswordOptions << endl;
				cin >> choice;

				switch (choice)
				{
					case 1:
					{
						cout << mainBanner;
						string siteName = "";
						cout << "Please Enter Site Name: ";
						cin >> siteName;

						cout << "Please Enter Password Length: ";
						cin >> choice;

						StoredData.GenerateAndStoreRandomPassword(siteName, choice);

						break;
					}

					case 2:
					{
						cout << mainBanner ;
						string siteName = "";
						cout << "Please Enter Site Name: ";
						cin >> siteName;

						string enteredPassword;
						cout << "Please Enter Password For Site: ";
						cin >> enteredPassword;

						StoredData.StoreNewPassword(siteName, enteredPassword);

						break;
					}
				}
				break;
			}

			case 2:
			{
				cout << mainBanner;

				string enteredSite;
				cout << "Please Enter Site Name: ";
				cin >> enteredSite;

				StoredData.GetSitePassword(enteredSite);

				break;
			}
			
			case 3:
			{
				string enteredSite;
				cout << "Please Enter Site Name: ";
				cin >> enteredSite;

				string newPassword;
				cout << "Please Enter a New Site Password: ";
				cin >> newPassword;

				StoredData.ChangeSpecificPassword(enteredSite, newPassword);

				break;
			}
			
			case 4:
			{
				cout << mainBanner << settingsOptions << endl;
				cin >> choice;
				
				switch (choice)
				{
					case 1:
					{
						string enteredPassword;
						cout << "Please Enter A New System Password: ";
						cin >> enteredPassword;

						StoredData.SaveUserData(loggedInUser, 1, enteredPassword);
					}

					case 2:
					{
						StoredData.BackupUserData(loggedInUser);
						break;
					}

					case 3:
					{
						break;
					}

				}
			}

			case 5:
			{
				StoredData.SaveUserData(loggedInUser, 0, "");
				break;
			}

			case 6:
			{
				StoredData.SaveUserData(loggedInUser, 0, "");

				cout << "Goodbye.";
				cin.ignore();
				cin.ignore();
				return 0;
			}
		}
	}
}

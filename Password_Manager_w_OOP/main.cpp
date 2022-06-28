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

	while (!(cin >> choice)) {
		cout << "\nInvalid Input." << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	switch (choice)
	{
		case 1:
		{
			cout << "\nPlease Enter Username: ";

			while (!(cin >> enteredUsername)) {
				cout << "\nInvalid Input." << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			while (!StoredData.CheckUserExists(enteredUsername))
			{
				
				//Create a New Account Option:
				char charChoice;
				cout << "\nCould Not Find User. Would You Like To Create An Account? [y/n]: ";

				while (!(cin >> charChoice)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				if (charChoice == 'y' || charChoice == 'Y')
				{
					cout << "\nPlease Enter a New Username: ";

					while (!(cin >> enteredUsername)) {
						cout << "\nInvalid Input." << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}

					string enterAccountPassword;
					cout << "\nPlease Enter a System Password: ";

					while (!(cin >> enterAccountPassword)) {
						cout << "\nInvalid Input." << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}

					while (!StoredData.CreateNewUser(enteredUsername, enterAccountPassword))
					{
						cout << "Please Enter a New Username: ";

						while (!(cin >> enteredUsername)) {
							cout << "\nInvalid Input." << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}

						cout << "\nPlease Enter a System Password: ";

						while (!(cin >> enterAccountPassword)) {
							cout << "\nInvalid Input." << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}
					break;
				}
				cout << "\nPlease Enter Username: ";
				while (!(cin >> enteredUsername)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

			}

			User foundUser(enteredUsername);

			string enteredPassword = "";
			cout << "Please Enter Account Password: ";
			cin >> enteredPassword;

			while (!(cin >> enteredPassword)) {
				cout << "\nInvalid Input." << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			while (!Password::CheckPassword(foundUser, enteredPassword))
			{
				cout <<  "\nPassword Not Correct. Please Enter Correct Password: ";

				while (!(cin >> enteredPassword)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}

			break;
		}

		case 2:
		{
			
			cout << "\nPlease Enter a New Username: ";

			while (!(cin >> enteredUsername)) {
				cout << "\nInvalid Input." << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			string enterAccountPassword;
			cout << "\nPlease Enter a System Password: ";

			while (!(cin >> enterAccountPassword)) {
				cout << "\nInvalid Input." << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			while (!StoredData.CreateNewUser(enteredUsername, enterAccountPassword))
			{
				cout << "Please Enter a New Username: ";

				while (!(cin >> enteredUsername)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				cout << "\nPlease Enter a System Password: ";

				while (!(cin >> enterAccountPassword)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
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

		while (!(cin >> choice)) {
			cout << "\nInvalid Input." << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		switch (choice)
		{
			case 1:
			{
				cout << mainBanner << storeNewPasswordOptions << endl;

				while (!(cin >> choice)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				switch (choice)
				{
					case 1:
					{
						string siteName = "";
						cout << "\nPlease Enter Site Name: ";

						while (!(cin >> siteName)) {
							cout << "\nInvalid Input." << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}

						cout << "Please Enter Password Length: ";

						while (!(cin >> choice)) {
							cout << "\nInvalid Input." << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}

						StoredData.GenerateAndStoreRandomPassword(siteName, choice);

						break;
					}

					case 2:
					{
						string siteName = "";
						cout << "\nPlease Enter Site Name: ";

						while (!(cin >> siteName)) {
							cout << "\nInvalid Input." << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}

						string enteredPassword;
						cout << "Please Enter Password For Site: ";

						while (!(cin >> enteredPassword)) {
							cout << "\nInvalid Input." << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}

						StoredData.StoreNewPassword(siteName, enteredPassword);

						break;
					}
				}
				break;
			}

			case 2:
			{

				string enteredSite;
				cout << "\nPlease Enter Site Name: ";

				while (!(cin >> enteredSite)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				StoredData.GetSitePassword(enteredSite);

				break;
			}
			
			case 3:
			{
				string enteredSite;
				cout << "\nPlease Enter Site Name: ";

				while (!(cin >> enteredSite)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				string newPassword;
				cout << "Please Enter a New Site Password: ";

				while (!(cin >> newPassword)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				StoredData.ChangeSpecificPassword(enteredSite, newPassword);

				break;
			}
			
			case 4:
			{
				cout << mainBanner << settingsOptions << endl;

				while (!(cin >> choice)) {
					cout << "\nInvalid Input." << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				
				switch (choice)
				{
					case 1:
					{
						string enteredPassword;
						cout << "\nPlease Enter A New System Password: ";

						while (!(cin >> enteredPassword)) {
							cout << "\nInvalid Input." << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}

						StoredData.SaveUserData(loggedInUser, 1, enteredPassword);
						break;
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
				break;
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

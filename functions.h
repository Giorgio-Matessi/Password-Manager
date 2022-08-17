#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <conio.h>
#include <direct.h>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;


string encryptPass(string password)
{
    for (int i = 0; i < password.size(); i++)
    {
        password[i] = (char)((int)password[i] + 15);
    }

    return password;
}

string decryptPass(string password)
{
    for (int i = 0; i < password.size(); i++)
    {
        password[i] = (char)((int)password[i] - 15);
    }

    return password;
}

string toLow(string inputString, int stringLength)
{
    for (int i = 0; i < stringLength; i++)
    {
        inputString[i] = tolower(inputString[i]);
    }

    return inputString;
}

int split(string inputString, char separator, string arr[], int size) {
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
}

string userNameEntry(string userFile) 
{   
    
    bool done = false;

    while (1)
    {
        int choice=0;
        cout << "1. Login\n2. Create Account" << endl;
        cin >> choice;
    
        string enteredUsername="";
        switch (choice)
        {
            case 1:
            {
                cout << endl << "Please Enter Username (case sensitive):" << endl;
                cin >> enteredUsername;

                ifstream fin;
                string temp;
                fin.open(userFile);

                while (!fin.eof())
                {
                    getline(fin, temp);

                    if (temp != "")
                    {
                        if (temp == enteredUsername)
                        {
                            cin.ignore();
                            return enteredUsername;
                        }
                    }
                }

                fin.close();
                cout << endl << "User could not be found." << endl;
                break;
            }

            case 2:
            {
                cout << endl << "Please Enter New Username: ";
                cin >> enteredUsername;
                bool found = false;
                string temp;

                ifstream fin;
                fin.open(userFile);

                while (!fin.eof())
                {
                    getline(fin, temp);
                    if (temp == enteredUsername)
                    {
                        found = true;

                    }
                }

                fin.close();
                
                if (found == false)
                {
                    ofstream fout;
                    fout.open(userFile, ios::app);
                    fout << enteredUsername << endl;
                    fout.close();
                    string path = "C:\\Users\\giorg\\Documents\\Password_Manager\\User_Folders\\" + enteredUsername;
                    fs::create_directory(path);
                    cin.ignore();
                    return enteredUsername;
                }
                else
                {
                    cout << endl << "User Already Exists." << endl;
                    cin.ignore();
                    cin.ignore();
                }
                    
            }
        }
    }
}

string generatePassword(int inputLength) {
    char lowerCase[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
    char upperCase[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
    char special[] = {'!', '”', '#', '$', '%', '&', '’', '(',  ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '~', '{', '|', '}'};
    srand(time(NULL));
    string password = "";
    int rLowerUpper;
    int rSpecial;
    int rRan;

    for (int i = 0; i < inputLength; i++)
    {
        rRan = rand() % 300;

        //lowerCase
        if (rRan < 100)
        {
            rLowerUpper = rand() % 25 + 1;

            password = password + lowerCase[rLowerUpper];
        }
        //upperCase
        else if (rRan >= 100 && rRan < 200)
        {
            rLowerUpper = rand() % 25 + 1;
            password = password + upperCase[rLowerUpper];
        }
        //special
        else if (rRan >= 200 && rRan < 300)
        {
            rSpecial = rand() % 31;
            password = password + special[rSpecial];
        }
    }

    return password;
}

void entryPass(string inputSysPassFile, string username)
{
    string entryPassword = "", systemPassword;
    bool passwordCheck = true;
    ifstream fin;
    fin.open(inputSysPassFile);
    getline(fin, systemPassword);
    fin.close();

    if (decryptPass(systemPassword) == "" || decryptPass(systemPassword) == " ")
    {
        cout << endl << "Hello, " << username << ". Please Enter a New System Password." << endl;
        ofstream fout;
        fout.open(inputSysPassFile);
        cin >> systemPassword;
        fout << encryptPass(systemPassword);
        fout.close();
        cin.ignore();
    }


    while (passwordCheck == true)
    {
        cout << endl << "Please Enter Password:" << endl;
        getline(cin, entryPassword);

        fin.open(inputSysPassFile);
        getline(fin, systemPassword);
        fin.close();

        if (entryPassword == decryptPass(systemPassword))
        {
            passwordCheck = false;
        }
    }
}

int populateData(vector<string>& inputNames, vector<string>& inputPasswords, string inputPassFile)
{
    string tempString = "";
    string arr[2];
    ifstream readPasswordFile;
    readPasswordFile.open(inputPassFile);
    int passwordCount = 0;

    if (readPasswordFile.is_open())
    {
        while (!readPasswordFile.eof())
        {
            getline(readPasswordFile, tempString);
            if (tempString != "")
            {
                split(tempString, ',', arr, 2);
                inputNames.push_back(arr[0]);
                inputPasswords.push_back(decryptPass(arr[1]));
                passwordCount++;
            }

        }
    }
    readPasswordFile.close();
    return passwordCount;
}

int generatePassword(vector<string>& inputNames, vector<string>& inputPasswords, string inputPassFile)
{
    ofstream fout;
    ifstream fin;
    bool checkDup = false;
    string siteName = "", createdPassword = "", temp, arr[2];
    int passLength;
    cout << endl << "Enter Site Name: ";
    cin >> siteName;

    //Check Duplicate:
    for (int i = 0; i < inputNames.size(); i++)
    {
        if (toLow(siteName, siteName.length()) == toLow(inputNames[i], inputNames[i].length()))
        {
            checkDup = true;
            break;
        }
    }

    //Write to File if it Doesn't Exist:
    if (checkDup == false)
    {
        cout << "Enter Password Length: ";
        cin >> passLength;

        createdPassword = generatePassword(passLength);

        cout << endl << "Your Password for " << siteName << " is: " << createdPassword << endl;
        cout << "It has been stored." << endl;

        fout.open(inputPassFile, ios::app);
        fout << siteName << "," << encryptPass(createdPassword);
        fout << endl;
        inputNames.push_back(siteName);
        inputPasswords.push_back(createdPassword);
        fout.close();
        cin.ignore();
        cin.ignore();
        return 1;
    }
    else
    {
        checkDup = false;
        cout << "Site Password Already Exists." << endl;
        cin.ignore();
        cin.ignore();
        return 0;
    }
}

void viewStoredPasswords(vector<string>& inputNames, vector<string>& inputPasswords, string inputPassFile)
{
    string siteSearch;
    int siteSearchChoice;
    bool siteSearchComplete = false;
    if (inputNames.size() == 0)
    {
        cout << endl << "No Passowords Stored.";
        cin.ignore();
        cin.ignore();
        return;
    }
    while (siteSearchComplete != true)
    {
        siteSearchComplete = false;
        cout << endl << "1. Search\n2. Go Back" << endl;
        cin >> siteSearchChoice;

        

        switch (siteSearchChoice)
        {
        case 1:
        {
            int siteIndex;
            cout << endl << "Enter Site: ";
            cin >> siteSearch;

            for (int i = 0; i < inputNames.size(); i++)
            {
                if (toLow(siteSearch, siteSearch.length()) == toLow(inputNames[i], inputNames[i].length()))
                {
                    siteIndex = i;
                    siteSearchComplete = true;
                }
            }

            if (siteSearchComplete == true)
            {
                cout << endl << "The password for " << inputNames[siteIndex] << " is " << inputPasswords[siteIndex] << endl;
                cin.ignore();
                cin.ignore();
                break;
            }
            else
            {
                cout << endl << "Could not Find Site." << endl;
                break;
            }
        }

        case 2:
        {
            siteSearchComplete = true;
            break;
        }
        }

    }

}

void changeSysPassword(string inputSysPassFile, string username)
{
    //Re-Ask Current System Password:
    cin.ignore();
    entryPass(inputSysPassFile, username);

    ofstream fout;
    fout.open(inputSysPassFile);
    string newSysPass = "";
    cout << "Please Enter a New System Password:" << endl;
    getline(cin, newSysPass);
    fout << encryptPass(newSysPass);

    cout << "New system password has been set." << endl;

}

int settings(vector<string>& inputNames, vector<string>& inputPasswords, string inputPassFile, string inputSysPassFile, string username)
{
    int settingsChoice;

    cout << endl << "1. Change System Password\n2. Backup Passwords\n3. Factory Reset\n4. Go Back" << endl;
    cin >> settingsChoice;

    switch (settingsChoice)
    {
    case 1:
    {
        changeSysPassword(inputSysPassFile, username);
        break;
    }

    case 2:
    {
        string tempChar;
        cout << endl << "Are you sure you would like to continue? [y/n]" << endl;
        cin >> tempChar;
        if (toLow(tempChar, 1) == "y")
        {
            ofstream fout;
            string path = "C:\\Users\\giorg\\Desktop\\" + username + "Backup_File.txt";
            fout.open(path);
            for (int i = 0; i < inputNames.size(); i++)
            {
                fout << inputNames[i] << "," << encryptPass(inputPasswords[i]) << endl;
            }
            fout.close();

            cout << endl << "A Backup File Has Been Created Under the Name: 'Backup_File.txt' and Placed on Your Desktop." << endl;
            cin.ignore();
            cin.ignore();
            return 1;
        }
        else
        {
            return 1;
        }
    }

    case 3:
    {
        cin.ignore();
        cout << endl;
        entryPass(inputSysPassFile, username);
        string tempChar;
        cout << endl << "This will delete all files and reset the system password. This is irreversible. Are you sure you would like to continue? [y/n]" << endl;
        cin >> tempChar;

        if (toLow(tempChar, 1) == "y")
        {
            ofstream fout;
            fout.open(inputPassFile);
            fout << "";
            fout.close();

            fout.open(inputSysPassFile);
            fout << "";
            fout.close();

            inputNames.clear();
            inputPasswords.clear();

            cout << endl << "The Program Will Close." << endl;

            cin.ignore();
            cin.ignore();
            return 0;
        }
        else
        {
            break;
        }
    }

    case 4:
    {
        return 1;
    }
    }
    return 1;
}

void changeSpecificPass(vector<string>& storedSiteNames, vector<string>& storedPasswords, string passwordsFile)
{

    string siteSearch;
    int siteIndex;
    int siteSearchChoice;
    bool siteSearchComplete = false;


    while (!siteSearchComplete)
    {
        cout << endl << "1. Search for Site\n2. Go Back" << endl;
        cin >> siteSearchChoice;

        switch (siteSearchChoice)
        {

        case 1:
        {
            cout << endl << "Enter Site: ";
            cin >> siteSearch;

            for (int i = 0; i < storedSiteNames.size(); i++)
            {
                if (toLow(siteSearch, siteSearch.length()) == toLow(storedSiteNames[i], storedSiteNames[i].length()))
                {
                    siteIndex = i;
                    siteSearchComplete = true;
                }
            }

            string newPassword;
            if (siteSearchComplete == true)
            {
                cout << endl << "Choose New Password for " << storedSiteNames[siteIndex] << ":" << endl;

                cin >> newPassword;
                storedPasswords[siteIndex] = newPassword;

                ofstream fout;
                fout.open(passwordsFile);

                for (int i = 0; i < sizeof(storedSiteNames); i++)
                {
                    fout << "" << endl;
                }

                fout.close();

                fout.open(passwordsFile);

                for (int i = 0; i < storedSiteNames.size(); i++)
                {
                    fout << storedSiteNames[i] << "," << encryptPass(storedPasswords[i]) << endl;
                }


                fout.close();

                cout << "Password Has Been Changed." << endl;
                cin.ignore();
                cin.ignore();

                break;
            }
            else
            {
                cout << "Could not Find Site." << endl;
                cin.ignore();
                cin.ignore();
                break;
            }
        }

        case 2:
        {
            return;
        }

        }
    }
    return;
}

void mainMenu(vector<string>& storedSiteNames, vector<string>& storedPasswords, string passwordsFile, string systemPasswordFile, int passwordCount, string username)
{
    int menuChoice; \


        cout << "\n----------------------PASSWORD MANAGER-----------------------\n------------------- Stored Passwords: " << passwordCount << "----------------------\n-------------------------------------------------------------\n1. Generate New Password\n2. View Stored Password\n3. Change Specific Password\n4. Settings\n5. Exit" << endl;

    cin >> menuChoice;

    switch (menuChoice)
    {
    case 1:
    {
        int creationSucess;

        creationSucess = generatePassword(storedSiteNames, storedPasswords, passwordsFile);

        if (creationSucess == 1)
        {
            passwordCount++;
        }

        break;
    }

    case 2:
    {
        viewStoredPasswords(storedSiteNames, storedPasswords, passwordsFile);
        break;
    }

    case 3:
    {
        changeSpecificPass(storedSiteNames, storedPasswords, passwordsFile);
        break;
    }

    case 4:
    {
        int checkReset = settings(storedSiteNames, storedPasswords, passwordsFile, systemPasswordFile, username);

        if (checkReset == 0)
        {
            return;
        }

        break;
    }

    case 5:
    {
        return;
    }
    }
    mainMenu(storedSiteNames, storedPasswords, passwordsFile, systemPasswordFile, passwordCount, username);
}


#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "functions.h"
 
/* Program List:

1. Settings Option:
    1. Factory Reset----Complete----
    2. Change System Password----Complete----

2. Backup Passwords to New File----Complete----

3. More Secure System Password----Complete----

4. Graphical Interface----Not Yet Complete----

5. Give Password Security Level----Not Yet Complete----

6. Change Specific Password----Complete----

7. System Password Hint----Not Yet Complete----

8. Stress Test----Complete(Success)----

9. Multiple Users----Complete----

10. Check for Incorrect Input ----Not Yet Complete----
*/

using namespace std;


int main()
{
    //Initialize Instance Variables:
    string userFile = "C:\\Users\\giorg\\Documents\\Password_Manager\\users.txt";
    string systemPasswordFile = "C:\\Users\\giorg\\Documents\\Password_Manager\\User_Folders\\";
    string passwordsFile = "C:\\Users\\giorg\\Documents\\Password_Manager\\User_Folders\\";
    vector<string> storedSiteNames;
    vector<string> storedPasswords;
    int passwordCount=0;
    string username = "";


    //Username:
    username = userNameEntry(userFile);
    systemPasswordFile = systemPasswordFile + username + "\\" + "SystemPassword.txt";
    passwordsFile = passwordsFile + username + "\\" + "Passwords.txt";
    

    //User Password:
    entryPass(systemPasswordFile,username);

    //Populate Passwords/Site Name Vector:
    passwordCount = populateData(storedSiteNames, storedPasswords, passwordsFile);

    //Main Menu:
    mainMenu(storedSiteNames, storedPasswords, passwordsFile, systemPasswordFile, passwordCount, username);

    return 0;
}
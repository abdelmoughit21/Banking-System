#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;



const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";



enum enMenuChoices { ShowClientsList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Transactions = 6, ManageUsers = 7, Logout = 8 };

enum enTransactionsMenuChoice { Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4 };

enum enManageUsersMenuChoice { ListUsers = 1, AddNewUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5 , MainMenu1 = 6 };

enum enMainMenuPermissions { pAll = -1 , pShowClientsList = 1 , pAddNewClient = 2 , pDeleteClient = 4 , pUpdateClient = 8 , pFindClient = 16 , pTransactions = 32 , pManageUsers = 64 };

struct stClient {

    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    int AccountBalance;
    bool MarkedForDelete = false;

};

struct stUser {

    string username;
    string password;
    short permission = 0;
    bool MarkedForDelete = false;

};

stUser CurrentUser;



bool CheckAccessPermission(enMainMenuPermissions Permission) {

    if (CurrentUser.permission == enMainMenuPermissions::pAll)
        return true;

    if ((Permission & CurrentUser.permission) == Permission)
        return true;
    else
        return false;

}


string ReadString(string message) {

    string text = "";

    cout << message;
    getline(cin >> ws, text);

    return text;

}

float ReadPositiveNumber(string message) {

    float num = 0;

    do {

        cout << message;
        cin >> num;

    } while (num <= 0);

    return num;

}

enMenuChoices ReadMenuChoices(string message) {

    short choice = 0;

    do {

        cout << message;
        cin >> choice;

    } while (choice < 1 || choice > 8);

    return (enMenuChoices)choice;

}

enTransactionsMenuChoice ReadTransactionsMenuChoices(string message) {

    short choice = 0;

    do {

        cout << message;
        cin >> choice;

    } while (choice < 1 || choice > 4);

    return (enTransactionsMenuChoice)choice;

}

enManageUsersMenuChoice ReadManageUsersMenuChoices(string message) {

    short choice = 0;

    do {

        cout << message;
        cin >> choice;

    } while (choice < 1 || choice > 6);

    return enManageUsersMenuChoice(choice);

}





void PrintClientRecord(stClient Client) {

    cout << "| " << left << setw(20) << Client.AccountNumber;
    cout << "| " << left << setw(17) << Client.PinCode;
    cout << "| " << left << setw(34) << Client.Name;
    cout << "| " << left << setw(15) << Client.Phone;
    cout << "| " << left << setw(15) << Client.AccountBalance;

}

void PrintClientCard(stClient Client) {

    cout << "\nThe following are the client details : ";
    cout << "\n------------------------------------------";
    cout << "\nAccount Number       : " << Client.AccountNumber;
    cout << "\nPin Code             : " << Client.PinCode;
    cout << "\nName                 : " << Client.Name;
    cout << "\nPhone                : " << Client.Phone;
    cout << "\nAccount Balance      : " << Client.AccountBalance;
    cout << "\n------------------------------------------\n";

}


void LoginHeader() {

    cout << "\n------------------------------------------------------\n";
    cout << "\t\t\tLogin Screen";
    cout << "\n------------------------------------------------------\n\n";

}


void AddNewClientHeader() {

    cout << "\n------------------------------------------------------\n";
    cout << "\t\tAdd New Clients Screen";
    cout << "\n------------------------------------------------------\n\n";

}
void DeleteClientHeader() {

    cout << "\n------------------------------------------------------\n";
    cout << "\t\tDelete Client Screen";
    cout << "\n------------------------------------------------------\n\n";

}
void UpdateClientInfoHeader() {

    cout << "\n----------------------------------------------------------------\n";
    cout << "\t\tUpdate Client Info Screen";
    cout << "\n----------------------------------------------------------------\n\n";

}
void FindClientScreenHeader() {

    cout << "\n--------------------------------------------------------\n";
    cout << "\t\tFind Client Screen";
    cout << "\n--------------------------------------------------------\n\n";

}



vector <string> SplitString(string S1, string Seperator = "#//#") {

    vector <string> vString;

    string word = "";
    short pos = 0;

    while ((pos = S1.find(Seperator)) != string::npos) {

        word = S1.substr(0, pos);

        if (word != "")
            vString.push_back(word);

        S1.erase(0, pos + Seperator.length());

    }

    if (S1 != "")
        vString.push_back(S1);

    return vString;

}



// Clients

stClient ConvertLineToRecord(string LineRecord, string Seperator = "#//#") {

    stClient Client;
    vector <string> vString;

    vString = SplitString(LineRecord, Seperator);

    Client.AccountNumber = vString[0];
    Client.PinCode = vString[1];
    Client.Name = vString[2];
    Client.Phone = vString[3];
    Client.AccountBalance = stoi(vString[4]);

    return Client;

}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#") {

    string stClientRecord;

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

void AddRecordToFile(string FileName, stClient Client) {

    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open()) {

        string Line = "";

        Line = ConvertRecordToLine(Client);

        MyFile << Line << endl;

        MyFile.close();

    }

}

vector <stClient> LoadClientsDataFromFile(string FileName) {

    vector <stClient> vClients;

    stClient Client;

    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {

        string Line;

        while (getline(MyFile, Line)) {

            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);

        }

        MyFile.close();

    }

    return vClients;

}

bool IsClientExist(string AccountNumber, vector <stClient> vClients) {

    for (stClient& Client : vClients) {

        if (Client.AccountNumber == AccountNumber)
            return true;

    }

    return false;

}

bool IsClientExist(string AccountNumber, vector <stClient> vClients, stClient& Client1) {

    for (stClient& Client : vClients) {

        if (Client.AccountNumber == AccountNumber) {

            Client1 = Client;
            return true;

        }

    }

    return false;

}


// Users


void PrintUserRecord(stUser User) {

    cout << "| " << left << setw(20) << User.username;
    cout << "| " << left << setw(17) << User.password;
    cout << "| " << left << setw(34) << User.permission;

}

void PrintUserCard(stUser User) {

    cout << "\nThe following are the user details : ";
    cout << "\n------------------------------------------";
    cout << "\nUsername       : " << User.username;
    cout << "\nPassword       : " << User.password;
    cout << "\nPermissions    : " << User.permission;
    cout << "\n------------------------------------------\n";

}



void AddNewUserHeader() {

    cout << "\n------------------------------------------------------\n";
    cout << "\t\tAdd New Users Screen";
    cout << "\n------------------------------------------------------\n\n";

}

void DeleteUserHeader() {

    cout << "\n------------------------------------------------------\n";
    cout << "\t\tDelete Users Screen";
    cout << "\n------------------------------------------------------\n\n";

}

void UpdateUserInfoHeader() {

    cout << "\n------------------------------------------------------\n";
    cout << "\t\tUpdate Users Screen";
    cout << "\n------------------------------------------------------\n\n";

}

void FindUserHeader() {

    cout << "\n------------------------------------------------------\n";
    cout << "\t\tFind User Screen";
    cout << "\n------------------------------------------------------\n\n";

}



stUser ConverUserLineToRecord(string S1, string Seperator = "#//#") {

    stUser User;

    vector <string> vUsers;

    vUsers = SplitString(S1, Seperator);

    User.username = vUsers[0];
    User.password = vUsers[1];
    User.permission = stoi(vUsers[2]);

    return User;

}

string ConvertUserRecordToLine(stUser User , string Seperator = "#//#") {

    string strRecordLine;

    strRecordLine += User.username + Seperator;
    strRecordLine += User.password + Seperator;
    strRecordLine += to_string(User.permission);

    return strRecordLine;

}

vector <stUser> LoadUsersDataFromFile(string FileName) {

    vector <stUser> vUsers;

    stUser User;

    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
    
        string Line = "";

        while (getline(MyFile, Line)) {

            User = ConverUserLineToRecord(Line);
            vUsers.push_back(User);

        }
    
        MyFile.close();
    
    }
  
    return vUsers;

}

bool FindUserByUsernameAndPassword(string username, string password , stUser &User1) {

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (stUser& User : vUsers) {

        if (User.username == username && User.password == password) {

            User1 = User;
            return true;

        }

    }

    return false;

}

void SaveUsersDataToFile(string FileName, vector <stUser> vUsers) {

    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {

        string Line = "";

        for (stUser& User : vUsers) {

            if (!User.MarkedForDelete) {
            
                Line = ConvertUserRecordToLine(User);
                MyFile << Line << endl;
            
            }

        }

        MyFile.close();

    }

}

bool IsUserExist(string username, vector <stUser> vUsers, stUser& User1) {

    for (stUser& User : vUsers) {

        if (User.username == username) {

            User1 = User;
            return true;

        }

    }

    return false;

}

bool MarkUserForDelete(string username, vector <stUser> &vUsers) {

    for (stUser& User : vUsers) {

        if (User.username == username) {

            User.MarkedForDelete = true;
            return true;

        }

    }

    return false;

}




void GoBackToTranscationsMenuScreen();
void GoBackToManageUsersMenuScreen();
void GoBackToMainMenu();


void AccessDeniedScreen() {

    cout << "\n------------------------------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You don't have permission to do this,\n";
    cout << "Please contact your Admin.\n";
    cout << "\n------------------------------------------------------\n\n";

    GoBackToMainMenu();

}


void ShowClientsListScreen() {

    if (!CheckAccessPermission(enMainMenuPermissions::pShowClientsList)) {

        system("cls");
        system("color 0f");
        AccessDeniedScreen();

    }

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n-----------------------------------------------------------------------------------------------------------\n";
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s)." << endl;
    cout << "\n-----------------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(20) << "Account Number";
    cout << "| " << left << setw(17) << "Pin Code";
    cout << "| " << left << setw(34) << "Client Name";
    cout << "| " << left << setw(15) << "Phone";
    cout << "| " << left << setw(15) << "Balance";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------\n\n";

    for (stClient& Client : vClients) {

        PrintClientRecord(Client);

        cout << endl;

    }

    cout << "\n\n-----------------------------------------------------------------------------------------------------------\n";

    GoBackToMainMenu();

}





stClient ReadNewClient(vector <stClient>& vClients) {

    stClient Client;
    char answer;

    cout << "Adding New Client : ";

    cout << "\n\nEnter Account Number : ";
    getline(cin >> ws, Client.AccountNumber);

    while (IsClientExist(Client.AccountNumber, vClients)) {

        cout << "\n\nClient with [" << Client.AccountNumber << "] already exists, Enter another account number : ";
        getline(cin >> ws, Client.AccountNumber);

    }

    cout << "\nEnter PinCode : ";
    getline(cin >> ws, Client.PinCode);

    cout << "\nEnter Name : ";
    getline(cin >> ws, Client.Name);

    cout << "\nEnter Phone : ";
    getline(cin >> ws, Client.Phone);

    cout << "\nEnter Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;

}

void AddNewClient1() {

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    stClient Client;
    char answer;

    do {

        system("cls");
        AddNewClientHeader();

        Client = ReadNewClient(vClients);

        AddRecordToFile(ClientsFileName, Client);

        vClients = LoadClientsDataFromFile(ClientsFileName);

        cout << "Client added successfully, do you want to add more : (Y/N) : ";
        cin >> answer;

    } while (toupper(answer) == 'Y');

}

void AddNewClientScreen() {

    if (!CheckAccessPermission(enMainMenuPermissions::pAddNewClient)) {

        system("cls");
        system("color 0f");
        AccessDeniedScreen();

    }

    AddNewClient1();
    GoBackToMainMenu();

}


void SaveClientsDataToFile(string FileName, vector <stClient> vClients) {

    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {

        string Line;

        for (stClient& Client : vClients) {

            if (Client.MarkedForDelete == false) {

                Line = ConvertRecordToLine(Client);
                MyFile << Line << endl;

            }

        }

        MyFile.close();

    }

}

void MarkClientForDelete(string AccountNumber, vector <stClient>& vClients) {

    for (stClient& Client : vClients) {

        if (Client.AccountNumber == AccountNumber) {

            Client.MarkedForDelete = true;
            return;
        }

    }

}

void DeleteClient1() {

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    stClient Client;
    char answer;
    string AccountNumber;

    AccountNumber = ReadString("Please enter Account Number : ");

    if (IsClientExist(AccountNumber, vClients, Client)) {

        PrintClientCard(Client);

        cout << "Are you sure you want to delete this client : (Y/N) : ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            MarkClientForDelete(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "\nClient deleted successfully.";
        }

    }
    else {

        cout << "\nClient with Account Number (" << AccountNumber << ") is not found!";

    }


}

void DeleteClientScreen() {

    if (!CheckAccessPermission(enMainMenuPermissions::pDeleteClient)) {

        system("cls");
        system("color 0f");
        AccessDeniedScreen();

    }

    DeleteClientHeader();
    DeleteClient1();
    GoBackToMainMenu();

}



stClient ReadUpdatedClient(string AccountNumber) {

    stClient Client;

    Client.AccountNumber = AccountNumber;

    Client.PinCode = ReadString("\nEnter Pin Code : ");
    Client.Name = ReadString("\nEnter Name : ");
    Client.Phone = ReadString("\nEnter Phone : ");
    Client.AccountBalance = stoi(ReadString("\nEnter Account Balance : "));

    return Client;

}

void UpdateClient1() {

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    stClient Client;
    char answer;
    string AccountNumber = ReadString("Please enter Account Number : ");

    if (IsClientExist(AccountNumber, vClients, Client)) {

        PrintClientCard(Client);

        cout << "Are you sure you want to update this client : (Y/N) : ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            for (stClient& Client : vClients) {

                if (Client.AccountNumber == AccountNumber) {

                    Client = ReadUpdatedClient(AccountNumber);

                }

            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "\nClient Updated successfully.";
        }

    }
    else {

        cout << "\nClient with Account Number (" << AccountNumber << ") is not found!";

    }

}

void UpdateClientInfoScreen() {

    if (!CheckAccessPermission(enMainMenuPermissions::pUpdateClient)) {

        system("cls");
        system("color 0f");
        AccessDeniedScreen();

    }

    UpdateClientInfoHeader();
    UpdateClient1();
    GoBackToMainMenu();

}



void FindClient1() {

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    stClient Client;
    string AccountNumber = ReadString("Please enter Account Number : ");

    if (IsClientExist(AccountNumber, vClients, Client)) {

        PrintClientCard(Client);

    }
    else {

        cout << "\nClient with Account Number (" << AccountNumber << ") is not found!";

    }

}

void FindClientScreen() {

    if (!CheckAccessPermission(enMainMenuPermissions::pFindClient)) {

        system("cls");
        system("color 0f");
        AccessDeniedScreen();

    }

    FindClientScreenHeader();
    FindClient1();
    GoBackToMainMenu();

}




void ExitScreen() {

    cout << "\n------------------------------------------------------\n";
    cout << "\t\tProgram Ends :-)";
    cout << "\n------------------------------------------------------\n\n";

}


// Bank Extension

void DepositScreenHeader() {

    cout << "\n-----------------------------------------------\n";
    cout << "\t\tDeposit Screen";
    cout << "\n-----------------------------------------------\n\n";

}

void PerformDepositOperation(string AccountNumber, float DepositAmount, vector <stClient>& vClients, stClient& Client) {

    for (stClient& Client1 : vClients) {

        if (Client1.AccountNumber == AccountNumber) {

            Client1.AccountBalance += DepositAmount;
            Client = Client1;
            return;

        }

    }

}

void DepositOperation() {

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    stClient Client;
    char answer;
    float depositAmount = 0;
    string AccountNumber = ReadString("Please enter Account Number : ");

    while (!IsClientExist(AccountNumber, vClients, Client)) {

        cout << "\nClient with [" << AccountNumber << "] does not exist.";
        AccountNumber = ReadString("\nPlease enter Account Number : ");

    }

    PrintClientCard(Client);

    depositAmount = ReadPositiveNumber("\nPlease enter deposit amount : ");

    cout << "\nAre you sure you want to perform this transaction : (Y/N) : ";
    cin >> answer;

    if (toupper(answer) == 'Y') {

        PerformDepositOperation(AccountNumber, depositAmount, vClients, Client);
        SaveClientsDataToFile(ClientsFileName, vClients);

        cout << "\nTransaction done successfully, new balance is " << Client.AccountBalance << endl;

    }

}

void ShowDepositScreen() {

    DepositScreenHeader();
    DepositOperation();
    GoBackToTranscationsMenuScreen();

}




void WithdrawScreenHeader() {

    cout << "\n-----------------------------------------------\n";
    cout << "\t\tWithdraw Screen";
    cout << "\n-----------------------------------------------\n\n";

}

void WithdrawOperation() {

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    stClient Client;
    char answer;
    float withdrawAmount = 0;
    string AccountNumber = ReadString("Please enter Account Number : ");

    while (!IsClientExist(AccountNumber, vClients, Client)) {

        cout << "\nClient with [" << AccountNumber << "] does not exist.";
        AccountNumber = ReadString("\nPlease enter Account Number : ");

    }

    PrintClientCard(Client);

    withdrawAmount = ReadPositiveNumber("\nPlease enter withdraw amount : ");

    while (withdrawAmount > Client.AccountBalance) {

        cout << "\nAmount exceeds the balance, you can withdraw up to : " << Client.AccountBalance;
        withdrawAmount = ReadPositiveNumber("\nPlease enter another amount : ");

    }

    cout << "\nAre you sure you want to perform this transaction : (Y/N) : ";
    cin >> answer;

    if (toupper(answer) == 'Y') {

        PerformDepositOperation(AccountNumber, withdrawAmount * (-1), vClients, Client);
        SaveClientsDataToFile(ClientsFileName, vClients);

        cout << "\nTransaction done successfully, new balance is " << Client.AccountBalance << endl;

    }

}

void ShowWithdrawScreen() {

    WithdrawScreenHeader();
    WithdrawOperation();
    GoBackToTranscationsMenuScreen();

}



void PrintClientTotalBalancesRecord(stClient Client) {

    cout << "| " << left << setw(27) << Client.AccountNumber;
    cout << "| " << left << setw(44) << Client.Name;
    cout << "| " << left << setw(30) << Client.AccountBalance;

}

void ShowTotalBalancesScreen() {

    int TotalBalance = 0;

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n-----------------------------------------------------------------------------------------------------------\n";
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s)." << endl;
    cout << "\n-----------------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(27) << "Account Number";
    cout << "| " << left << setw(44) << "Client Name";
    cout << "| " << left << setw(30) << "Balance";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------\n\n";

    for (stClient& Client : vClients) {

        TotalBalance += Client.AccountBalance;
        PrintClientTotalBalancesRecord(Client);

        cout << endl;

    }

    cout << "\n\n-----------------------------------------------------------------------------------------------------------\n";
    cout << "\n\t\t\t\t\t   Total Balances = " << TotalBalance << endl;


    GoBackToTranscationsMenuScreen();

}



void TransactionsMenuScreenChoice(enTransactionsMenuChoice choice) {

    switch (choice) {

    case enTransactionsMenuChoice::Deposit:
        system("cls");
        system("color 0f");
        ShowDepositScreen();
        break;
    case enTransactionsMenuChoice::Withdraw:
        system("cls");
        system("color 0f");
        ShowWithdrawScreen();
        break;
    case enTransactionsMenuChoice::TotalBalances:
        system("cls");
        system("color 0f");
        ShowTotalBalancesScreen();
        break;
    case enTransactionsMenuChoice::MainMenu:
        GoBackToMainMenu();
        break;

    }

}

void TransactionsMenuScreen() {

    cout << "\n=========================================================================================\n";
    cout << "\t\t\t\tTransactions Menu Screen";
    cout << "\n=========================================================================================\n";
    cout << "\t\t[1] Deposit.";
    cout << "\n\t\t[2] Withdraw.";
    cout << "\n\t\t[3] Total Balances.";
    cout << "\n\t\t[4] Main Menu.";
    cout << "\n=========================================================================================\n";

}

void TransactionsScreen() {

    if (!CheckAccessPermission(enMainMenuPermissions::pTransactions)) {

        system("cls");
        system("color 0f");
        AccessDeniedScreen();

    }

    TransactionsMenuScreen();
    TransactionsMenuScreenChoice(ReadTransactionsMenuChoices("\nChoose what do you want to do? [1 to 4] ? "));

}



// Bank extension 2


void ShowUsersListScreen() {

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    cout << "\n-----------------------------------------------------------------------------------------------------------\n";
    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s)." << endl;
    cout << "\n-----------------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(20) << "User Name";
    cout << "| " << left << setw(17) << "Password";
    cout << "| " << left << setw(34) << "Permissions";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------\n\n";

    for (stUser& User : vUsers) {

        PrintUserRecord(User);

        cout << endl;

    }

    cout << "\n\n-----------------------------------------------------------------------------------------------------------\n";

    GoBackToManageUsersMenuScreen();

}


void ReadNewUser() {

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    stUser User;

    char answer;


    User.username = ReadString("\nEnter username : ");

    while (IsUserExist(User.username, vUsers , User)) {

        cout << "\nUser with username [" << User.username << "] already exists, Enter another username : ";
        User.username = ReadString("\nEnter username : ");

    }

    User.password = ReadString("\nEnter password : ");


    cout << "\nDo you want to give full access : (Y/N) ? ";
    cin >> answer;

    if (toupper(answer) == 'Y') {

        User.permission = -1;

    }
    else {

        cout << "\nDo you want to give access to : ";

        cout << "\nShow Client List : (Y/N) ? ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            User.permission = 1;

        }

        cout << "\nAdd New Client : (Y/N) ? ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            User.permission += 2;

        }

        cout << "\nDelete Client : (Y/N) ? ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            User.permission += 4;

        }

        cout << "\nUpdate Client : (Y/N) ? ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            User.permission += 8;

        }

        cout << "\nFind Client List : (Y/N) ? ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            User.permission += 16;

        }

        cout << "\nTransactions : (Y/N) ? ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            User.permission += 32;

        }

        cout << "\nManage Users : (Y/N) ? ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            User.permission += 64;

        }

    }

    vUsers.push_back(User);

    SaveUsersDataToFile(UsersFileName, vUsers);


}

void AddNewUser1() {

    char answer;

    do {

        cout << "\nAdding New User : ";

        ReadNewUser();

        cout << "\nUser added successfully, Do you want to add more Users : (Y/N) ? ";
        cin >> answer;

    } while (toupper(answer) == 'Y');


}

void AddNewUserScreen() {

    AddNewUserHeader();
    AddNewUser1();
    GoBackToManageUsersMenuScreen();

}





void DeleteUser1() {

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    stUser User;
    char answer;

    string username;

    username = ReadString("\nEnter username : ");

    if (IsUserExist(username, vUsers, User)) {

        if (User.username == "Admin") {

            cout << "\nYou cannot delete this user.";

        }
        else {


            PrintUserCard(User);

            cout << "\nAre you sure you want to delete this user : (Y/N) ? ";
            cin >> answer;

            if (toupper(answer) == 'Y') {

                MarkUserForDelete(username, vUsers);
                SaveUsersDataToFile(UsersFileName, vUsers);


                cout << "\nUser Deleted Successfully.";

            }

        }
    
    }
    else {
    
        cout << "\nUser with username (" << username << ") is not Found!";
    
    }

}

void DeleteUserScreen() {

    DeleteUserHeader();
    DeleteUser1();
    GoBackToManageUsersMenuScreen();

}




void UpdateUser1() {

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    stUser User;
    char answer;

    string username;

    username = ReadString("\nEnter username : ");

    if (IsUserExist(username, vUsers, User)) {

        PrintUserCard(User);

        cout << "\nAre you sure you want to update this user : (Y/N) ? ";
        cin >> answer;

        if (toupper(answer) == 'Y') {

            
            for (stUser& User : vUsers) {

                if (User.username == username) {
                
                    User.username = username;

                    User.password = ReadString("\nEnter password : ");

                    cout << "\nDo you want to give full access : (Y/N) ? ";
                    cin >> answer;

                    if (toupper(answer) == 'Y') {

                        User.permission = -1;

                    }
                    else {

                        cout << "\nDo you want to give access to : ";

                        cout << "\nShow Client List : (Y/N) ? ";
                        cin >> answer;

                        if (toupper(answer) == 'Y') {

                            User.permission = 1;

                        }

                        cout << "\nAdd New Client : (Y/N) ? ";
                        cin >> answer;

                        if (toupper(answer) == 'Y') {

                            User.permission += 2;

                        }

                        cout << "\nDelete Client : (Y/N) ? ";
                        cin >> answer;

                        if (toupper(answer) == 'Y') {

                            User.permission += 4;

                        }

                        cout << "\nUpdate Client : (Y/N) ? ";
                        cin >> answer;

                        if (toupper(answer) == 'Y') {

                            User.permission += 8;

                        }

                        cout << "\nFind Client List : (Y/N) ? ";
                        cin >> answer;

                        if (toupper(answer) == 'Y') {

                            User.permission += 16;

                        }

                        cout << "\nTransactions : (Y/N) ? ";
                        cin >> answer;

                        if (toupper(answer) == 'Y') {

                            User.permission += 32;

                        }

                        cout << "\nManage Users : (Y/N) ? ";
                        cin >> answer;

                        if (toupper(answer) == 'Y') {

                            User.permission += 64;

                        }

                    }

                }
            
            }


            SaveUsersDataToFile(UsersFileName, vUsers);


            cout << "\nUser Updated Successfully.";

        }

    }
    else {

        cout << "\nUser with username (" << username << ") is not Found!";

    }

}

void UpdateUserInfoScreen() {

    UpdateUserInfoHeader();
    UpdateUser1();
    GoBackToManageUsersMenuScreen();

}





void FindUser1() {

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    stUser User;
    char answer;

    string username;

    username = ReadString("\nEnter username : ");

    if (IsUserExist(username, vUsers, User)) {

        PrintUserCard(User);

    }
    else {

        cout << "\nUser with username (" << username << ") is not Found!";

    }

}

void FindUserScreen() {

    FindUserHeader();
    FindUser1();
    GoBackToManageUsersMenuScreen();

}




void StartProject();

void ManageUsersScreen();

void ManageUsersMenuScreenChoice(enManageUsersMenuChoice choice) {

    switch (choice) {

    case enManageUsersMenuChoice::ListUsers:
        system("cls");
        system("color 0f");
        ShowUsersListScreen();
        break;
    case enManageUsersMenuChoice::AddNewUser:
        system("cls");
        system("color 0f");
        AddNewUserScreen();
        break;
    case enManageUsersMenuChoice::DeleteUser:
        system("cls");
        system("color 0f");
        DeleteUserScreen();
        break;
    case enManageUsersMenuChoice::UpdateUser:
        system("cls");
        system("color 0f");
        UpdateUserInfoScreen();
        break;
    case enManageUsersMenuChoice::FindUser:
        system("cls");
        system("color 0f");
        FindUserScreen();
        break;
    case enManageUsersMenuChoice::MainMenu1:
        system("cls");
        system("color 0f");
        StartProject();
        break;

    }

}

void ManageUsersMenuScreen() {

    cout << "\n=========================================================================================\n";
    cout << "\t\t\tManage Users Menu Screen";
    cout << "\n=========================================================================================\n";
    cout << "\t\t[1] List Users.";
    cout << "\n\t\t[2] Add New User.";
    cout << "\n\t\t[3] Delete User.";
    cout << "\n\t\t[4] Update User.";
    cout << "\n\t\t[5] Find User.";
    cout << "\n\t\t[6] Main Menu.";
    cout << "\n=========================================================================================\n";

}





void Login();

void MainMenuScreenChoice(enMenuChoices choice) {

    switch (choice) {

    case enMenuChoices::ShowClientsList:
        system("cls");
        system("color 0f");
        ShowClientsListScreen();
        break;
    case enMenuChoices::AddNewClient:
        system("cls");
        system("color 0f");
        AddNewClientScreen();
        break;
    case enMenuChoices::DeleteClient:
        system("cls");
        system("color 0f");
        DeleteClientScreen();
        break;
    case enMenuChoices::UpdateClientInfo:
        system("cls");
        system("color 0f");
        UpdateClientInfoScreen();
        break;
    case enMenuChoices::FindClient:
        system("cls");
        system("color 0f");
        FindClientScreen();
        break;
    case enMenuChoices::Transactions:
        system("cls");
        system("color 0f");
        TransactionsScreen();
        break;
    case enMenuChoices::ManageUsers:
        system("cls");
        system("color 0f");
        ManageUsersScreen();
        break;
    case enMenuChoices::Logout:
        system("cls");
        system("color 0f");
        Login();
        break;

    }

}

void ShowMainMenuScreen() {

    cout << "\n=================================================================================\n";
    cout << "\t\t\t\tMain Menu Screen";
    cout << "\n=================================================================================\n";
    cout << "\t\t[1] Show Client List.";
    cout << "\n\t\t[2] Add New Client.";
    cout << "\n\t\t[3] Delete Client.";
    cout << "\n\t\t[4] Update Client Info.";
    cout << "\n\t\t[5] Find Client.";
    cout << "\n\t\t[6] Transactions.";
    cout << "\n\t\t[7] Manage Users.";
    cout << "\n\t\t[8] Logout.";
    cout << "\n=================================================================================\n";

}

bool checkUsernameAndPassword(string username , string password , stUser &User) {

    return FindUserByUsernameAndPassword(username, password , User);

}



int main()
{

    Login();

    system("pause >0");

    return 0;
}



void Login() {

    LoginHeader();

    string username = ReadString("\nEnter username : ");
    string password = ReadString("\nEnter password : ");

    while (!checkUsernameAndPassword(username, password , ::CurrentUser)) {

        system("cls");
        LoginHeader();
        cout << "\nInvalid Username/Password!";
        username = ReadString("\nEnter username : ");
        password = ReadString("\nEnter password : ");

    }

    StartProject();

}

void GoBackToMainMenu() {

    cout << "\nPress any key to go back to main menu...";
    system("pause");
    system("cls");
    StartProject();

}

void GoBackToManageUsersMenuScreen() {

    cout << "\nPress any key to go back to manage users menu...";
    system("pause");
    system("cls");
    ManageUsersScreen();

}

void GoBackToTranscationsMenuScreen() {

    cout << "\nPress any key to go back to transacions menu...";
    system("pause");
    system("cls");
    TransactionsScreen();

}

void ManageUsersScreen() {

    if (!CheckAccessPermission(enMainMenuPermissions::pManageUsers)) {

        system("cls");
        system("color 0f");
        AccessDeniedScreen();

    }

    ManageUsersMenuScreen();
    ManageUsersMenuScreenChoice(ReadManageUsersMenuChoices("\nChoose what do you want to do : [1 to 6] ? "));

}

void StartProject() {

    system("cls");
    ShowMainMenuScreen();
    MainMenuScreenChoice(ReadMenuChoices("\nChoose what do you want to do? [1 to 8] ? "));

}


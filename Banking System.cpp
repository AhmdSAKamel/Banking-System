#include "MyFirstLibrary.h"  
#include <iostream>  
#include <fstream>  
#include <iomanip>  
#include <string>  d
#include <vector>
#include <limits>  
#include <cstdlib>

const string ClientsFileName = "ClientsInfo.txt";
const string UsersFileName = "UsersInfo.txt";


enum enMainMenuePermissions {
	enAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
	pUpdateClients = 8, pFindClient = 16, pTransactions = 31, pManageUsers = 61,
};

struct stClient
{
	string AccountNumber;
	string PinCode;
	string ClientName;
	string Phone;
	float Balance = 0;
	bool DeletionMark = false;
};

struct stUsers
{
	string UserName;
	string Password;
	short Permissions = 0;
};

stUsers CurrentUser;

enum enTransactions
{
	Deposit = 1, Withdraw = 2, TotalBalance = 3, MainMenue = 4
};

void ReShowMainMenue();

void ShowMainMenue();

string ReadString(string Message)
{
	string S;

	cout << Message;
	cin >> S;

	return S;
}

int ReadNumberInRange(string Message, short From, short To)
{
	short Number = 0;
	cout << Message;

	do
	{
		cin >> Number;

		if (cin.fail()) 
		{
			cin.clear(); // Clear error flags
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			Number = From - 1;
			cout << "\nPlease enter a valid number between: ";
		}


	} while (Number < From || Number > To);

	return Number;
}

bool FindClientByAccNumber(vector <stClient> vClients, stClient &Client, string AccNumber)
{
	for (stClient C : vClients)
	{
		if (C.AccountNumber == AccNumber)
		{
			Client = C;
			return 1;
		}

	}
	return 0;
}

void PrintClientsCard(stClient Client)
{
	cout << "| " << setw(15) << Client.AccountNumber;
	cout << "| " << setw(10) << Client.PinCode;
	cout << "| " << setw(40) << Client.ClientName;
	cout << "| " << setw(12) << Client.Phone;
	cout << "| " << setw(12) << Client.Balance;
}

void PrintClientCard(stClient Client)
{
	cout << "\n____________________________________________";
	cout << "\nAccount Number      : " << Client.AccountNumber;
	cout << "\nPin Code            : " << Client.PinCode;
	cout << "\nName                : " << Client.ClientName;
	cout << "\nPhone               : " << Client.Phone;
	cout << "\nAccount Balance     : " << Client.Balance;
	cout << "\n____________________________________________";
}

void Login();

void PrintAllClientsData(vector <stClient> Clients)
{
	cout << "\n\t\t\t\t\tClient List (" << Clients.size() << ") Client(s).";
	cout << "\n_________________________________________________________________________";
	cout << "____________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_________________________________________________________________________";
	cout << "____________________________________\n" << endl;

	if (Clients.size() == 0)
	{
		cout << "\t\t\t\t\tNo Clients Available In the System";
	}
	else
	{
		for (stClient& Client : Clients)
		{
			PrintClientsCard(Client);
			cout << endl;
		}
	}
	cout << "\n_________________________________________________________________________";
	cout << "____________________________________\n" << endl;
}

stClient ConvertLineToRecord(string DataLine, string Seperator)
{
	stClient Client;
	string Copy;

	size_t pos = 0;
	for (short i = 0; i < 5; ++i)	 // Loop to get all the fields  
	{
		pos = DataLine.find(Seperator);
		Copy = DataLine.substr(0, pos);

		DataLine.erase(0, pos + Seperator.length()); // Adjust for the separator length  
	
		switch (i) // Assign to the correct member variable  
		{ 

		case 0: Client.AccountNumber = Copy; break;
		case 1: Client.PinCode = Copy; break;
		case 2: Client.ClientName = Copy; break;
		case 3: Client.Phone = Copy; break;
		case 4: Client.Balance = stof(Copy); break;

		}
	}
	return Client;
}

vector <stClient> LoadFileDataToVector(string FileName, string Seperator)
{
	stClient Client;
	vector <stClient> vClients;

	fstream myFile;
	string Line;

	myFile.open(FileName, ios::in);

	if (myFile.is_open())
	{
		while (getline(myFile, Line))
		{
			Client = ConvertLineToRecord(Line, Seperator);

			vClients.push_back(Client);

		}
		myFile.close();
	}

	return vClients;
}

void ShowClientListData(string FileName, string Seperator, vector <stClient> VCs)
{
	PrintAllClientsData(VCs);
}

void ShowAddNewClient()
{
	cout << "____________________________________________\n";
	cout << setw(25) << "Add New Clients Screen\n";
	cout << "____________________________________________\n";
	cout << "Adding New Client:\n\n";
}

bool isAccNumberExist(vector <stClient> vClients, stClient &Client)
{
	for (stClient& C : vClients)
	{
		if (Client.AccountNumber == C.AccountNumber)
			return true;
	}

	return false;
}

stClient ReadNewClient(string Seperator)
{
	stClient Client;
	vector <stClient> vClients = LoadFileDataToVector(ClientsFileName, Seperator);

	cout << "Enter Account Number? ";
	cin >> Client.AccountNumber;
	
	while (isAccNumberExist(vClients, Client))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		cin >> Client.AccountNumber;
	} 
	
	cout << "\nEnter PinCode? ";
	cin >> Client.PinCode;
	cout << "\nEnter Name? ";
	cin >> Client.ClientName;
	cout << "\nEnter Phone? ";
	cin >> Client.Phone;
	
	Client.Balance = ReadNumberInRange("\nEnter Account Balance? ", 1, 1000000);

	
	return Client;
}

string ConvertRecordToLine(stClient Client, string Seperator)
{
	string RecordClient;

	RecordClient += Client.AccountNumber + Seperator;
	RecordClient += Client.PinCode + Seperator;
	RecordClient += Client.ClientName + Seperator;
	RecordClient += Client.Phone + Seperator;
	RecordClient += to_string(Client.Balance);

	return RecordClient;
}

void AddClientToFile(stClient Client, string FileName, string Seperator)
{
	string ClientData = ConvertRecordToLine(Client, Seperator);

	fstream myfile;

	myfile.open(FileName, ios::app);

	if (myfile.is_open())
	{
		myfile << ClientData << endl ;
	}
	myfile.close();
}

void AddNewClient(string FileName, string Seperator)
{
	char Again = 'y';
	stClient Client;

	do
	{
		ShowAddNewClient();

		Client = ReadNewClient(Seperator);

		AddClientToFile(Client, FileName, Seperator);
		

		cout << "\n\nClient Added Successfull, do you want to add more clients? Y/N? ";
		cin >> Again;

	} while (tolower(Again) == 'y');

}

void DeleteClientFromFile(vector <stClient> &vClients, stClient Client, string FileName, string Seperator)
{
	fstream myfile;

	myfile.open(FileName, ios::out);

	string DataLine;

	if (myfile.is_open())
	{
		for (stClient C : vClients)
		{
			if (C.DeletionMark == false)
			{
				DataLine = ConvertRecordToLine(C, Seperator);

				myfile << DataLine << endl;
			}
		}

		vClients = LoadFileDataToVector(FileName, Seperator);

		myfile.close();
	}
}

bool isMatch(stClient Client, string AccountNumber)
{
	if (Client.AccountNumber == AccountNumber)
	{
		return 1;
	}
	else
		return 0;

}

bool DeleteClient(string FileName, string Seperator,vector <stClient> vClients)
{
	string AccNum;
	char DeleteOrNot;

	cout << "____________________________________\n";
	cout <<  setw(10) << "Delete Client Screen\n";
	cout << "____________________________________\n\n";

	cout << "Please enter Account Number? ";
	cin >> AccNum;

	for (stClient &C : vClients)
	{
		if (C.AccountNumber == AccNum)
		{
			cout << "\nThe Following are the client details:";
			PrintClientCard(C);

			cout << "\n\nAre you sure you want to delete this client y/n ? ";
			cin >> DeleteOrNot;

			if (DeleteOrNot == tolower('y'))
			{
				C.DeletionMark = true;

				DeleteClientFromFile(vClients, C, FileName, Seperator);
			}
			return true;
		}
	}
	cout << "\n\nClient with Account Number (" << AccNum << ") is not found\n";
	
	return 0;
}

void UpdateClientInfo(stClient &Client)
{
	cout << "\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "\nEnter Name? ";
	getline(cin >> ws, Client.ClientName);

	cout << "\nEnter Phone? ";
	cin >> Client.Phone;
	cout << "\nEnter Account Balance? ";
	cin >> Client.Balance;
}

void LoadVectorClientsToFile(vector <stClient> vClients, string Seperator, string FileName)
{
	fstream myfile;
	string DataLine;
	stClient Client;

	myfile.open(FileName, ios::out);

	if (myfile.is_open())
	{
		for (stClient& C : vClients)
		{
			DataLine = ConvertRecordToLine(C, Seperator);

			myfile << DataLine << endl;

		}
		myfile.close();
	}
}

void UpdateClientsInfo(string FileName, string Seperator, vector <stClient> vClients)
{
	stClient Client;

	char Answer;

	cout << "________________________________________________\n";
	cout <<  setw(30) << "Update Client Info Screen\n";
	cout << "________________________________________________\n";

	string AccountNumber = ReadString("\nPlease enter Account Number? ");

	for (stClient &C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			PrintClientCard(C);
			cout << "\n\nAre you sure you want to update this client? y/n ";
			cin >> Answer;

			if (tolower(Answer) == 'y')
			{
				UpdateClientInfo(C);

				LoadVectorClientsToFile(vClients, Seperator, FileName);

				cout << "\n\nClient Updated Successfully.";
				break;
			}
			else
				cout << "\n\nClient has not Updated.";
				break;
		}		
	}
	cout << "\n\nAccount number is not found." << endl;
}

void FindClientScreen()
{
	cout << "___________________________________________\n";
	cout << setw(20) << "Find Client Screen" << endl;
	cout << "___________________________________________\n";
}

void FindClientDetailsByID(string FileName, string Seperator)
{
	FindClientScreen();

	vector <stClient> vClients = LoadFileDataToVector(FileName, Seperator);
	
	stClient Client;

	Client.AccountNumber = ReadString("\nPlease enter Account Number? ");
	
	if (isAccNumberExist(vClients, Client))
	{
		for (stClient &C : vClients)
		{
			if (C.AccountNumber == Client.AccountNumber)
			{
				cout << "\nThe following are the client details:";

				PrintClientCard(C);
			}
		}
	}
	else
	{
		cout << "\nClient with Account Number [" << Client.AccountNumber << "] is not found!";
	}
}

void ProgramEndsScreen()
{
	cout << "___________________________________________\n";
	cout << setw(30) << "Program Ends  :-) ";
	cout << "\n___________________________________________";
}

void ShowTransactionScreen(string Seperator);

char ConfirmAddDeposit(string AccNumber, vector<stClient> &vClients, stClient &Client)
{
	char Confirmation;
	short Deposit = 0;

	cout << "\nplease enter deposit amount? ";
	cin >> Deposit;

	cout << "\n\nAre you sure you want to perform this transaction y/n? ";
	cin >> Confirmation;

	if (tolower(Confirmation) == 'y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccNumber)
			{
				C.Balance += Deposit;
				Client.Balance = C.Balance;
				return 'y';
			}
		}
	}
	else
		return 'n';
}

bool DepositBalanceToClientByAccountNumber(string AccNum, double Amount, vector <stClient> vClients, string Seperator)
{
	char Answer = 'n';

	cout << "\n\nAre you sure you want to perform this transaction y/n ? ";
	cin >> Answer;

	if (tolower(Answer) == 'y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccNum)
			{
				C.Balance +=  Amount;

				LoadVectorClientsToFile(vClients, Seperator, ClientsFileName);
				cout << "\n\nDone Successfully. New balance is: " << C.Balance;

				return true;
			}
		}
	}
	return false;
}

void DepositScreen(string Seperator)
{
	system("cls");

	cout << "_________________________________________\n";
	cout << "\tDeposit Screen\n";
	cout << "_________________________________________\n";

	vector <stClient> vClients = LoadFileDataToVector(ClientsFileName, Seperator);
	stClient Client;

	string AccNumber = ReadString("Please enter Account Number? ");

	while (!FindClientByAccNumber(vClients, Client, AccNumber))
	{
		cout << "\nClient with [" << AccNumber << "] does not exist." << endl;

		AccNumber = ReadString("\nPlease enter Account Number ? ");
	}
	
	cout << "\nThe following are the client details:";

	PrintClientCard(Client);

	float Amount = 0;

	cout << "\nPlease enter deposit amount?  ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(AccNumber, Amount, vClients, Seperator);
}

char ConfirmAddWithdrwal(string AccNumber, vector<stClient>& vClients, stClient& Client)
{
	char Confirmation;
	short Deposit = 0;

	cout << "\nplease enter deposit amount? ";
	cin >> Deposit;

	cout << "\n\nAre you sure you want to perform this transaction y/n? ";
	cin >> Confirmation;

	if (tolower(Confirmation) == 'y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccNumber)
			{
				if (C.Balance >= Deposit)
				{
					C.Balance -= Deposit;
					Client.Balance = C.Balance;
					return 'y';
				}
				else
				{
					cout << "\nAmount exceeds the balance, you can withdraw up to : " << C.Balance;
					ConfirmAddWithdrwal(AccNumber, vClients, C);
				}
			}
		}
	}
	else
		return 'n';
}

void WithdrawalScreen(string Seperator)
{
	system("cls");

	cout << "_________________________________________\n";
	cout << setw(25) << "Withdrawal Screen\n";
	cout << "_________________________________________\n\n";

	stClient Client;

	vector <stClient> vClients = LoadFileDataToVector(ClientsFileName, Seperator);

	string ACcountNumber = ReadString("\nPlease enter account number");

	while (!FindClientByAccNumber(vClients, Client, ACcountNumber))
	{
		cout << "\nClient with [" << ACcountNumber << "] does not exist.";
		ACcountNumber = ReadString("\nPlease enter account number");
	}
	
	PrintClientCard(Client);

	float Amount = 0;

	cout << "Please enter withdraw amount? ";
	cin >> Amount;

	while (Amount > Client.Balance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.Balance;
		cout << "Please enter withdraw amount? ";
		cin >> Amount;
	}
	DepositBalanceToClientByAccountNumber(ACcountNumber, Amount * 1, vClients, Seperator);

}

void PrintTotalBalances(vector <stClient> vClients)
{
	double TotalBalances = 0;

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_________________________________________________________________________";
	cout << "____________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_________________________________________________________________________";
	cout << "____________________________________\n" << endl;

	if (vClients.empty())
	{
		cout << "\t\t\t\t\tNo Clients Available In the System";
	}
	else
	{
		for (stClient& Client : vClients)
		{
			cout << "| " << setw(15) << Client.AccountNumber;
			cout << "| " << setw(40) << Client.ClientName;
			cout << "| " << setw(12) << Client.Balance;
		
			TotalBalances += Client.Balance;

			cout << endl;
		}
	}

	cout << "\n_________________________________________________________________________";
	cout << "____________________________________\n" << endl;

	cout << "\t\t\t\tTotal Balances = " << TotalBalance;
}

void TotalBalancesScreen(string Seperator)
{
	system("cls");

	vector <stClient> vClients = LoadFileDataToVector(ClientsFileName, Seperator);

	PrintTotalBalances(vClients);

	system("pause>0");
}

void GoBackToTransactionMenue(string Seperator);

void PerformTransactions(string Seperator)
{
	stUsers User;

	enTransactions UserTrnsaction = enTransactions(ReadNumberInRange("Choose what do you want to do ? [1 to 4]? ", 1, 4));

	switch (UserTrnsaction)
	{
	case enTransactions::Deposit:
	{
		DepositScreen(Seperator);
		GoBackToTransactionMenue(Seperator);

		break;
	}
	case enTransactions::Withdraw:
	{
		WithdrawalScreen(Seperator);
		GoBackToTransactionMenue(Seperator);

		break;
	}
	case enTransactions::TotalBalance:
	{
		TotalBalancesScreen(Seperator);

		GoBackToTransactionMenue(Seperator);
	}
	case enTransactions::MainMenue:
	{
		ShowMainMenue();
	}
	}
}

void ManageUsersScreen();

void ManageUsers();

bool CheckAccessPermissions(short Choice)
{
	enMainMenuePermissions Permission = enMainMenuePermissions(Choice);

	if ((CurrentUser.Permissions == enMainMenuePermissions::enAll) || Choice == 8)
		return true;
						
	short Pemis = (Permission & CurrentUser.Permissions);
	//    5					17
	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else
		return false;

	// 10100000
	// 10001000			!
}

void UserChoice(short Choice, string Seperator, stUsers User)
{
	system("cls");

	if (!CheckAccessPermissions(Choice))
	{
		system("cls");		

		cout << "\n\nYou don't have permission! Contact your admin.\n\n";
		
		ReShowMainMenue();
	}

	vector <stClient> VCs = LoadFileDataToVector(ClientsFileName, Seperator);

	switch (Choice)
	{
	case 1:
	{
		ShowClientListData(ClientsFileName, Seperator, VCs);		
		ReShowMainMenue();

		break;
	}
	case 2:
	{
		AddNewClient(ClientsFileName, Seperator);
		ReShowMainMenue();

		break;
	}
	case 3:
	{
		if (DeleteClient(ClientsFileName, Seperator, VCs))
		{
			cout << "\nClient Deleted Successfully.";
		}

		ReShowMainMenue();

		break;
	}
	case 4:
	{
		UpdateClientsInfo(ClientsFileName, Seperator, VCs);
		ReShowMainMenue();

		break;
	}
	case 5:
	{
		FindClientDetailsByID(ClientsFileName, Seperator);
		ReShowMainMenue();

		break;
	}
	case 6:
	{
		ShowTransactionScreen(Seperator);
		
		break;
	}
	case 7:
	{
		ManageUsers();

		break;
	}
	case 8:
	{
		system("cls");
		Login();
		break;
	}
	}
}

void ShowMainMenue()
{
	system("cls");

	cout << "======================================================\n";
	cout << right << setw(40) << "Main Menue Screen";
	cout << "\n======================================================\n";

	cout << setw(30) << "[1] Show Client List.   \n";
	cout << setw(30) << "[2] Add New Client.     \n";
	cout << setw(30) << "[3] Delete Client.      \n";
	cout << setw(30) << "[4] Update Client Info. \n";
	cout << setw(30) << "[5] Find Client.        \n";
	cout << setw(30) << "[6] Transactions.       \n";
	cout << setw(30) << "[7] Manage Users.       \n";
	cout << setw(30) << "[8] Logout.             \n";

	cout << "=====================================================\n" << endl;

	short Choice = ReadNumberInRange("\nChoose what you want to do? [1 to 8] ? ", 1, 8);

	UserChoice(Choice, "/###/", CurrentUser);
}

void ShowTransactionScreen(string Seperator)
{
	system("cls");

	cout << "======================================================\n";
	cout << setw(30) << "Transactions Menue Screen\n";
	cout << "======================================================\n";
	cout << setw(25) << " [1] Deposit.      \n";
	cout << setw(25) << " [2] Withdraw.     \n";
	cout << setw(25) << " [3] Total Balance.\n";
	cout << setw(25) << " [4] Main Menue.   \n";
	cout << "=======================================================\n";

	PerformTransactions(Seperator);
}

void LoginScreen();

stUsers ReadUserInfo()
{
	stUsers UserInfo;

	cout << "Enter Username? ";
	getline(cin >> ws, UserInfo.UserName);

	cout << "Enter Password? ";
	getline(cin, UserInfo.Password);

	return UserInfo;
}

stUsers ConvertUserLineToRecord(string Line, string Seperator = "#//#")
{
	stUsers User;
	string Copy;

	size_t pos = 0;
	
	for (short i = 0; i < 3; ++i)	 // Loop to get all the fields.
	{
		pos = Line.find("#//#");
		Copy = Line.substr(0, pos);

		pos += Seperator.length();

		switch (i) // Assign to the correct member variable.
		{

		case 0: User.UserName = Copy; break;
		case 1: User.Password = Copy; break;
		case 2: User.Permissions = stoi(Copy); break;

		}
	
		Line.erase(0, pos); // Adjust for the separator length.
	}	
	return User;
}

string ConvertUserRecordToLine(stUsers UserInfo, string Seperator)
{
	return UserInfo.UserName + Seperator + UserInfo.Password + Seperator + to_string(UserInfo.Permissions);
}

vector <stUsers> LoadUserInfoToVector(string FileName)
{
	vector <stUsers> UsersInfo;
	stUsers UserInfo;

	fstream UserFile;

	UserFile.open(FileName, ios::in);

	if (UserFile.is_open())
	{
		string Line;

		while (getline(UserFile, Line))
		{
			UserInfo = ConvertUserLineToRecord(Line);

			UsersInfo.push_back(UserInfo);
		}
	}
	UserFile.close();

	return UsersInfo;
}

bool IsUserInfoCorrect(stUsers &UserInfo)
{
	vector <stUsers> vUsersInfo = LoadUserInfoToVector(UsersFileName);

	for (stUsers& User : vUsersInfo)
	{
		if (UserInfo.UserName == User.UserName && UserInfo.Password == User.Password)
		{
			UserInfo.Permissions = User.Permissions;
			return true;
		}
	}

	return false;
}

void PrintUserInfo(stUsers User)
{
	cout << "| " << setw(15) << User.UserName;
	cout << "| " << setw(10) << User.Password;
	cout << "| " << setw(40) << User.Permissions;
}

void PrintUserCard(stUsers User)
{
	cout << "\n\nThe following are the User details:";
	cout << "\n__________________________________________\n";
	cout << "\n| UserName    : " << setw(5) << User.UserName;
	cout << "\n| Password    : " << setw(5) << User.Password;
	cout << "\n| Permissions : " << setw(5) << User.Permissions;
	cout << "\n__________________________________________\n";
}

void ShowUsersList(vector <stUsers> UsersInfo);

void AgainForUser()
{
	cout << "\nPress any key to go back....";

	system("pause>0");

	ManageUsers();
}

void UserScreen(string Required = "")
{
	system("cls");

	cout << "____________________________________________\n";
	cout << setw(35) << Required;
	cout << "____________________________________________\n";
}

void AddNewUserToFile(stUsers NewUser)
{
	string LineInfo = ConvertUserRecordToLine(NewUser, "#//#");

	fstream UserFile;

	UserFile.open(UsersFileName, ios::app);

	if (UserFile.is_open())
	{
		UserFile << endl << LineInfo ;
	}
	UserFile.close();
}

bool IsUserExtant(string UserName, vector <stUsers> UsersInfo, stUsers &User)
{
	for (stUsers &U : UsersInfo)
	{
		if (UserName == U.UserName)
		{
			User = U;
			return 1;
		}
	}	
	return 0;
}

short ReadPermissionsToSet()
{
	char Answer = 'n';
	short Pemissions = 0;

	cout << "\n\nDo you want to give full access y/n? ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{
		return -1;
	}


	cout << "\n\nDo you want to give access to :\n\n";

	for (short i = 1; i < 8; i++)
	{
		switch (i)
		{
		case 1:
		{
			cout << "Show Client List Y/N? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
			{
				Pemissions += enMainMenuePermissions::pListClients;
			}

			break;
		}
		case 2:
		{
			cout << "Add New Client? Y/N? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
			{
				Pemissions += enMainMenuePermissions::pAddNewClient;
			}

			break;
		}
		case 3:
		{
			cout << "Delete Client? Y/N? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
			{
				Pemissions += enMainMenuePermissions::pDeleteClient;
			}
			break;
		}
		case 4:
		{
			cout << "Update Client? Y/N? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
			{
				Pemissions += enMainMenuePermissions::pUpdateClients;
			}
			break;
		}
		case 5:
		{
			cout << "Find Client? Y/N? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
			{
				Pemissions += enMainMenuePermissions::pFindClient;
			}
			break;
		}
		case 6:
		{
			cout << "Transactions? Y/N? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
			{
				Pemissions += enMainMenuePermissions::pTransactions;
			}
			break;
		}
		case 7:
		{
			cout << "Manage Users? Y/N? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
			{
				Pemissions += enMainMenuePermissions::pManageUsers;
			}
			break;
		}
		}
	}

	return Pemissions;
}

void AddNewUser(vector <stUsers> Users)
{
	char Again = 'y';

	while (Again == 'y')
	{
		UserScreen("Add New User Screen\n");

		stUsers User;

		cout << "Enter Username? ";
		cin >> User.UserName;

		while (IsUserExtant(User.UserName, Users, User))
		{
			cout << endl << "User with [" << User.UserName << "] already exists, Enter another Username? ";
			cin >> User.UserName;
		}

		cout << "Enter Password? ";
		cin >> User.Password;

		
		User.Permissions = ReadPermissionsToSet();

		AddNewUserToFile(User);

		cout << "\n\nUser Added Successfully, do you want to add more Users Y/N? ";
		cin >> Again;

		Again = tolower(Again);
	}
}

void DeleteUserByUserName(stUsers UserToDelete, vector <stUsers> vUsers)
{
	fstream UsersFile;

	UsersFile.open(UsersFileName, ios::out);
	string LineInfo;

	if (UsersFile.is_open())
	{
		for (stUsers U : vUsers)
		{
			if (U.UserName != UserToDelete.UserName)
			{
				LineInfo = ConvertUserRecordToLine(U, "#//#");

				UsersFile << LineInfo;
			}
		}
	}
}

void DeleteUser(vector <stUsers> Users)
{

	UserScreen("Delete Users Screen\n");

	stUsers User;
	char Answer;

	cout << "\nPlease enter Username? ";
	cin >> User.UserName;

	if (!IsUserExtant(User.UserName, Users, User))
	{
		cout << "\nUser with Username (" << User.UserName << ") is not found!";

		AgainForUser();
	}
	else
		PrintUserCard(User);
	cout << "\n\nAre you sure you want delete this User? y/n? ";
	cin >> Answer;

	if (tolower(Answer == 'y'))
	{
		DeleteUserByUserName(User, Users);
		cout << "\n\nUser Deleted Successfully.";
	}

	AgainForUser();
}

void UpdateUserByUserName(stUsers &User, vector <stUsers> vUsers)
{
	cout << "\n\nEnter Password? ";
	cin >> User.Password;
	string LineInfo;

	User.Permissions = ReadPermissionsToSet();

	fstream UserF;

	UserF.open(UsersFileName, ios::out);

	if (UserF.is_open())
	{
		for (stUsers Us : vUsers)
		{
			if (Us.UserName == User.UserName)
			{
				LineInfo = ConvertUserRecordToLine(User, "#//#");

				UserF << LineInfo << endl;
			}
			else
				LineInfo = ConvertUserRecordToLine(Us, "#//#");
				UserF << LineInfo << endl;
		}
	}
}

void UpdateUser(vector <stUsers> Users)
{
	UserScreen("Update Users Screen\n");

	stUsers User;
	char Answer;

	cout << "\nPlease enter Username? ";
	cin >> User.UserName;

	if (!IsUserExtant(User.UserName, Users, User))
	{
		cout << "\nUser with Username (" << User.UserName << ") is not found!";
	}
	else
		PrintUserCard(User);
		cout << "\n\nAre you sure you want Update this User? y/n? ";
		cin >> Answer;

	if (tolower(Answer == 'y'))
	{
		UpdateUserByUserName(User, Users);
		cout << "\n\nUser Updated Successfully.";
	}

	AgainForUser();
}

void FindUser(vector <stUsers> vUsers)
{
	UserScreen("Update Users Screen\n");

	stUsers User;
	string sUser;

	cout << "\nPlease enter UserName? ";
	cin >> sUser;

	if (IsUserExtant(sUser, vUsers, User))
	{
		PrintUserCard(User);
	}
	else
		cout << "\nUser with Username (" << User.UserName << ") is not found!";
}

void ManageUserChoice(short Choice)
{
	vector <stUsers> UsersInfo = LoadUserInfoToVector(UsersFileName);

	switch (Choice)
	{
	case 1:
	{
		ShowUsersList(UsersInfo);

		AgainForUser();
		break;
	}
	case 2:
	{
		AddNewUser(UsersInfo);

		AgainForUser();
		break;
	}
	case 3:
	{
		DeleteUser(UsersInfo);

		AgainForUser();
		break;
	}
	case 4:
	{
		UpdateUser(UsersInfo);

		AgainForUser();
		break;
	}
	case 5:
	{
		FindUser(UsersInfo);

		AgainForUser();
		break;
	}

	case 6:
	{
	    ReShowMainMenue();
	}
	}
}


int main()
{
	Login();


	return 0;
}


void GoBackToTransactionMenue(string Seperator)
{
	cout << "\n\nPress any key to go back to any transaction menue . . .";

	system("pause>0");

	system("cls");

	cout << "======================================================\n";
	cout << setw(30) << "Transactions Menue Screen\n";
	cout << "======================================================\n";
	cout << setw(25) << " [1] Deposit.      \n";
	cout << setw(25) << " [2] Withdraw.     \n";
	cout << setw(25) << " [3] Total Balance.\n";
	cout << setw(25) << " [4] Main Menue.   \n";
	cout << "=======================================================\n";

	PerformTransactions(Seperator);
}

void ReShowMainMenue()
{
	cout << "\nPress to Continue . . . ";
	
	system("pause>0");
	system("cls");

	cout << "======================================================\n";
	cout << right << setw(40) << "Main Menue Screen";
	cout << "\n======================================================\n";

	cout << setw(30) << "[1] Show Client List.   \n";
	cout << setw(30) << "[2] Add New Client.     \n";
	cout << setw(30) << "[3] Delete Client.      \n";
	cout << setw(30) << "[4] Update Client Info. \n";
	cout << setw(30) << "[5] Find Client.        \n";
	cout << setw(30) << "[6] Transactions.       \n";
	cout << setw(30) << "[7] Mangae Users        \n";
	cout << setw(30) << "[8] Logout.             \n";

	cout << "=====================================================\n" << endl;

	short Choice = ReadNumberInRange("\nChoose what you want to do? [1 to 8] ? ", 1, 8);

	UserChoice(Choice, "/###/", CurrentUser);
}

void LoginScreen()
{
	system("cls");

	cout << "\n===============================================\n";
	cout << setw(30) << "Login Screen";
	cout << "\n===============================================" << endl;
}

void Login()
{
	
	LoginScreen();

	CurrentUser = ReadUserInfo(); 

	while (!IsUserInfoCorrect(CurrentUser))
	{
		LoginScreen();

		cout << "Invalid Username/Password!\n";

	    CurrentUser = ReadUserInfo();
	}

    ShowMainMenue();
}

void ManageUsersScreen()
{
	system("cls");

	cout <<"======================================================\n" << right;
	cout << setw(40) << "Manage Users Menue Screen";
	cout << "\n======================================================\n";

	cout << setw(25) << "[1] List Users.   \n";
	cout << setw(25) << "[2] Add New Users.\n";
	cout << setw(25) << "[3] Delete User.  \n";
	cout << setw(25) << "[4] Update User.  \n";
	cout << setw(25) << "[5] Find User.    \n";
	cout << setw(25) << "[6] Main Menue.   \n";
	cout << "======================================================\n";
}

void ManageUsers()
{
	ManageUsersScreen();

	short Choice = ReadNumberInRange("Choose what you want to do? [1 to 6] ? ", 1, 8);

	ManageUserChoice(Choice);
}

void ShowUsersList(vector <stUsers> UsersInfo)
{
	system("cls");

	cout << "\n\t\t\t\t\tUser List (" << UsersInfo.size() << ") User(s).";
	cout << "\n_________________________________________________________________________";
	cout << "____________________________________\n" << endl;

	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n_________________________________________________________________________";
	cout << "____________________________________\n" << endl;

	if (UsersInfo.size() == 0)
	{
		cout << "\t\t\t\t\tNo Usres Available In the System";
	}
	else
	{
		for (stUsers& User : UsersInfo)
		{
			PrintUserInfo(User);

			cout << endl;
		}
	}

	cout << "\n_________________________________________________________________________";
	cout << "____________________________________\n" << endl;
}
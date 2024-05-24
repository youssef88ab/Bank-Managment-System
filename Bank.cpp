// BY YOUSSEF ABOU ELJIHAD 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdio>


void Mainscreen();
void Transiction();


using namespace std;

struct sClient 
{
	string Num_Account;
	string Pincode;
	string Name;
	string Phone;
	double Balance = 0;
};

string FileName = "BANK.txt";


// ------------------ CONVERSION FUNCTIONS -----------------------------------

vector <string> SplitString(string Letter, string Delim)
{

	// Variables ;

	vector <string> vString;
	string Word;
	int pos = 0;

	while ((pos = Letter.find(Delim)) != std::string::npos)
	{
		Word = Letter.substr(0, pos);

		// Store Word In Vector ;

		if (Word != "")
		{
			vString.push_back(Word);
		}

		// Erase Word That Stored ;

		Letter.erase(0, pos + Delim.length());
	}


	// Store Last Word ;

	if (Letter != "")
	{
		vString.push_back(Letter);
	}

	return vString;


}

sClient Line_To_Record(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.Num_Account = vClientData[0];
	Client.Pincode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.Balance = stod(vClientData[4]); //cast string to double
	return Client;
}

string  Client_To_Record(sClient Client, string Delim)
{
	string Record = "";
	Record += Client.Num_Account + Delim;
	Record += Client.Pincode + Delim;
	Record += Client.Name + Delim;
	Record += Client.Phone + Delim;
	Record += to_string(Client.Balance);
	return Record;
}

sClient Record_To_Client(string Record, string Delim)
{

	// Variables ;

	vector <string> vString;
	vector <double> vdouble;
	string Word;
	int pos = 0;

	while ((pos = Record.find(Delim)) != std::string::npos)
	{
		Word = Record.substr(0, pos);

		// Store Word In Vector ;

		if (Word != "")
		{
			vString.push_back(Word);
		}

		// Erase Word That Stored ;

		Record.erase(0, pos + Delim.length());
	}


	// Store Last Word ;

	if (Record != "")
	{
		vdouble.push_back(stod(Record));
	}


	sClient Client;

	Client.Num_Account = vString[0];
	Client.Pincode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.Balance = vdouble[0];


	return Client;
}


//--------------------- UX/UI FUNCTIONS --------------------------------------



string Read_Account_Number()
{
	string AccNumber;

	cout << "Please Enter Account Number : ";
	cin >> AccNumber;

	return AccNumber;
}






void PrintClientRecord(sClient Client)
{
	cout << "\n\nThe following is the extracted client record:\n";
	cout << "\nAccout Number: " << Client.Num_Account;
	cout << "\nPin Code     : " << Client.Pincode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.Balance;
}

void Print_Client(sClient Client)
{

	cout << "| " << left << setw(16) << Client.Num_Account;
	cout << "| " << left << setw(16) << Client.Pincode;
	cout << "| " << left << setw(16) << Client.Name;
	cout << "| " << left << setw(16) << Client.Phone;
	cout << " | " << left << setw(16) << Client.Balance;
	cout << endl;

}

void Print_Client_Balance(sClient Client)
{

	cout << "| " << left << setw(16) << Client.Num_Account;
	cout << "| " << left << setw(16) << Client.Name;
	cout << "| " << left << setw(16) << Client.Balance;
	cout << endl;
}


void BackToMenu()
{
	cout << "\n Press Any Key To Back To Menu .\n";
	system("pause>0");
	system("cls");
	Mainscreen();
}

void BackToTransiction()
{
	cout << "\n Press Any Key To Back To Transiction Menu .\n";
	system("pause>0");
	system("cls");
	Transiction();
}



void AddClientScreen()
{
	cout << "------------- ADD CLIENT MENU --------------- \n";
	cout << "----------------------------------------------- \n \n";
}

void DeleteClientScreen()
{
	cout << "------------- DELETE CLIENT MENU --------------\n";
	cout << "----------------------------------------------- \n \n";
}

void UpdateClientScreen()
{
	cout << "------------- UPDATE CLIENT MENU --------------\n";
	cout << "----------------------------------------------- \n \n";
}

void FindClientScreen()
{
	cout << "------------- FIND CLIENT MENU --------------\n";
	cout << "----------------------------------------------- \n \n";

}

void TransictionScreen()
{
	cout << "--------------- TRANSITION MENU ---------------\n";
	cout << "----------------------------------------------- \n \n";
	cout << setw(10) << "" << "[1] : Deposit. \n";
	cout << setw(10) << "" << "[2] : Withdraw. \n";
	cout << setw(10) << "" << "[3] : Total Balances. \n";
	cout << setw(10) << "" << "[4] : Main Menu. \n";
	cout << "-------------------------------------------\n";
	cout << "-------------------------------------------\n\n";

	cout << "Chose From [1-4] :";

}


//---------------------------------------------------------------------

//---------------------- DEALING DATA IN FILES ------------------------



vector <sClient> Load_Data_From_File(string FileName)
{
	fstream File;
	vector <sClient >vClients;

	sClient Client;
	File.open(FileName, ios::in); // Read mode



	// Store Data Of Users From File in Vector;

	if (File.is_open())
	{
		string Line;
		string Record;
		while (getline(File, Line))
		{
			Client = Line_To_Record(Line);
			vClients.push_back(Client);
		}
	}
	return vClients;
}

bool Isitexist(string AccNumber, string FileName)
{
	fstream File;
	File.open(FileName, ios::in); // Read Mode

	vector <sClient> vClient = Load_Data_From_File(FileName);

	for (sClient& N : vClient)
	{
		if (N.Num_Account == AccNumber) return true;
	}
	return false;

}

sClient	Readclient()
{
	sClient Client;

	cout << "-------- PLEASE ENTER ACCOUNT DATA : ---------\n \n";

	cout << "Enter Account Number  : ";
	do
	{
		getline(cin >> ws, Client.Num_Account);
		if (Isitexist(Client.Num_Account, "BANK.txt"))
		{
			cout << "THIS ACCOUNT NUMBER ALREADY EXIST PLEASE ENTER ANOTHER ONE : ";
		}

	} while (Isitexist(Client.Num_Account, "BANK.txt"));

	cout << "Enter Pincode         : ";
	getline(cin, Client.Pincode);

	cout << "Enter Name            : ";
	getline(cin, Client.Name);

	cout << "Enter Phone           : ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance : ";
	cin >> Client.Balance;

	return Client;
}

string AddClient()
{
	sClient Client;
	fstream	File;

	File.open(FileName, ios::out | ios::app); // Write mode or App  Mode if file Dosent Exist;
	char Check;
	do
	{
		Client = Readclient();

		if (File.is_open())
		{
			File << Client_To_Record(Client, "#//#") << "\n";
		}

		cout << " \n Client Added Succesfully , Do you Want to add More ? (y/n) :";
		cin >> Check;

		if (Check == 'y' || Check == 'Y') system("cls");

	} while (Check == 'y' || Check == 'Y');

	return FileName;
}

void Print_Clients(string FileName)
{
	fstream File;
	int     Count = 0;
	sClient Client;
	File.open(FileName, ios::in); // Read mode

	vector <sClient> vClient = Load_Data_From_File(FileName);

	// User Interface 
	cout << "              CLIENTS LIST (" << vClient.size() << ") " << "Client(s).";
	cout << "\n--------------------------------------------------------------------------------\n";
	cout << "| Account Number  ";
	cout << "| Pincode         ";
	cout << "| Name            ";
	cout << "| Phone           ";
	cout << "| Balance        \n";
	cout << "\n--------------------------------------------------------------------------------\n";


	// Print Data Of Users From File;

	if (File.is_open())
	{
		string Line;
		string Record;
		while (getline(File, Line))
		{
			Client = Line_To_Record(Line);
			Print_Client(Client);
			Count++;
		}
	}
}

void SaveVectorToFile(string FileName, vector <string> vFileContent)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (string Line : vFileContent)
		{
			if (Line != "")
			{
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
}

bool Find_Client_By_Account_Number(string AccountNumber , string FileName)
{
	vector <sClient> vClients = Load_Data_From_File(FileName);
	bool Check = false;
	sClient Clienttest;


	// Search For Client ;
	for (sClient Client : vClients)
	{
		if (Client.Num_Account == AccountNumber)
		{
			Check = true;
			Clienttest = Client;
			break;
		}
	}

	// Results : 
	if (Check == false) cout << "Client With Account Number " << AccountNumber << " Not Found";
	else if (Check == true)
	{
		cout << "Account Details : \n";
			PrintClientRecord(Clienttest);
			cout << endl;
	}
	if (Check == false) return false;
	else  return true;

}

vector <sClient> Delete(vector <sClient>& vClient, string AccNumber)
{
	string Word;
	int Count = 0;
	for (sClient& N : vClient)
	{
		if (N.Num_Account == AccNumber)
		{
			vClient.erase(vClient.begin() + Count);
		}
		Count++;
	}
	return vClient;
}

void Delete_Accounts(string FileName, string AccNumber)
{

	bool Check = Find_Client_By_Account_Number(AccNumber, FileName);
	vector <sClient> vClient = Load_Data_From_File(FileName);
	string Word;
	vector <string> vString;

	if (Check == true)
	{
		cout << "\nARE YOU SURE YOU WANT TO DELETE THIS CLIENT ? (Y/N) :";
		cin >> Word;
	}

	if (Word == "Y" || Word == "y")
	{
		vClient = Delete(vClient, AccNumber);

		for (sClient N : vClient)
		{
			vString.push_back(Client_To_Record(N, "#//#"));
		}

		SaveVectorToFile(FileName, vString);
		cout << "DELETED SECESFULLY ;-;";
	}

}

void UpdateClientfile(string FileName , string AccNumber)
{
	vector <sClient> vClient = Load_Data_From_File(FileName);
	sClient Target;
	string Check;

	if (Find_Client_By_Account_Number(AccNumber, FileName))
	{
		cout << "\nDO YOU WANT TO UPDATE IT ? (Y/N) :";
		cin >> Check;

		if (Check == "Y" || Check == "y")
		{
			Target = Readclient();

			for (sClient& N : vClient)
			{
				if (N.Num_Account == AccNumber)
				{
					N.Num_Account = Target.Num_Account;
					N.Balance = Target.Balance;
					N.Phone = Target.Phone;
					N.Pincode = Target.Pincode;
					N.Name = Target.Name;
				}
			}
		}
	}
	vector <string> vString;

	for (sClient N : vClient)
	{
		vString.push_back(Client_To_Record(N,"#//#"));
	}

	SaveVectorToFile(FileName, vString);

	cout << "FILE UPDATED SECCUSFULY :-:";

}

void Save_Vector_Client_File(vector <sClient> vClient)
{
	vector <string> vString;

	for (sClient N : vClient)
	{
		vString.push_back(Client_To_Record(N, "#//#"));
	}

	SaveVectorToFile(FileName, vString);
}

//------------------------------- TRANSICTION FUNCTIONS ---------------------------//

void Deposit()
{
	float Depo;
	string AccNumber = Read_Account_Number();

	if (Find_Client_By_Account_Number(AccNumber, FileName))
	{
		cout << "Please Enter Deposit Amount : ";
		cin >> Depo;

		vector <sClient> vClient = Load_Data_From_File(FileName);
		
		for (sClient &N : vClient)
		{
			if (N.Num_Account == AccNumber) N.Balance += Depo;
		}
		
		Save_Vector_Client_File(vClient);
		cout << "\nDeposit Added Successfully.\n";
	}
}

void Withdraw()
{
	float With;
	string Check;
	string AccNumber = Read_Account_Number();

	if (Find_Client_By_Account_Number(AccNumber, FileName))
	{
		cout << "Please Enter WithDraw  Amount : ";
		cin >> With;

		vector <sClient> vClient = Load_Data_From_File(FileName);

		for (sClient &N : vClient)
		{
			if (N.Num_Account == AccNumber)
			{
				if (N.Balance >= With)
				{
					N.Balance -= With;
					Save_Vector_Client_File(vClient);
					cout << "\nWithdraw Successfully.\n";
					BackToTransiction();
				}

				else if (N.Balance < With)
				{
					cout << "Account Balance Insuffisant You Can Draw Up to " << N.Balance << endl;
					cout << "Enter 1 To Try Again Or Any Key To Back To Transiction Menu :";
					cin >> Check;

					if (Check == "1")
					{
						cout << system("pause>0");
						Transiction();
					}
				}
			}
		}
	}
}

double Count_Balances(string FileName)
{
	fstream File;
	double Balances = 0;

	File.open(FileName, ios::in); // Read Mode 

	vector <sClient> vClient = Load_Data_From_File(FileName);

	for (sClient& N : vClient)
	{
		Balances += N.Balance;
	}

	return Balances;
}

void Print_Clients_Balances(string FileName)
{
	fstream File;
	sClient Client;
	File.open(FileName, ios::in); // Read mode

	vector <sClient> vClient = Load_Data_From_File(FileName);

	// User Interface 
	cout << "              CLIENTS LIST (" << vClient.size() << ") " << "Client(s).";
	cout << "\n--------------------------------------------------------------------------------\n";
	cout << "| Account Number  ";
	cout << "| Name            ";
	cout << "| Balance        \n";
	cout << "\n--------------------------------------------------------------------------------\n";


	// Print Data Of Users From File;

	if (File.is_open())
	{
		string Line;
		string Record;
		while (getline(File, Line))
		{
			Client = Line_To_Record(Line);
			Print_Client_Balance(Client);
		}
	}
	cout << "\n--------------------------------------------------------------------------------\n";
	cout << "                                                   TOTAL BALANCES = " << Count_Balances("BANK.txt");
}

void Transiction()
{
	short Check;
	TransictionScreen();
	cin >> Check;
	cout << system("cls");

	switch (Check)
	{
	case 1 :
	{
		Deposit();
		BackToTransiction();
	}

	case 2 :
	{
		Withdraw();
	}

	case 3 :
	{
		Print_Clients_Balances(FileName);
		BackToTransiction();
	}

	default: BackToMenu();
	}


}


//-----------------------------------------------------------------------

void Mainscreen()
{
	short Check;


	cout << "--------------- SCREEN MENU -------------------\n";
	cout << "-----------------------------------------------\n\n";
	cout << setw(10) << "" << "[1] : Show Client List. \n";
	cout << setw(10) << "" << "[2] : Add New Client. \n";
	cout << setw(10) << "" << "[3] : Delete Client. \n";
	cout << setw(10) << "" << "[4] : Update Client Info. \n";
	cout << setw(10) << "" << "[5] : Find Client. \n";
	cout << setw(10) << "" << "[6] : Trasniction. \n";
	cout << setw(10) << "" << "[7] : Exit. \n";

	cout << "-------------------------------------------\n";
	cout << "-------------------------------------------\n\n";

	cout << "Chose From [1-7] :";
	cin >> Check;

	cout << system("cls");

	switch (Check)
	{
	case 1:
	{
		Print_Clients(FileName);
		BackToMenu();
		break;
	}

	case 2:
	{
		AddClientScreen();
		AddClient();
		BackToMenu();
		break;
	}

	case 3:
	{
		DeleteClientScreen();
		Delete_Accounts(FileName, Read_Account_Number());
		BackToMenu();
		break;
	}

	case 4:
	{
		UpdateClientScreen();
		UpdateClientfile(FileName, Read_Account_Number());
		BackToMenu();
		break;
	}
	
	case 5:
	{
		FindClientScreen();
		Find_Client_By_Account_Number(Read_Account_Number(), FileName);
		BackToMenu();
		break;
	}

	case 6 : 

	{
		Transiction();
	}

	default :
	{
		cout << system("cls");
		cout << "--------------------------------------\n Program Ends .-. \n----------------------------";
	}
	}
}

//------------------------------------------------------------------------------------------

int main()
{
		
	Mainscreen();

	return 0;
}

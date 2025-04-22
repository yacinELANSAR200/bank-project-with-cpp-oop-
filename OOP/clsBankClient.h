#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>
class clsBankClient:public clsPerson
{
private:
	enum enMode
	{
		EmptyMode=0,UpdateMode=1,AddNewMode=2,
	};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete=false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#") {
		vector<string> vClientData = clsString::Split(Line,Seperator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {
		string stClientRecord = "";
		stClientRecord +=  Client.FirstName + Seperator;
		stClientRecord +=  Client.LastName + Seperator;
		stClientRecord +=  Client.Email + Seperator;
		stClientRecord +=  Client.Phone + Seperator;
		stClientRecord +=  Client.GetAccountNumber() + Seperator;
		stClientRecord +=  Client.PinCode + Seperator;
		stClientRecord +=  to_string(Client.AccountBalance) + Seperator;
		return stClientRecord;

	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile() {
		fstream MyFile;
		vector <clsBankClient> vClients;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients, string Seperator = "#//#") {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		
		string DataLine="";
		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients) {
				if (C.GetMarkForDelete()==false)
				{
				//we store only clients with MarkForDelete property is false
				DataLine = _ConvertClientObjectToLine(C);
				MyFile << DataLine<< endl;
				}
			}
		}
		MyFile.close();
	}

	static void _AddDataLineToFile(string Line) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app | ios::out);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}
	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _Update() {
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClients) {
			if (C.GetAccountNumber()==GetAccountNumber())
			{
				C = *this; 
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}
	string _PrepareTransferRecord(double Amount, clsBankClient DestinationClient, string UserName,string Seperator = "#//#")
	{
		string TransferRecord = "";
		TransferRecord+= clsDate::GetSystemDateTimeInString() + Seperator;
		TransferRecord+= _AccountNumber + Seperator;
		TransferRecord+= DestinationClient.GetAccountNumber() + Seperator;
		TransferRecord+= to_string(Amount) + Seperator;
		TransferRecord+= to_string(_AccountBalance) + Seperator;
		TransferRecord+= to_string(DestinationClient.AccountBalance)+ Seperator;
		TransferRecord+= UserName;
		return TransferRecord;

	}
	void _RegisterTransferLogin(double Amount, clsBankClient DestinationClient ,string UserName) {
		string DataLine = _PrepareTransferRecord(Amount, DestinationClient, UserName);
		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
	struct stTransferLog;
	static stTransferLog _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#")
	{
		stTransferLog TransferLogData;
		vector<string> vTransferLogData = clsString::Split(Line, Separator);
		TransferLogData.DateTime = vTransferLogData[0];
		TransferLogData.AccountFrom = vTransferLogData[1];
		TransferLogData.AccountTo = vTransferLogData[2];
		TransferLogData.Amount = stod(vTransferLogData[3]);
		TransferLogData.AccountBalanceSource = stod(vTransferLogData[4]);
		TransferLogData.AccountBalanceDestination = stod(vTransferLogData[5]);
		TransferLogData.User = vTransferLogData[6];
	
		return TransferLogData;
	}
public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_PinCode = PinCode;
		_AccountNumber = AccountNumber;
		_AccountBalance = AccountBalance;
	}
	
	struct stTransferLog 
	{
		string DateTime;
		string AccountFrom;
		string AccountTo;
		double Amount;
		double AccountBalanceSource;
		double AccountBalanceDestination;
		string User;
	};

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}
	
	string GetAccountNumber() {
		return _AccountNumber;
	}
	
	string GetPinCode() {
		return _PinCode;
	}
	void setPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	__declspec(property(get = GetPinCode, put = setPinCode))string PinCode;

	float GetAccountBalance() {
		return _AccountBalance;
	}
	void setAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = setAccountBalance))float AccountBalance;

	bool GetMarkForDelete() {
		return _MarkForDelete;
	}

	bool Delete() {
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : vClients) {
			if (C.GetAccountNumber()==_AccountNumber)
			{
				C._MarkForDelete = true; 
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	
	static clsBankClient Find(string AccountNumber) {
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.GetAccountNumber()==AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	
	static clsBankClient Find(string AccountNumber,string PinCode) {
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.GetAccountNumber() == AccountNumber && Client.PinCode==PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	
	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			if (IsEmpty())
			{
			return enSaveResults::svFaildEmptyObject;
			}
		case clsBankClient::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case clsBankClient::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else 
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		default:
			break;
		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) 
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector<clsBankClient> GetClientsList() 
	{
		return _LoadClientsDataFromFile();
	}
	static float GetTotalBalances() 
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		double TotalBalance = 0;

		for (clsBankClient& C : vClients) {
			TotalBalance += C.AccountBalance;
		}
		return TotalBalance;
	}
	void Deposit(double Amount) {
		_AccountBalance += Amount;
		save();
	}
	bool WithDraw(double Amount) {
		if (Amount > _AccountBalance)
			return false;
		else {
			_AccountBalance -= Amount;
			save();
			return true;
		}
	}
	bool Transfer(double Amount, clsBankClient& DestinationClient,string UserName="") {
		if (Amount > _AccountBalance ||( GetAccountNumber()== DestinationClient.GetAccountNumber()))
			return false;
		else {
			WithDraw(Amount);
			DestinationClient.Deposit(Amount);
			_RegisterTransferLogin(Amount,DestinationClient,UserName);
			return true;
		}
	}

	static vector<stTransferLog> GetTransferLogList() {
		vector<stTransferLog> vTransferLogData;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			stTransferLog TransferLogData;
			while (getline(MyFile, Line)) {
				TransferLogData = _ConvertTransferLogLineToRecord(Line);
				vTransferLogData.push_back(TransferLogData);
			}
			MyFile.close();
		}
		return vTransferLogData;
	}
	
};


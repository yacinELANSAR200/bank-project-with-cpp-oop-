#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class clsAddNewClient:protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client) {
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadNumber<float>();
	}

	static void _Print(clsBankClient Client) {
		cout << "\n============Client Card============\n";
		cout << "\nFirst Name: " << Client.FirstName;
		cout << "\nLast  Name: " << Client.LastName;
		cout << "\nFull  Name: " << Client.FullName();
		cout << "\nEmail     : " << Client.Email;
		cout << "\nAcc Number: " << Client.GetAccountNumber();
		cout << "\nBalance   : " << Client.AccountBalance;
		cout << "\nPassword  : " << Client.PinCode;
		cout << "\n==================================\n";

	}

public:
	static void AddNewClient() {
		if (!_CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}
		_DrawScreenHeader("\t Add new Client Screen");

		string AccountNumber = "";
		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient already Exist , Enter Account Number: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults saveResult;

		saveResult = NewClient.save();

		switch (saveResult)
		{
		case clsBankClient::svFaildEmptyObject:
			cout << "\nError account was not saved because it's Empty";
			break;
		case clsBankClient::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";
			_Print(NewClient);
			break;
		case clsBankClient::svFaildAccountNumberExists:
			cout << "\nError account was not saved because account number is used!\n";
			break;
		default:
			break;
		}
	}

};


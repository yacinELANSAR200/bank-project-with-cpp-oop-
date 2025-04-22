#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iostream>
#include <string>
#include <iomanip>


class clsUpdateClientScreen:clsScreen
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
	static void UpdateClient() {
		if (!_CheckAccessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;
		}
		_DrawScreenHeader("\t Update Client Screen");

		string AccountNumber = "";
		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient not Exist , Enter Account Number: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_Print(Client1);

		cout << "\n\nUpdate Client Info:";
		cout << "\n____________________\n";

		_ReadClientInfo(Client1);

		clsBankClient::enSaveResults saveResult;

		saveResult = Client1.save();

		switch (saveResult)
		{
		case clsBankClient::svFaildEmptyObject:
			cout << "\nError account was not saved because it's Empty";
			break;
		case clsBankClient::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";
			_Print(Client1);
			break;
		default:
			break;
		}
	}

};


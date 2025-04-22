#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <string>
#include <iomanip>


class clsFindClientScreen:protected clsScreen
{
private:
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
	static void FindClient() {
		if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}
		_DrawScreenHeader("\t Find Client Screen");
		string AccountNumber = "";
		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient not Exist , Enter Account Number: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		
		if (!Client1.IsEmpty())
		{
		_Print(Client1);
		}
		else {
			cout << "Client Not Found\n";
		}
	}
};


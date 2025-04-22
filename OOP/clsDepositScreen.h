#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsInputValidate.h"

class clsDepositScreen:protected clsScreen
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

	static string _ReadAccountNumber() {
		cout << "Please Enter Account Number: ";
		return clsInputValidate::ReadString();
	}
public:
	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t Deposit Screen");

		string AccountNumber = _ReadAccountNumber();
		
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber =_ReadAccountNumber();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		if (!Client1.IsEmpty())
		{
			_Print(Client1);
		}
		
		double Amount = 0;
		cout << "\nPlease enter deposit amount? ";
		Amount = clsInputValidate::ReadNumber<double>();

		cout << "Are you Sure you want to perform this transaction? ";
		
	
		char Answer='n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Client1.Deposit(Amount);
			cout << "\nNew Balance Is: " << Client1.AccountBalance;
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};


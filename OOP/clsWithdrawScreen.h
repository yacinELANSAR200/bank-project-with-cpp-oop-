#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
class clsWithdrawScreen :protected clsScreen
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
	static void ShowWithdrawScreen() {
		_DrawScreenHeader("\t Withdraw Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		if (!Client1.IsEmpty())
		{
			_Print(Client1);
		}
		double Amount = 0;

		cout << "\nPlease enter withdraw amount? ";
		Amount = clsInputValidate::ReadNumber<double>();
		while (Amount>Client1.AccountBalance)
		{
			cout << "\nInsuffecient Balance!Please enter another withdraw amount? ";
			Amount = clsInputValidate::ReadNumber<double>();
		}

		cout << "Are you Sure you want to perform this transaction? ";


		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client1.WithDraw(Amount))
			{
				cout << "\nAmount Withdraw Successfully";
				cout << "\nNew Balance is " << Client1.AccountBalance << endl;
			}
			else 
			{
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmout to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client1.AccountBalance;
			}
		}
		else 
		{
			cout << "\nOperation was cancelled.\n";
		}
		
	}
};


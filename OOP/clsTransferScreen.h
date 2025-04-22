#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferScreen:protected clsScreen
{
private:
	static void _Print(clsBankClient Client) {
		cout << "\n============Client Card============\n";
		cout << "\nFull  Name: " << Client.FullName();
		cout << "\nAcc Number: " << Client.GetAccountNumber();
		cout << "\nBalance   : " << Client.AccountBalance;
		cout << "\n==================================\n";
	}
	static string _ReadAccountNumber(string Message) {
		string AccountNumber = "";
		cout << Message;
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient not Exist , Enter Account Number: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;


		
		
	}
	static double _ReadAmount(clsBankClient SourceClient) 
	{
		cout << "\nEnter Transfer Amount: ";
		double TransferAmount = clsInputValidate::ReadNumber<double>();
		while (TransferAmount > SourceClient.AccountBalance) {
			cout << "\nAmount Exceeds the available Balance,Enter another Amount? ";
			TransferAmount = clsInputValidate::ReadNumber<double>();

		}
		return TransferAmount;
	}
public :
	static void ShowTransferScreen() {
		_DrawScreenHeader("\t Transfer Screen");
		
		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Transfer From: "));

		_Print(SourceClient);
		
		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Transfer To: "));

		if (SourceClient.GetAccountNumber() == DestinationClient.GetAccountNumber()) {
			cout << "\nYou cannot deposit an amount into the account you want to withdraw from!  ";
			//clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Transfer To: "));
			return;
		}
		_Print(DestinationClient);

		double TransferAmount=_ReadAmount(SourceClient);
		

		char Answer = 'n';
		cout << "Are you Sure you want to perform this operation? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (SourceClient.Transfer(TransferAmount,DestinationClient,CurrentUser.UserName))
			{
				cout << "\n\nTransfer Done Successfully\n\n";
				
			}
			else
			{
				cout << "\n\nTransfer Failed\n\n";
			}
		}
		else
		{
			cout << "\n\nOperation was cancelled.\n";
		}
		
		_Print(SourceClient);
		_Print(DestinationClient);
		


	}
};


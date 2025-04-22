#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include <iomanip>
class clsTotalBalancesScreen:protected clsScreen
{
private:
	static void PrintClientRecord(clsBankClient Client) {
		cout << setw(32) << left << "" << "|" << left << setw(15) << Client.GetAccountNumber();
		cout << "|" << left << setw(20) << Client.FullName();
		cout << "|" << left << setw(12) << Client.AccountBalance;
	}
public:
	static void ShowTotalBalancesScreen() {
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t\tTotal Balances";
		string SubTitle = "\t\t(" + to_string(vClients.size()) + ")" + "Clients";
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t______________________________________________________";
		cout << "______________________________________________________\n";

		cout << setw(32) << left << "" << "| " << left << setw(15) << "AccountNumber";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "AccountBalance";
		cout << setw(8) << left << "" << "\n\t______________________________________________________";
		cout << "______________________________________________________\n";

		if (vClients.size() == 0)
			cout << "\n\t\t\t\t\tNo clients available in the system\n";
		else
			for (clsBankClient& C : vClients) {
				PrintClientRecord(C);
				cout << endl;
			}
		cout << setw(8) << left << "" << "\n\t______________________________________________________";
		cout << "______________________________________________________\n";
		cout << "\t\t\t\t\tTotal Balance=" << clsBankClient::GetTotalBalances() << "\n";

		double TotalBalance = clsBankClient::GetTotalBalances();

		cout << "\t\t\t\t\t" << clsUtil::NumberToText(TotalBalance) << "\n";
	}
};


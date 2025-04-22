#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUser.h"

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class clsClientsListScreen :clsScreen
{
private:
	static void PrintClientRecord(clsBankClient Client) {
		cout << setw(8)<<left <<"" << "|" << left << setw(15) << Client.GetAccountNumber();
		cout << "|" << left << setw(20) << Client.FullName();
		cout << "|" << left << setw(12) << Client.Phone;
		cout << "|" << left << setw(25) << Client.Email;
		cout << "|" << left << setw(10) << Client.PinCode;
		cout << "|" << left << setw(12) << Client.AccountBalance;
	}
public:
	static void ShowClientsList() {
		if (!_CheckAccessRights(clsUser::enPermissions::pListClients))
		{
			return;
		}
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t\tClients List";
		string SubTitle = "\t\t(" + to_string(vClients.size()) + ")" + "Clients";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8)<<left<< "" << "\n\t______________________________________________________";
		cout << "______________________________________________________\n";

		cout <<setw(8)<<left<<"" << "| " << left << setw(15) << "AccountNumber";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(25) << "Email";
		cout << "| " << left << setw(10) << "PinCode";
		cout << "| " << left << setw(12) << "AccountBalance";
		cout << setw(8) << left << ""<< "\n\t______________________________________________________";
		cout << "______________________________________________________\n";

		if (vClients.size() == 0)
			cout << "\n\t\t\t\t\tNo clients available in the system\n";
		else
			for (clsBankClient& C : vClients) {
				PrintClientRecord(C);
				cout << endl;
			}
	}
};


#pragma once
#include "clsScreen.h"
#include "clsString.h"
#include "clsBankClient.h"
#include <vector>
#include <iomanip>
class clsTransferLogScreen :protected clsScreen
{
private:

	static void PrintTransferLogRecord(clsBankClient::stTransferLog TransferLogRecord) {
		cout << setw(8) << left << "" << "| " << left << setw(25) << TransferLogRecord.DateTime;
		cout << "| " << left << setw(10) << TransferLogRecord.AccountFrom;
		cout << "| " << left << setw(10) << TransferLogRecord.AccountTo;
		cout << "| " << left << setw(10) << TransferLogRecord.Amount;
		cout << "| " << left << setw(12) << TransferLogRecord.AccountBalanceSource;
		cout << "| " << left << setw(12) << TransferLogRecord.AccountBalanceDestination;
		cout << "| " << left << setw(15) << TransferLogRecord.User;

	}
public:
	static void ShowTransferLogScreen()
	{
		if (!_CheckAccessRights(clsUser::pLoginRegister))
		{
			return;
		}
		vector<clsBankClient::stTransferLog> vTransferLogData = clsBankClient::GetTransferLogList();
		string Title = "\t\Transfer Log List Screen";
		string SubTitle = "\t\t(" + to_string(vTransferLogData.size()) + ")" + "Record(s)";
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_________________________________________________";
		cout << "_________________________________________________\n";

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acct";
		cout << "| " << left << setw(10) << "d.Acct";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(12) << "s.Balance";
		cout << "| " << left << setw(12) << "d.Balance";
		cout << "| " << left << setw(15) << "User";
		cout << setw(8) << left << "" << "\n\t_________________________________________________";
		cout << "_________________________________________________\n";

		if (vTransferLogData.size() == 0)
			cout << "\n\t\t\t\t\tNo Records available in the system\n";
		else
			for (clsBankClient::stTransferLog& Record : vTransferLogData) {
				PrintTransferLogRecord(Record);
				cout << endl;
			}
	}
};



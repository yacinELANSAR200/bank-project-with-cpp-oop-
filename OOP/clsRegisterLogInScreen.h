#pragma once
#include "clsScreen.h"
#include "clsString.h"
#include "clsUser.h"
#include <vector>


class clsRegisterLogInScreen:protected clsScreen
{
private:
	
	 static void PrintRegisterLoginRecord(clsUser::sLoginRegisterRecord LoginRecord) {
		 cout << setw(8) << left << "" << "| " << left << setw(25) << LoginRecord.DateTime;
		 cout << "| " << left << setw(20) << LoginRecord.UserName;
		 cout << "| " << left << setw(12) << LoginRecord.Password;
		 cout << "| " << left << setw(25) << LoginRecord.Permissions;
	
	}
public:
	static void ShowLoginRegisterScreen() 
	{
		if (!_CheckAccessRights(clsUser::pLoginRegister))
		{
			return;
		}
		vector<clsUser::sLoginRegisterRecord> vLoginRegisterData = clsUser::GetLoginRegisterList();
		string Title = "\t\Login Register List Screen";
		string SubTitle = "\t\t(" + to_string(vLoginRegisterData.size()) + ")" + "Record(s)";
		_DrawScreenHeader(Title,SubTitle);
		
		cout << setw(8) << left << "" << "\n\t______________________________________";
		cout << "______________________________________\n";

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(20) << "User Name";
		cout << "| " << left << setw(12) << "Password";
		cout << "| " << left << setw(25) << "Permissions";
		cout << setw(8) << left << "" << "\n\t______________________________________";
		cout << "______________________________________\n";

		if (vLoginRegisterData.size() == 0)
			cout << "\n\t\t\t\t\tNo Records available in the system\n";
		else
			for (clsUser::sLoginRegisterRecord&  Record: vLoginRegisterData) {
				PrintRegisterLoginRecord(Record);
				cout << endl;
			}
	}
};


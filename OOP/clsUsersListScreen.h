#pragma once

#include "clsScreen.h"
#include "clsUser.h"
#include <iostream>
#include <string>
#include <iomanip>
class clsUsersListScreen:protected clsScreen
{
private:
	static void PrintUserRecord(clsUser User) {
		cout << setw(8) << left << "" << "| " << left << setw(12) << User.UserName;
		cout << "| " << left << setw(25) << User.FullName();
		cout << "| " << left << setw(12) << User.Phone;
		cout << "| " << left << setw(25) << User.Email;
		cout << "| " << left << setw(10) << User.Password;
		cout << "| " << left << setw(12) << User.Permissions;
	}
public:
	static void ShowUsersList() {
		{
			vector <clsUser> vUsers = clsUser::GetUsersList();

			string Title = "\t\tUsers List";
			string SubTitle = "\t\t(" + to_string(vUsers.size()) + ")" + "Users";

			_DrawScreenHeader(Title, SubTitle);

			cout << setw(8) << left << "" << "\n\t______________________________________________________";
			cout << "______________________________________________________\n";

			cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
			cout << "| " << left << setw(25) << "Full Name";
			cout << "| " << left << setw(12) << "Phone";
			cout << "| " << left << setw(25) << "Email";
			cout << "| " << left << setw(10) << "Password";
			cout << "| " << left << setw(12) << "Permessions";
			cout << setw(8) << left << "" << "\n\t______________________________________________________";
			cout << "______________________________________________________\n";
			
			
			if (vUsers.size() == 0)
				cout << "\n\t\t\t\t\tNo Users available in the system\n";
			else
				for (clsUser& U : vUsers) {
					PrintUserRecord(U);
					cout << endl;
				}
			cout << setw(8) << left << "" << "\n\t______________________________________________________";
			cout << "______________________________________________________\n";

		}
	}
};


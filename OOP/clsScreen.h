#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;
class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\t\t\t\t\t______________________________________";
		cout << "\n\n\t\t\t\t\t " << Title;
		if (SubTitle != "") {
			cout << "\n\t\t\t\t\t " << SubTitle;
		}
		cout << "\n\t\t\t\t\t______________________________________\n\n";
		if (!CurrentUser.IsEmpty())
		{
		cout << "\t\t\t\t\tUser: " << CurrentUser.UserName << endl;
		}
		//cout << "\t\t\t\t\tDate: "<< clsDate::GetSystemDate().DateToString() << endl;
		cout << "\t\t\t\t\tDate: "<< clsDate::DateToString(clsDate()) ;
		cout << "\n\n";

	}
	static bool _CheckAccessRights(clsUser::enPermissions Permissions) {
		if (!CurrentUser.CheckPermissions(Permissions))
		{
			cout << "\t\t\t\t\t______________________________________";
			cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
			cout << "\n\t\t\t\t\t______________________________________\n\n";
			return false;
		}
		else 
		{
			return true;
		}
	}
};


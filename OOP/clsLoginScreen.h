#pragma once
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "Global.h"
class clsLoginScreen:protected clsScreen
{
private:
	

	static bool  _Login() {
		bool LoginFailed = false;
		short FailedLoginCounter = 0;
		string UserName, Password;
		do
		{
			if (LoginFailed) {
				FailedLoginCounter++;
				system("cls");
				_DrawScreenHeader("\t Login Screen");
				cout << "Invalid UserName or password\n";
				cout << "You have " << 3- FailedLoginCounter << " trial(s) To login\n";
				if (FailedLoginCounter ==3)
				{
					cout << "You are locked after 3 Trials\n"; 
					return false;
				}
			}

			cout << "Enter User Name: ";
			cin >> UserName;
			cout << "Enter Password: ";
			cin >> Password;

			while (UserName.length() == 0 || Password.length() == 0)
			{
				cout << "Username or password can not be empty!\n";
				cout << "Enter User Name: ";
				cin >> UserName;
				cout << "Enter Password: ";
				cin >> Password;
			}

			CurrentUser = clsUser::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();

				
		} while (LoginFailed);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenueScreen();

		return true;
		
	}
public:
	static bool ShowLoginScreen() {
		
		system("cls");
		_DrawScreenHeader("\t Login Screen");
		return _Login();
	}
};


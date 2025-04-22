#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClient.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsRegisterLogInScreen.h"
#include "clsCurrencyExchangeScreen.h"

#include <iomanip>
class clsMainScreen:protected clsScreen
{
private:
	enum enMainMenueOptions{
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7,eLoginRegister=8,eCurrencyExchange=9, eExit = 10
	};

	static short _ReadMainMenueOption() {
		cout << setw(37) << left<<"" << "Choose what do you want to do? [1 to 10]? ";
		short Option = clsInputValidate::ReadNumberBetween<short>(1, 10);
		return Option;
	}

	static void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\nPress Any Key to go back to Main Menue...";
		system("pause>0");
		ShowMainMenueScreen();
	}

	static void _ShowAllClientsScreen()
	{
		//cout << "\nClient List Screen Will be here...\n";
		clsClientsListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		//cout << "\nAdd New Client Screen Will be here...\n";
		clsAddNewClient::AddNewClient();

	}

	static void _ShowDeleteClientScreen()
	{
		//cout << "\nDelete Client Screen Will be here...\n";
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		//cout << "\nUpdate Client Screen Will be here...\n";
		clsUpdateClientScreen::UpdateClient();
	}

	static void _ShowFindClientScreen()
	{
		//cout << "\nFind Client Screen Will be here...\n";
		clsFindClientScreen::FindClient();
	}

	static void _ShowTransactionsMenue()
	{
		//cout << "\nTransactions Menue Will be here...\n";
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenue()
	{
		//cout << "\nUsers Menue Will be here...\n";
		clsManageUsersScreen::ShowManageUsersMenue();

	}

	/*static void _ShowEndScreen()
	{
		cout << "\nEnd Screen Will be here...\n";

	}*/
	static void _Logout() {
		CurrentUser = clsUser::Find("","");
	}
	static void _ShowLoginRegisterScreen() {
		clsRegisterLogInScreen::ShowLoginRegisterScreen();
	}
	
	static void _ShowCurrencyExchangeScreen() {
		clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
	}

	static void _PerformMainMenueOption(enMainMenueOptions option) {
		switch (option)
		{
		case clsMainScreen::eListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::eAddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::eShowTransactionsMenue:
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::eManageUsers:
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::eLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
		case clsMainScreen::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenue();
		case clsMainScreen::eExit:
			system("cls");
			_Logout();
			break;
		default:
			break;
		}
	}
public:
	static void ShowMainMenueScreen() 
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");
		cout << left << setw(37) << "" << "===========================================\n";
		cout << left << setw(37) << "" << "\t\t\tMain Menue\n";
		cout << left << setw(37) << "" << "===========================================\n";
		cout << left << setw(37) << "" <<"\t[1]Show Client List." << "\n";
		cout << left << setw(37) << "" <<"\t[2]Add New Client." << "\n";
		cout << left << setw(37) << "" <<"\t[3]Delete Client" << "\n";
		cout << left << setw(37) << "" <<"\t[4]Update Client." << "\n";
		cout << left << setw(37) << "" <<"\t[5]Find Client." << "\n";
		cout << left << setw(37) << "" <<"\t[6]Transactions." << "\n";
		cout << left << setw(37) << "" <<"\t[7]Manage Users." << "\n";
		cout << left << setw(37) << "" <<"\t[8]Login register." << "\n";
		cout << left << setw(37) << "" <<"\t[9]Currency Exchange" << "\n";
		cout << left << setw(37) << "" <<"\t[10]Logout" << "\n";
		cout << left << setw(37) << "" << "===========================================\n";
		_PerformMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}
};


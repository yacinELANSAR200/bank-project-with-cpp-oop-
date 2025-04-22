#pragma once
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"

#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionsScreen:protected clsScreen
{
private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eTransfer=4,eTransferLog=5,eShowMainMenue = 6
    };
    static short _ReadTransactionsMenueOption(){
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Option = clsInputValidate::ReadNumberBetween<short>(1, 6);
        return Option;
    }
	static void _ShowDepositScreen()
	{
		//cout << "\n Deposit Screen will be here.\n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		//cout << "\n Withdraw Screen will be here.\n";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		//cout << "\n Balances Screen will be here.\n";
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}
	static void _ShowTransferScreen() {
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
		ShowTransactionsMenue();

	}
	static void _PerformTransactionMenueOption(enTransactionsMenueOptions TransactionsOptions) {
		switch (TransactionsOptions)
		{
		case clsTransactionsScreen::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eShowTotalBalance:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();

		case clsTransactionsScreen::eShowMainMenue:
			system("cls");
			break;
		default:
			break;
		}
	}
public:
	static void ShowTransactionsMenue()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pTranactions))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("\t\tTransactions Screen");
		cout << left << setw(37) << "" << "===========================================\n";
		cout << left << setw(37) << "" << "\t\t\Transactions Menue\n";
		cout << left << setw(37) << "" << "===========================================\n";
		cout << left << setw(37) << "" << "\t[1]Deposit." << "\n";
		cout << left << setw(37) << "" << "\t[2]Withdraw." << "\n";
		cout << left << setw(37) << "" << "\t[3]Total Balances" << "\n";
		cout << left << setw(37) << "" << "\t[4]Transfer" << "\n";
		cout << left << setw(37) << "" << "\t[5] Transfer Log." << "\n";
		cout << left << setw(37) << "" << "\t[6] Main Menue." << "\n";
		cout << left << setw(37) << "" << "===========================================\n";
		_PerformTransactionMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
	}
        
    
};


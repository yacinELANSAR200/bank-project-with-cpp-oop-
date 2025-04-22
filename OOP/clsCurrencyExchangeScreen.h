#pragma once
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen:protected clsScreen
{
private:
	enum enCurrencyExchangeMenueOptions { eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenue = 5 };
	
	static short _ReadCurrencyExchangeMenueOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Option = clsInputValidate::ReadNumberBetween<short>(1, 5);
		return Option;
	}

	static void _ShowListCurrenciesScreen() {
		clsCurrenciesListScreen::_ShowListCurrenciesScreen();
	}
	
	static void _ShowFindCurrencyScreen() {
		clsFindCurrencyScreen::_ShowFindCurrencyScreen();
	}
	
	static void _ShowUpdateRateScreen() {
		clsUpdateCurrencyScreen::_ShowUpdateRateScreen();

	}
	
	static void _ShowCurrencyCalculatorScreen() {
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _GoBackToExchangeMenueMenue()
	{
		cout << "\n\nPress any key to go back to Exchang Menue...";
		system("pause>0");
		ShowCurrencyExchangeScreen();
	}

	static void _PerformExchangeMenueOption(enCurrencyExchangeMenueOptions ExchangeMenueOptions) {
		switch (ExchangeMenueOptions)
		{
		case clsCurrencyExchangeScreen::eListCurrencies:
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToExchangeMenueMenue();
			break;
		case clsCurrencyExchangeScreen::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToExchangeMenueMenue();
			break;
		case clsCurrencyExchangeScreen::eUpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToExchangeMenueMenue();
			break;
		case clsCurrencyExchangeScreen::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToExchangeMenueMenue();
			break;
		case clsCurrencyExchangeScreen::eMainMenue:
			break;
		default:
			break;
		}
	}
public:
	static void ShowCurrencyExchangeScreen() {
		system("cls");
		_DrawScreenHeader("\t\tCurrency Exchange Main Screen");
		cout << left << setw(37) << "" << "===========================================\n";
		cout << left << setw(37) << "" << "\t\t\Currency Exchange Menue\n";
		cout << left << setw(37) << "" << "===========================================\n";
		cout << left << setw(37) << "" << "\t[1]List Currencies." << "\n";
		cout << left << setw(37) << "" << "\t[2]Find Currency." << "\n";
		cout << left << setw(37) << "" << "\t[3]Update Rate" << "\n";
		cout << left << setw(37) << "" << "\t[4]Currency Calculator" << "\n";
		cout << left << setw(37) << "" << "\t[5] Main Menue." << "\n";
		cout << left << setw(37) << "" << "===========================================\n";
		_PerformExchangeMenueOption((enCurrencyExchangeMenueOptions)_ReadCurrencyExchangeMenueOption());
	}
};


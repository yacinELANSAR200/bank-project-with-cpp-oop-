#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
class clsCurrenciesListScreen:clsScreen
{
private:
	static void PrintClientRecord(clsCurrency Currency) {
		cout << setw(8) << left << "" << "| " << left << setw(27) << Currency.GetCountry();
		cout << "| " << left << setw(10) <<Currency.GetCurrencyCode();
		cout << "| " << left << setw(40) <<Currency.GetCurrencyName();
		cout << "| " << left << setw(20) <<Currency.GetRate();
	
	}
public:
	static void _ShowListCurrenciesScreen() {
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string Title = "\t\tCurrencies List Screen";
		string SubTitle = "\t\t(" + to_string(vCurrencies.size()) + ")" + "Currency";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t________________________________________________";

		cout << setw(8) << left << "" << "| " << left << setw(27) << "Country";
		cout << "| " << left << setw(10) << "Code";
		cout << "| " << left << setw(40) << "Name";
		cout << "| " << left << setw(20) << "Rate/(1$)";
	

		cout << setw(8) << left << "" << "\n\t________________________________________________";
		cout << "________________________________________________\n";

		if (vCurrencies.size() == 0)
			cout << "\n\t\t\t\t\tNo Currency available in the system\n";
		else
			for (clsCurrency& C : vCurrencies) {
				PrintClientRecord(C);
				cout << endl;
			}

		cout << "________________________________________________\n";cout << setw(8) << left << "" << "\n\t________________________________________________";
		cout << "________________________________________________\n";
	}
};


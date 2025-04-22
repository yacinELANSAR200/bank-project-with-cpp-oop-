#pragma once 
#include "clsScreen.h"
#include "clsCurrency.h"
class clsUpdateCurrencyScreen:clsScreen
{
private:
	static void _Print(clsCurrency currency) {
		cout << "\n============Currency Card============\n";
		cout << "\nCountry: " << currency.GetCountry();
		cout << "\nCode   : " << currency.GetCurrencyCode();
		cout << "\nName   : " << currency.GetCurrencyName();
		cout << "\nRate   : " << currency.GetRate();
		cout << "\n==================================\n";
	}
	static void _ShowResults(clsCurrency Currency) {
		if (!Currency.IsEmpty())
		{
			_Print(Currency);
		}
		else {
			cout << "Currency is not found";
		}
	}
	static float _ReadRate() {
		cout << "\nEnter New Rate: ";
		float Rate =clsInputValidate::ReadNumber<float>();
		return Rate;
	}
public:
	static void _ShowUpdateRateScreen() {
		_DrawScreenHeader("\t Update Currency Screen");

		string CountryCode = "";
		cout << "Please Entry Country Code? ";
		CountryCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExistByCode(CountryCode))
		{
			cout << "\Country Code not Exist , Enter another Country Code: ";
			CountryCode = clsInputValidate::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CountryCode);

		_ShowResults(Currency);


		char Answer = 'n';
		cout << "Are you sure you want to update the rate of this currency y/n? ";
		cin >> Answer;

		if (Answer=='Y'||Answer=='y')
		{
			
			Currency.UpdateRate(_ReadRate());
			cout << "Currency Rate Updated Succefully :-)\n";
			_ShowResults(Currency);
			
		}
		else {
			cout << "\nOperation was cancelled!\n";
		}
	}
};


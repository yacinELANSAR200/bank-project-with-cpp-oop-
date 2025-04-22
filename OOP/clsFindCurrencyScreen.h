#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
class clsFindCurrencyScreen:protected clsScreen
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
public:
	static void _ShowFindCurrencyScreen() {
		_DrawScreenHeader("\t Find Currency Screen");
		
		cout << "Find By: [1] Country or [2] Code? ";
		short Option = clsInputValidate::ReadNumberBetween<short>(1, 2);

		if (Option==1)
		{
			string CountryName="";
			cout << "Please Entry Country Name? ";
			CountryName = clsInputValidate::ReadString();
			while (!clsCurrency::IsCurrencyExistByCountry(CountryName))
			{
				cout << "\Country Name not Exist , Enter another Country Name: ";
				CountryName = clsInputValidate::ReadString();
			}
			clsCurrency Currency = clsCurrency::FindByCountry(CountryName);

			if (!Currency.IsEmpty())
			{
				_Print(Currency);
			}
		}
		else 
		{
			string CountryCode = "";
			cout << "Please Entry Country Code? ";
			CountryCode = clsInputValidate::ReadString();
			while (!clsCurrency::IsCurrencyExistByCode(CountryCode))
			{
				cout << "\Country Code not Exist , Enter another Country Code: ";
				CountryCode = clsInputValidate::ReadString();
			}
			clsCurrency Currency = clsCurrency::FindByCode(CountryCode);

			if (!Currency.IsEmpty())
			{
				_Print(Currency);
			}
		}
	}
};


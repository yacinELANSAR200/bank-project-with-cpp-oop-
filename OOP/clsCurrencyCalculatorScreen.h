//#pragma once
//#include "clsScreen.h"
//#include "clsCurrency.h"
//class clsCalculatorScreen :clsScreen
//{
//private:
//	static void _PrintCurrency(clsCurrency currency) {
//		cout << "\n============Currency Card============\n";
//		cout << "\nCountry: " << currency.GetCountry();
//		cout << "\nCode   : " << currency.GetCurrencyCode();
//		cout << "\nName   : " << currency.GetCurrencyName();
//		cout << "\nRate   : " << currency.GetRate();
//		cout << "\n==================================\n";
//	}
//	
//	static clsCurrency _GetCurrency(string Message)
//	{
//		string CurrencyCode = "";
//		cout << Message;
//		CurrencyCode = clsInputValidate::ReadString();
//
//		while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
//		{
//			cout << "\Currency Code not Exist , Enter another Currency Code: ";
//			CurrencyCode = clsInputValidate::ReadString();
//		}
//		clsCurrency Currency=clsCurrency::FindByCode(CurrencyCode);
//		return Currency;
//	}
//
//	
//	static float _ReadAmountToExchange() {
//		cout << "\nEnter Amount to Exchange: ";
//		float Amount = clsInputValidate::ReadFloatNumber();
//		return Amount;
//	}
//
//	static void _PrintExchangeResult(float Amount,clsCurrency Currency1,float AmountAfterExchange,clsCurrency Currency2) {
//		cout << to_string(Amount) << " " << Currency1.GetCurrencyCode() << " = " << AmountAfterExchange <<" " << Currency2.GetCurrencyCode();
//	}
//	static void _PrintExchangeResultFromCurrencyToUsd(float Amount, clsCurrency Currency1) {
//		cout << endl<< to_string(Amount) << " " << Currency1.GetCurrencyCode() << " = " << Currency1.ConvertCurrencyToUsd(Amount,Currency1.GetRate()) << " USD" <<endl;
//
//	}
//public:
//	static void _ShowCurrencyCalculatorScreen() {
//		char Answer = 'y';
//		while (Answer == 'y' || Answer == 'Y')
//		{
//			system("cls");
//			_DrawScreenHeader("\t\t Calculator Screen");
//
//			clsCurrency Currency1 = _GetCurrency("Please Enter Currency1 code: ");
//
//			clsCurrency Currency2 = _GetCurrency("Please Enter Currency2 code: ");
//
//			float Amount = _ReadAmountToExchange();
//			float AmountAfterExchange = Currency1.CalculateAmountAfterExchange(Amount, Currency2);
//
//			if (Currency1.GetCurrencyCode() != "USD" && Currency2.GetCurrencyCode() != "USD")
//			{
//				cout << "Convert From:\n";
//				_PrintCurrency(Currency1);
//				_PrintExchangeResultFromCurrencyToUsd(Amount, Currency1);
//				cout << "Convert To:\n";
//				_PrintCurrency(Currency2);
//				_PrintExchangeResult(Amount, Currency1, AmountAfterExchange, Currency2);
//			}
//			else
//			{
//				cout << "Convert From:\n";
//				_PrintCurrency(Currency1);
//				_PrintExchangeResult(Amount, Currency1, AmountAfterExchange, Currency2);
//			}
//			cout << "\n\nDo you want to perform another calculation y/n?";
//			cin>>Answer;
//		} ;
//		
//		
//		
//
//
//	}
//};
//
#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen :protected clsScreen

{
private:

    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = clsInputValidate::ReadNumber<float>();
        return Amount;
    }

    static clsCurrency _GetCurrency(string Message)
    {

        string CurrencyCode;
        cout << Message << endl;

        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;

    }


    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.GetCountry();
        cout << "\nCode          : " << Currency.GetCurrencyCode();
        cout << "\nName          : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) =    : " << Currency.GetRate();
        cout << "\n_____________________________\n\n";

    }

    static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {

        _PrintCurrencyCard(Currency1, "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.GetCurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (Currency2.GetCurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");

        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

        cout << Amount << " " << Currency1.GetCurrencyCode()
            << " = " << AmountInCurrency2 << " " << Currency2.GetCurrencyCode();
    }


public:

    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");

            _DrawScreenHeader("\tUpdate Currency Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;

        }


    }
};


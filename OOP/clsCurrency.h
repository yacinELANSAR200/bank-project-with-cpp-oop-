#pragma once
#include<iostream>
#include<string>
#include "clsString.h"
#include <vector>
#include <fstream>
class clsCurrency
{
private:
	enum enMode { EmptyMode = 1, UpdateMode = 2 };
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float  _Rate;

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode,"","","",0);
	}
	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#") {
		vector<string> vCurrencyData;
        vCurrencyData = clsString::Split(Line, Separator);

        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
            stof(vCurrencyData[3]));
	}
	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{
		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.GetCountry() + Seperator;
		stCurrencyRecord += Currency.GetCurrencyCode() + Seperator;
		stCurrencyRecord += Currency.GetCurrencyName() + Seperator;
		stCurrencyRecord += to_string(Currency.GetRate());

		return stCurrencyRecord;

	}
	static  vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{	
		vector <clsCurrency> vCurrencies;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrency Currency=_ConvertLineToCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencies;
	}
	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencies) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open())
		{
			string DataLine;
			for (clsCurrency& C : vCurrencies) {
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}
	void _Update()
	{
		vector <clsCurrency>vCurrencies = _LoadCurrenciesDataFromFile();
		for (clsCurrency& C : vCurrencies) {

			if (C.GetCurrencyCode()==GetCurrencyCode())
			{
				if (C.GetCurrencyCode()!="EUR")
				{
					C = *this; 
					break;
				}
				C._Rate = _Rate;

			}
		}
		_SaveCurrencyDataToFile(vCurrencies);
	}
public:
	clsCurrency(enMode Mode,string Country,string CurrencyCode,string CurrencyName,float Rate)
	{
		_Mode=Mode;
		_Country=Country;
		_CurrencyCode= CurrencyCode;
		_CurrencyName= CurrencyName;
		_Rate= Rate;
	}
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}
	string GetCountry(){
		return _Country;
	 }
	string GetCurrencyCode() {
		return _CurrencyCode;
	}
	string GetCurrencyName() {
		return _CurrencyName;
	}
	float GetRate() {
		return _Rate;
	}
	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}
	__declspec(property(get = GetRate, put = setRate))float Rate;

	static  clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			 
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.GetCurrencyCode()) == CurrencyCode)
				{
					return Currency;
					MyFile.close();
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}
	
	static  clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			 
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.GetCountry()) == Country)
				{
					return Currency;
					MyFile.close();
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}
	static bool IsCurrencyExistByCode(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}
	static bool IsCurrencyExistByCountry(string CountryName)
	{
		clsCurrency Currency = clsCurrency::FindByCountry(CountryName);
		return (!Currency.IsEmpty());
	}
	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	 /*float ConvertCurrencyToUsd(float Amount, float Rate)
	{
		return Amount / Rate;
	}
	
	 float ConvertUsdToCurrency(float Amount, float Rate)
	{
		return Amount * Rate;
	}
	
	 float CalculateAmountAfterExchange(float Amount,clsCurrency CurrencyCodeDestination) {
		if (CurrencyCodeDestination.GetCurrencyCode() == "USD" && GetCurrencyCode()!="USD")
		{
			return ConvertCurrencyToUsd(Amount, GetRate());
		}
		else if (CurrencyCodeDestination.GetCurrencyCode() != "USD" && GetCurrencyCode() == "USD")
		{
			return ConvertUsdToCurrency(Amount, CurrencyCodeDestination.GetRate());
		}
		else 
		{
			float SourceCurrencyToUSD= ConvertCurrencyToUsd(Amount, GetRate());
			return ConvertUsdToCurrency(SourceCurrencyToUSD, CurrencyCodeDestination.GetRate());
		}
	}*/

	 float ConvertToUSD(float Amount)
	 {
		 return (float)(Amount / GetRate());
	 }

	 float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	 {
		 float AmountInUSD = ConvertToUSD(Amount);

		 if (Currency2.GetCurrencyCode() == "USD")
		 {
			 return AmountInUSD;
		 }

		 return (float)(AmountInUSD * Currency2.GetRate());

	 }

};


#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
class clsInputValidate
{

public:
	
	template <typename T>
	static bool IsNumberBetween(T Number, T From, T To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	/*static bool IsNumberBetween(int Number, int From, int To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;

	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}*/

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		//Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			)
		{
			return true;
		}

		//Date>=To && Date<=From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;
	}

	template <typename T>
	static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		T Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	//static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
	//	float Number;
	//	while (!(cin >> Number)) {
	//		cin.clear();
	//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//		cout << ErrorMessage;
	//	}
	//	return Number;
	//}
	
	template <typename T>
	static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		T Number = ReadNumber<T>();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			 Number = ReadNumber<T>();
		}
		return Number;
	}

	//static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	//{
	//	double Number;
	//	while (!(cin >> Number)) {
	//		cin.clear();
	//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//		cout << ErrorMessage;
	//	}
	//	return Number;
	//}

	//static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	//{
	//	double Number = ReadDblNumber();

	//	while (!IsNumberBetween(Number, From, To)) {
	//		cout << ErrorMessage;
	//		Number = ReadDblNumber();
	//	}
	//	return Number;
	//}

	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}

	static string ReadString() {
		string S1="";
		getline(cin>>ws , S1);
		return S1;
	}
};


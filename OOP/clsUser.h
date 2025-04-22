#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsDate.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>
class clsUser :public clsPerson
{
private:
	enum enMode
	{
		EmptyMode = 0, UpdateMode = 1, AddNewMode = 2,
	};
	enMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkForDelete = false;

	struct sLoginRegisterRecord;

	static sLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Separator = "#//#")
	{
		sLoginRegisterRecord LoginRegisterData;
		vector<string> vLoginRegisterData = clsString::Split(Line, Separator);
		LoginRegisterData.DateTime = vLoginRegisterData[0];
		LoginRegisterData.UserName = vLoginRegisterData[1];
		LoginRegisterData.Password = clsUtil::DecryptText(vLoginRegisterData[2],4);
		LoginRegisterData.Permissions = stoi(vLoginRegisterData[3]);
		return LoginRegisterData;
	}
	 string _PrepareLogInRecord( string Seperator = "#//#") {
		string LogInRecord= "";
		LogInRecord += clsDate::GetSystemDateTimeInString() + Seperator;
		LogInRecord += UserName + Seperator;
		LogInRecord += clsUtil::EncryptText(Password,4)+Seperator;
		LogInRecord += to_string(Permissions);
		return LogInRecord;
	}
	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#") {
		vector<string> vUserData = clsString::Split(Line, Seperator);
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5],4), stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#") {
		string stUserRecord = "";
		stUserRecord += User.FirstName + Seperator;
		stUserRecord += User.LastName + Seperator;
		stUserRecord += User.Email + Seperator;
		stUserRecord += User.Phone + Seperator;
		stUserRecord += User.UserName + Seperator;
		stUserRecord += clsUtil::EncryptText(User.Password,4) + Seperator;
		stUserRecord += to_string(User.Permissions) ;
		return stUserRecord;

	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsUser> _LoadUsersDataFromFile() {
		fstream MyFile;
		vector <clsUser> vUsers;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}

	static void _SaveUsersDataToFile(vector<clsUser> vUsers, string Seperator = "#//#") {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		string DataLine = "";
		if (MyFile.is_open())
		{
			for (clsUser& U : vUsers) {
				if (U.GetMarkForDelete() == false)
				{
					//we store only Users with MarkForDelete property is false
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}
		}
		MyFile.close();
	}

	static void _AddDataLineToFile(string Line) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::app | ios::out);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}
	void _AddNew() {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _Update() {
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();
		for (clsUser& U : _vUsers) {
			if (U.GetUserName() == GetUserName())
			{
				U = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
	}
public:

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string	UserName, string Password, int Permissions)
		:clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_Password = Password;
		_UserName = UserName;
		_Permissions = Permissions;
	}
	struct sLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		short Permissions;
	};
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64,pLoginRegister=128
	};

	static int GetSumPermissions() {
		return clsUser::enPermissions::pListClients
			+ clsUser::enPermissions::pAddNewClient
			+ clsUser::pDeleteClient + clsUser::pUpdateClients
			+ clsUser::pFindClient + clsUser::pTranactions
			+ clsUser::pManageUsers+clsUser::pLoginRegister;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string GetUserName() {
		return _UserName;
	}
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	string GetPassword() {
		return _Password;
	}
	void setPassword(string Password) {
		_Password = Password;
	}
	__declspec(property(get = GetPassword, put = setPassword))string Password;

	int GetPermissions() {
		return _Permissions;
	}
	void setPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	__declspec(property(get = GetPermissions, put = setPermissions))int Permissions;

	bool GetMarkForDelete() {
		return _MarkForDelete;
	}

	bool Delete() {
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();
		for (clsUser& U : vUsers) {
			if ( clsString::LowerAllString(U.UserName) == "admin") {
				return false;
			}
			if (U.UserName == _UserName)
			{
				U._MarkForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}


	static clsUser Find(string UserName) {
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
		
	}

	static clsUser Find(string UserName, string Password) {
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName) {
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists = 2 };

	enSaveResults save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		case clsUser::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case clsUser::AddNewMode:
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUserNameExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		default:
			break;
		}
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}
	 bool CheckPermissions(enPermissions Permissions) {
		if (this->Permissions== enPermissions::eAll)
		{
			return true;
		}
		if ((this->Permissions & Permissions) == Permissions)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	  void RegisterLogIn() {
		 string DataLine = _PrepareLogInRecord();
		 fstream MyFile;

		 MyFile.open("LoginRegister.txt", ios::out|ios::app);
		 if (MyFile.is_open())
		 {
			 MyFile << DataLine << endl;
		 }
		 MyFile.close();
	 }
	  static vector<sLoginRegisterRecord> GetLoginRegisterList() {
		  vector<sLoginRegisterRecord> vLoginRegisterData;
		  fstream MyFile;
		  MyFile.open("LoginRegister.txt", ios::in);
		  if (MyFile.is_open())
		  {
			  string Line;
			  sLoginRegisterRecord LoginRegisterData;
			  while (getline(MyFile, Line)) {
				  LoginRegisterData = _ConvertLoginRegisterLineToRecord(Line);
				  vLoginRegisterData.push_back(LoginRegisterData);
			  }
			  MyFile.close();
		  }
		  return vLoginRegisterData;
	  }
};


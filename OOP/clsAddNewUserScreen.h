#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iostream>
#include <string>
class clsAddNewUserScreen:protected clsScreen
{
private:
	static void _ReadUserInfo(clsUser& User) {
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nPermissions:\n ";
		User.Permissions = _ReadPermissionsToSet();
	}

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Clients List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }
        
        cout << "\nLogin Register? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }
        
        if (Permissions != clsUser::GetSumPermissions())
        {
            return Permissions;
        }
        else {
            return -1;
        }
        
    }

	static void _Print(clsUser User) {
		cout << "\n============User Card============\n";
		cout << "\nFirst Name: " << User.FirstName;
		cout << "\nLast  Name: " << User.LastName;
		cout << "\nFull  Name: " << User.FullName();
		cout << "\nEmail     : " << User.Email;
		cout << "\nUser Name : " << User.UserName;
		cout << "\nPassword  : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n==================================\n";

	}

public:
    static void AddNewUser() {
        _DrawScreenHeader("\t Add new User Screen");
        string UserName = "";
        cout << "\nPlease Enter User Name: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUser already Exist , Enter Account Number: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults saveResult;

        saveResult = NewUser.save();

        switch (saveResult)
        {
        case clsUser::svFaildEmptyObject:
            cout << "\nError User was not saved because it's Empty";
            break;
        case clsUser::svSucceeded:
            cout << "\nUser Added Successfully :-)\n";
            _Print(NewUser);
            break;
        case clsUser::svFaildUserNameExists:
            cout << "\nError User was not saved because user name is used!\n";
            break;
        default:
            break;
        }
    }
    
};


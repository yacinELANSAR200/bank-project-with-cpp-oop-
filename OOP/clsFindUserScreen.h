#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsFindUserScreen:protected clsScreen
{
private:
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
    static void FindUser() {
        _DrawScreenHeader("\t Find User Screen ");
        string UserName = "";
        cout << "Please Enter a User Name: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nUser [" << UserName << "], Enter another User Name: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User1 = clsUser::Find(UserName);
        if (!User1.IsEmpty())
        {
            _Print(User1);
        }
        else {
            cout << " User not Found !";
        }
    }
};


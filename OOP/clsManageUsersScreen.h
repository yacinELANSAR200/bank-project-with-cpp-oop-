#pragma once
#include <iomanip>
#include <iostream>
#include "Global.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersScreen:protected clsScreen
{
private:
    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };
    static short _ReadManageUsersOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Option = clsInputValidate::ReadNumberBetween<short>(1, 6);
        return Option;
    }
    static void _GoBackToMangeUsersMenue() {
        cout << "Press any key to go back to Manage Users Screen ....";
        system("pause>0");
        ShowManageUsersMenue();
    }

    static void _ShowListUsersScreen()
    {
        //cout << "\nList Users Screen Will Be Here.\n";
        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        //cout << "\nAdd New User Screen Will Be Here.\n";
        clsAddNewUserScreen::AddNewUser();
    }

    static void _ShowDeleteUserScreen()
    {
        //cout << "\nDelete User Screen Will Be Here.\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();

    }

    static void _ShowUpdateUserScreen()
    {
        //cout << "\nUpdate User Screen Will Be Here.\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        //cout << "\nFind User Screen Will Be Here.\n";
        clsFindUserScreen::FindUser();
    }

    static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOptions) {
        switch (ManageUsersMenueOptions)
        {
        case clsManageUsersScreen::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToMangeUsersMenue();
            break;
        case clsManageUsersScreen::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToMangeUsersMenue();
            break;
        case clsManageUsersScreen::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToMangeUsersMenue();
            break;
        case clsManageUsersScreen::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToMangeUsersMenue();
            break;
        case clsManageUsersScreen::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToMangeUsersMenue();
            break;
        case clsManageUsersScreen::eMainMenue:
            break;
        default:
            break;
        }
    }
public :
    static void ShowManageUsersMenue() {
        if (!_CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;
        }
        system("cls");
        _DrawScreenHeader("\t\Manage Users Screen");
        cout << left << setw(37) << "" << "===========================================\n";
        cout << left << setw(37) << "" << "\t\t\ Manage Users Menue\n";
        cout << left << setw(37) << "" << "===========================================\n";
        cout << left << setw(37) << "" << "\t[1]List Users.." << "\n";
        cout << left << setw(37) << "" << "\t[2]Add New User." << "\n";
        cout << left << setw(37) << "" << "\t[3]Delete User" << "\n";
        cout << left << setw(37) << "" << "\t[4]Update User." << "\n";
        cout << left << setw(37) << "" << "\t[5]Find User." << "\n";
        cout << left << setw(37) << "" << "\t[6]Main Menue." << "\n";
        cout << left << setw(37) << "" << "===========================================\n";
        _PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersOption());
    }
};


#pragma once
#include <iostream>
#include "clsEmployee.h";
using namespace std;

class clsDeveloper :public clsEmployee {
private:
	string _MainProgrammingLanguage;
public:
	
	clsDeveloper(int Id, string FirstName, string LastName, string Email, string Phone, string Title, string Department, float Salary, string MainProgrammingLanguage)
		:clsEmployee(Id, FirstName, LastName, Email, Phone, Title, Department, Salary) {
		_MainProgrammingLanguage = MainProgrammingLanguage;
	}
	void setMainProgrammingLanguage(string MainProgrammingLanguage) {
		_MainProgrammingLanguage = MainProgrammingLanguage;
	}
	string getMainProgrammingLanguage() {
		return _MainProgrammingLanguage;
	}
	
	void Print() {
		cout << "\n===============================\n";
		cout << "\t Info\t";
		cout << "\n===============================\n";
		cout << "Id : " << getId();
		cout << "\nFirst Name : " << getFirstName();
		cout << "\nLast Name : " << getLastName();
		cout << "\nEmail : " << getEmail();
		cout << "\nTitle : " << getTitle();
		cout << "\nDepartment : " << getDepartment();
		cout << "\nSalary : " << getSalary();
		cout << "\nMain Programming Language : " << getMainProgrammingLanguage();
		cout << "\n===============================\n";
	}
};


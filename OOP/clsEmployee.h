#pragma once
#include <iostream>
#include "clsPerson.h";
using namespace std;
class clsEmployee :public clsPerson {
protected:
	bool protectedExample = false;
private:
	float _Salary;
	string _Department;
	string _Title;
public:
	
	clsEmployee(int Id, string FirstName, string LastName, string Email, string Phone, string Title, string Department, float Salary)
		:clsPerson(Id, FirstName, LastName, Email, Phone) {
		_Salary = Salary;
		_Department = Department;
		_Title = Title;
	}
	float getSalary() {
		return _Salary;
	}
	string getDepartment() {
		return _Department;
	}
	string getTitle() {
		return _Title;
	}
	void setSalary(double Salary) {
		_Salary = Salary;
	}
	void setDepartment(string Department) {
		_Department = Department;
	}
	void setTitle(string Title) {
		_Title = Title;
	}
	void Print() {
		cout << "\n===============================\n";
		cout << "\t Info\t";
		cout << "\n===============================\n";
		cout << "Id : " << getId();
		cout << "\nFirst Name : " << getFirstName();
		cout << "\nLast Name : " << getLastName();
		cout << "\nEmail : " << getEmail();
		cout << "\nTitle : " << _Title;
		cout << "\nDepartment : " << _Department;
		cout << "\nSalary : " << _Salary;
		cout << "\n===============================\n";
	}
};


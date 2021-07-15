// Milestone 1 DBS 211 NCC
// Group project (Group 11)
// Student Name: Junwoo Lee,	Student ID: 124395203,  Student	Email: jlee648@myseneca.ca
// Student Name: Sukhmanpreet Kaur Malhi,	Student ID: 134893205,	Student Email: skmalhi2@myseneca.ca 
// Student Name: Balazs Sztojkovics,	 Student ID: 144563202,   Student Email: bsztojkovics@seneca.ca

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <occi.h>
#include <string.h>
#include <cstring>
using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;


struct Employee
{
	int  employeeNumber;
	char lastName[50];
	char firstName[50];
	char extension[10];
	char email[100];
	char officecode[10];
	int  reportsTo;
	char jobTitle[50];
};
int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp);
void displayEmployee(Connection* conn, struct Employee emp);
int menu();
void displayAllEmployees(Connection* conn);

int main(void)
{
	int number = 0;
	bool check = true;
	/* OCCI Variables */
	Environment* env = nullptr;
	Connection* conn = nullptr;
	/* Used Variables */
	string user = "dbs211_212c17";
	string pass = "38462531";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, constr);
		while (check)
		{
			number = menu();
			switch (number)
			{
			case 1:
				int employeeNum;
				cout << "Enter Employee Number: ";
				cin >> employeeNum;
				Employee emp1;
				if (findEmployee(conn, employeeNum, &emp1))
				{
					displayEmployee(conn, emp1);
				}
				else
					cout << "Employee " << employeeNum << " does not exist." << endl<<endl;
				break;
			case 2:
				displayAllEmployees(conn);
				cout << endl;
				break;
			case 3:
				cout << "3" << endl;
				break;
			case 4:
				cout << "4" << endl;
				break;
			case 5:
				cout << "5" << endl;
				break;
			default:
				cout << "Exiting..." << endl;
				check = false;
				break;
			}
		}
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	//system("pause");  // to stop the output window from closing in VS2013
	return 0;
}



int menu()
{
	int choice = 0;
	cout << "********************* HR Menu *********************" << endl;
	cout << "1) Find Employee" << endl;
	cout << "2) Employees Report" << endl;
	cout << "3) Add Employee" << endl;
	cout << "4) Update Employee" << endl;
	cout << "5) Remove Employee" << endl;
	cout << "0) Exit" << endl;
	cout << "Enter an option (0-5): ";

	int number = 0;
	bool check = true;
	char letter = 'X';

	while (check) {
		cin >> number;
		letter = cin.get();
		if (cin.fail()) {
			cout << "Bad integer value, try again: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (letter != '\n') {
			cout << "Enter only an integer, try again: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (0 > number || number > 5) {
			cout << "Enter an option (0-5): ";
		}
		else {
			check = false;
		}
	}
	return number;
}


void displayAllEmployees(Connection* conn)
{

	Statement* stmt = nullptr;
	stmt = conn->createStatement();

	ResultSet* rs = nullptr;
	rs = stmt->executeQuery("SELECT e.employeenumber AS ID, e.firstname || ' ' || e.lastname AS \"Employee Name\", e.email, o.phone, e.extension, d.firstname || ' ' || d.lastname AS \"Manager Name\" FROM dbs211_employees e JOIN dbs211_offices o ON e.officecode = o.officecode Left OUTER JOIN dbs211_employees d ON e.reportsto = d.employeenumber ORDER BY e.employeenumber");

	if (!rs->next())
	{

		cout << "ResultSet is empty." << endl;
	}
	else {
		cout << "------   ---------------    ---------------------------------  ----------------  ---------   -----------------" << endl;
		cout << "ID       Employee Name      Email                              Phone             Extension   Manager          " << endl;
		cout << "-----    ---------------    ---------------------------------  ----------------  ---------   -----------------" << endl;
		do {
			int id = rs->getInt(1);
			string name = rs->getString(2);
			string email = rs->getString(3);
			string phone = rs->getString(4);
			string extension = rs->getString(5);
			string managerName = rs->getString(6);

			cout.setf(ios::left);
			cout.width(9);
			cout << id;
			cout.unsetf(ios::left);

			cout.setf(ios::left);
			cout.width(19);
			cout << name;
			cout.unsetf(ios::left);

			cout.setf(ios::left);
			cout.width(35);
			cout << email;
			cout.unsetf(ios::left);

			cout.setf(ios::left);
			cout.width(18);
			cout << phone;
			cout.unsetf(ios::left);

			cout.setf(ios::left);
			cout.width(12);
			cout << extension;
			cout.unsetf(ios::left);

			cout << managerName << endl;
		} while (rs->next());
	}
}

int findEmployee(Connection* conn, int employeeNumber, Employee* emp)
{
	int res = 0;
	Statement* stmt = conn->createStatement();
	stmt->setSQL("SELECT * FROM dbs211_employees where employeenumber=:1");
	stmt->setInt(1, employeeNumber);
	ResultSet* rs = stmt->executeQuery();
	if (rs->next())
	{
		res = 1;
		emp->employeeNumber = rs->getInt(1);
		strncpy(emp->lastName, rs->getString(2).c_str(), 49);
		strncpy(emp->firstName, rs->getString(3).c_str(), 49);
		strncpy(emp->extension, rs->getString(4).c_str(), 9);
		strncpy(emp->email, rs->getString(5).c_str(), 99);
		strncpy(emp->officecode, rs->getString(6).c_str(), 9);
		emp->reportsTo = rs->getInt(7);
		strncpy(emp->jobTitle, rs->getString(8).c_str(), 49);
	}
	conn->terminateStatement(stmt);
	return res;
}

void displayEmployee(Connection* conn, Employee ep)
{
	cout << endl << "-------------- Employee Information -------------" << endl;
	cout << "Employee Number: " << ep.employeeNumber << endl;
	cout << "Last Name: " << ep.lastName << endl;
	cout << "First Name: " << ep.firstName << endl;
	cout << "Extenstion: " << ep.extension << endl;
	cout << "Email: " << ep.email << endl;
	cout << "Office Code: " << ep.officecode << endl;
	cout << "Manager ID: " << ep.reportsTo << endl;
	cout << "Job Title: " << ep.jobTitle << endl<<endl;

}
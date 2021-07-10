#include <iostream>
#include <occi.h>
#include "Employee.h"
using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;
using namespace sdds;
int main(void)
{

	/* OCCI Variables */
	Environment* env = nullptr;
	Connection* conn = nullptr;
	/* Used Variables */
	string user = "dbs211_212c13";
	string pass = "40102997";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";
	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, constr);
		cout << "Connection is Successful!" << endl;
		//Statement* stmt = conn->createStatement();
		//ResultSet* rs = stmt->executeQuery();
		struct Employee* ep;
		struct Employee emp1 = {};
		ep = &emp1;
		int employeeNum;
		cout << "Enter employ number: ";
		cin >> employeeNum;
		if (findEmployee(conn, employeeNum, ep))
		{
			cout << "Employ number: " << ep->employeeNumber << endl;
			cout << "Last name: " << ep->lastName << endl;
			cout << "First name: " << ep->firstName << endl;
			cout << "extenstion: " << ep->extension << endl;
			cout << "Email: " << ep->email << endl;
			cout << "Office Code: " << ep->officecode << endl;
			cout << "Reports To: " << ep->reportsTo << endl;
			cout << "Jon Title: " << ep->jobTitle << endl;
		}
		else
			cout << "Employee does not exist!" << endl;
		//conn->terminateStatement(stmt);
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;
}

#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

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
		Statement* stmt = conn->createStatement();
		stmt ->setSQL("SELECT employeenumber, firstname, lastname, phone, extension FROM dbs211_employees e JOIN dbs211_offices o ON e.officecode=o.officecode AND city='San Francisco'");
		ResultSet* rs = stmt->executeQuery();
		cout << "------------------------- Report 1 (Employee Report) -----------------------------------" << endl;
		cout << "Employee ID   First Name         Last Name          Phone             Extension" << endl;
		cout << "------------  -----------------  -----------------  ----------------  ---------" << endl;
		cout.setf(ios::left);
		while (rs->next()) {
			cout.width(14);
			cout << rs->getInt(1);
			cout.width(19);
			cout << rs->getString(2);
			cout.width(19);
			cout << rs->getString(3);
			cout.width(18);
			cout << rs->getString(4);
			cout.width(9);
			cout << rs->getString(5);
			cout << endl;
		}
		rs = stmt->executeQuery("SELECT DISTINCT e.employeenumber, e.firstname, e.lastname, phone, e.extension FROM dbs211_employees e JOIN dbs211_offices o ON e.officecode=o.officecode JOIN dbs211_employees e2 ON e2.reportsto = e.employeenumber ORDER BY e.employeenumber");
		cout << endl;
		cout << "------------------------- Report 2 (Employee Report) -----------------------------------" << endl;
		cout << "Employee ID   First Name         Last Name          Phone             Extension" << endl;
		cout << "------------  -----------------  -----------------  ----------------  ---------" << endl;
		while (rs->next()) {
			cout.width(14);
			cout << rs->getInt(1);
			cout.width(19);
			cout << rs->getString(2);
			cout.width(19);
			cout << rs->getString(3);
			cout.width(18);
			cout << rs->getString(4);
			cout.width(9);
			cout << rs->getString(5);
			cout << endl;
		}
		conn->terminateStatement(stmt);
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;
}

#include "Employee.h"
#include "cstring.h"
namespace sdds {
	int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp)
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
			strCpy(emp->lastName, rs->getString(2).c_str());
			strCpy(emp->firstName, rs->getString(3).c_str());
			strCpy(emp->extension, rs->getString(4).c_str());
			strCpy(emp->email, rs->getString(5).c_str());
			strCpy(emp->officecode, rs->getString(6).c_str());
			emp->reportsTo = rs->getInt(7);
			strCpy(emp->jobTitle, rs->getString(8).c_str());
		}
		conn->terminateStatement(stmt);
		return res;
	}
}
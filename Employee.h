#ifndef SDDS_EMPLOYEE_H_
#define SDDS_EMPLOYEE_H_
#include <occi.h>
using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

namespace sdds {
	struct Employee {
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
}

#endif
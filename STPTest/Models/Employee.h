#pragma once

#include <afxwin.h>

class Employee
{
public:
	CString id;
	CString firstName;
	CString lastName;
	CString startingDate;
	CString vacationDays;
	CString position;
	CString officeId;
	CString assignedHeadId;

	static void Read(CArray<Employee, Employee>& employees, CString query);

	static void Create(CString firstName, CString lastName, CString startingDate, CString vacationDays, CString position, 
		CString officeId, CString assignedHead);

	static void Update(Employee* employee,
		CString firstName, CString lastName, CString startingDate, CString vacationDays, CString position,
		CString officeId, CString assignedHead);

	static void Delete(Employee* employee);

	static CString PosIntToStr(int pos);
};

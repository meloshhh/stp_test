#pragma once

#include <afxwin.h>

class Office;

class Employee
{
public:
	CString id = L"";
	CString firstName = L"";
	CString lastName = L"";
	CString startingDate;
	CString vacationDays;
	CString position;
	CString officeId;
	CString assignedHeadId;

	Office* office;
	Employee* headChief;




	~Employee();

	CString GetDescriptiveStr();

	static void Read(CArray<Employee, Employee>& employees, CString query);

	static void Create(CString firstName, CString lastName, CString startingDate, CString vacationDays, CString position, 
		CString officeId, CString assignedHead);

	static void Update(Employee* employee,
		CString firstName, CString lastName, CString startingDate, CString vacationDays, CString position,
		CString officeId, CString assignedHead);

	static void Delete(Employee* employee);

	static CString PosIntToStr(int pos);

	static void LoadOffice(CArray<Employee, Employee>& employees);

	static void LoadHeadChief(CArray<Employee, Employee>& employees);

	static CString PluckOfficeIds(CArray<Employee, Employee>& employees);

	static CString PluckHeadChiefIds(CArray<Employee, Employee>& employees);
};

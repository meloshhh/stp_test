#pragma once

#include <afxwin.h>
#include "resource.h"
#include "Models/Employee.h"
#include "Models/Office.h"
#include <afxdtctl.h>

class EmployeeDialog : public CDialog
{
public:
	enum { IDD = IDD_EMPLOYEE };

	CString valFirstName;
	CString valLastName;
	COleDateTime valStartingDate;
	CString valVacationDays;

	CComboBox ctrlPosition;
	CComboBox ctrlOffice;
	CComboBox ctrlAssignedHeadId;

	Employee* employee;
	CArray<Office, Office> offices;
	CArray<Employee, Employee> headChiefs;



	EmployeeDialog(Employee* employee);

	~EmployeeDialog();

	void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog();

	void LoadOffices();

	void LoadHeadChiefs(CString officeId);

	void OnOK();
protected:
	afx_msg void OnCbnSelchangeEPos();
	afx_msg void OnCbnSelchangeEOffice();
	DECLARE_MESSAGE_MAP()
};


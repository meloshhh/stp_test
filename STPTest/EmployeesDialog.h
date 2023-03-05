#pragma once

#include <afxwin.h>
#include "resource.h"
#include <afxlistctrl.h>
#include "Models/Employee.h"

class EmployeesDialog : public CDialog
{
public:
	enum { IDD = IDD_EMPLOYEES };
	CListCtrl ctrlEmployees;
	CArray<Employee, Employee> employees;



    EmployeesDialog(CWnd* parentWnd);

    ~EmployeesDialog();

    void DoDataExchange(CDataExchange* pDX);

    BOOL OnInitDialog();

    void LoadEmployees();

    void OnOK();

protected:
    afx_msg void OnBnClickedCreateEmployee();
    afx_msg void OnBnClickedEditEmployee();
    afx_msg void OnBnClickedDeleteEmployee();
    afx_msg void OnBnClickedCompanies();
    afx_msg void OnBnClickedOffices();
    afx_msg void OnBnClickedEmployees();
    DECLARE_MESSAGE_MAP()
};


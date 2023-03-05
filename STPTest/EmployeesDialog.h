#pragma once

#include <afxwin.h>
#include "resource.h"
#include <afxlistctrl.h>
#include "Models/Employee.h"
#include "CDialogExt.h"

class EmployeesDialog : public CDialogExt
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

    void ResizeToParent();
protected:
    void OptimizeColumnWidths();

    afx_msg void OnBnClickedCreateEmployee();
    afx_msg void OnBnClickedEditEmployee();
    afx_msg void OnBnClickedDeleteEmployee();
    afx_msg void OnBnClickedCompanies();
    afx_msg void OnBnClickedOffices();
    afx_msg void OnBnClickedEmployees();
    DECLARE_MESSAGE_MAP()
};


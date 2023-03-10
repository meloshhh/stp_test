#pragma once

#include <afxwin.h>
#include "resource.h"
#include <afxlistctrl.h>
#include "Models/Company.h"
#include "CDialogExt.h"

class CompaniesDialog : public CDialogExt
{
public:
    enum { IDD = IDD_COMPANIES };
    CListCtrl ctrlCompaniesList;
    CArray<Company,Company> companies;



    CompaniesDialog(CWnd* parentWnd);

    ~CompaniesDialog();

    void DoDataExchange(CDataExchange* pDX);

    BOOL OnInitDialog();

    void LoadCompanies();

    void OnOK();
    
    void ResizeToParent();
protected:
    void OptimizeColumnWidths();

    afx_msg void OnBnClickedCreateCompany();
    afx_msg void OnBnClickedEditCompany();
    afx_msg void OnBnClickedDeleteCompany();
    afx_msg void OnBnClickedCompanies();
    afx_msg void OnBnClickedOffices();
    afx_msg void OnBnClickedEmployees();
    DECLARE_MESSAGE_MAP()
};
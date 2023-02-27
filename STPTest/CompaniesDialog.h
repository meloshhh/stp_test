#pragma once

#include <afxwin.h>
#include "resource.h"
#include <odbcinst.h>
#include <afxdb.h>
#include <afxlistctrl.h>

class CompaniesDialog : public CDialog
{
public:
    enum { IDD = IDD_COMPANIES };
    CListCtrl ctrlCompaniesList;

    CompaniesDialog(CWnd* parentWnd);
    ~CompaniesDialog();

    void DoDataExchange(CDataExchange* pDX);

    BOOL OnInitDialog();

    void LoadCompanies();

    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedCreateCompany();
};
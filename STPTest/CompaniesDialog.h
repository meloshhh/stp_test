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

    void OnOK();

protected:
    afx_msg void OnBnClickedCreateCompany();
    DECLARE_MESSAGE_MAP()
};
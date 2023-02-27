#pragma once

#include <afxwin.h>
#include "resource.h"

class MainDialog : public CDialog
{
public:
    enum { IDD = IDD_MAIN };

    CString valServer;
    CString valDatabaseName;
    CString valUsername;
    CString valPassword;

    MainDialog(CWnd* parentWnd);
    ~MainDialog();

    void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedConnect();
};
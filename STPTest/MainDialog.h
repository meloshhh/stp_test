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

    BOOL OnInitDialog();

    void OnOK();
protected:
    afx_msg void OnBnClickedConnect();
    DECLARE_MESSAGE_MAP()
};
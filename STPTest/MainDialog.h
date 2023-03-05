#pragma once

#include <afxwin.h>
#include "resource.h"
#include "CDialogExt.h"

class MainDialog : public CDialogExt
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
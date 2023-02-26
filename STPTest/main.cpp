#include <afxwin.h>
#include "resource.h"
#include <odbcinst.h>
#include <afxdb.h>
#include "DataTypes.h"

// Utility functions

void DebugMsg(CString* message)
{
    MessageBoxW(nullptr, message->GetString(), nullptr, 0);
}

// Classes

class Test1Dialog : public CDialog
{
public:
    enum { IDD = IDD_TEST1 };

    Test1Dialog(CWnd* parentWindow) : CDialog(IDD)
    {
        Create(IDD, parentWindow);
    }

    ~Test1Dialog() {}
protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedSwitchTo2nd();
};



class Test2Dialog : public CDialog
{
public:
    enum { IDD = IDD_TEST2 };

    Test2Dialog(CWnd* parentWindow) : CDialog(IDD)
    {
        Create(IDD, parentWindow);
    }

    ~Test2Dialog() {}
protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedSwitchTo1st();
};



class MainDialog : public CDialog
{
public:
    enum { IDD = IDD_MAIN };

    MainDialog(CWnd* parentWnd) : CDialog(IDD)
        , valUsername(_T(""))
    {
        Create(IDD, parentWnd);
    }

    ~MainDialog() {}

    void DoDataExchange(CDataExchange* pDX)
    {
        DDX_Text(pDX, IDC_USERNAME, valUsername);
    }

    CString valUsername;
    DECLARE_MESSAGE_MAP()
        afx_msg void OnBnClickedConnect();
};



class MainFrame : public CFrameWnd {
public:
    MainFrame()
    {
        Create(NULL, L"STP Test Program", WS_OVERLAPPEDWINDOW);
    }
};



class Program : public CWinApp
{
public:
    Program() : CWinApp(), db(nullptr) {}

    BOOL InitInstance()
    {
        m_pMainWnd = new MainFrame;
        m_pMainWnd->ShowWindow(SW_SHOW);
        m_pMainWnd->UpdateWindow();

        if (!activeDialog)
        {
            activeDialog = new Test1Dialog(m_pMainWnd);
        }

        return TRUE;
    }

    void SwitchToTest2View()
    {
        delete activeDialog;
        activeDialog = nullptr;
        activeDialog = new Test2Dialog(m_pMainWnd);
    }

    void SwitchToTest1View()
    {
        delete activeDialog;
        activeDialog = nullptr;
        activeDialog = new Test1Dialog(m_pMainWnd);
    }

    void ConnectToDb(DBType dbType)
    {
        if (!db)
        {
            db = new CDatabase();
        }

        CString* connStr = new CString("ODBC;");

        //db->Open(NULL, FALSE, FALSE, );
    }

    CDatabase* db;

protected:
    CDialog* activeDialog = nullptr;
};


// Implementations

void Test1Dialog::OnBnClickedSwitchTo2nd()
{
    Program* program = static_cast<Program*>(AfxGetApp());

    /*CString* msg = new CString(); msg->Format(L"Program ref is valid: %d", program != nullptr);
    DebugMsg(msg);
    return;*/

    program->SwitchToTest2View();
}

void Test2Dialog::OnBnClickedSwitchTo1st()
{
    Program* program = static_cast<Program*>(AfxGetApp());

    program->SwitchToTest1View();
}

void MainDialog::OnBnClickedConnect()
{
    // Establish a database connection in the application
}






BEGIN_MESSAGE_MAP(Test1Dialog, CDialog)
    ON_BN_CLICKED(IDC_SWITCH_TO_2ND, &Test1Dialog::OnBnClickedSwitchTo2nd)
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(Test2Dialog, CDialog)
    ON_BN_CLICKED(IDC_SWITCH_TO_1ST, &Test2Dialog::OnBnClickedSwitchTo1st)
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(MainDialog, CDialog)
    ON_BN_CLICKED(IDC_CONNECT, &MainDialog::OnBnClickedConnect)
END_MESSAGE_MAP()

Program program;

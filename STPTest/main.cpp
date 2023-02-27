#include <afxwin.h>
#include "resource.h"
#include <odbcinst.h>
#include <afxdb.h>
#include "DataTypes.h"
#include <afxlistctrl.h>

// Utility functions


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
        , valServer(_T(""))
    {
        Create(IDD, parentWnd);
    }

    ~MainDialog() {}

    virtual void DoDataExchange(CDataExchange* pDX)
    {
        DDX_Text(pDX, IDC_SERVER, valServer);
        DDX_Text(pDX, IDC_DATABASE_NAME, valDatabaseName);
        DDX_Text(pDX, IDC_USERNAME, valUsername);
        DDX_Text(pDX, IDC_PASSWORD, valPassword);
    }

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedConnect();
public:
    CString valServer;
    CString valDatabaseName;
    CString valUsername;
    CString valPassword;
};

class CompaniesDialog : public CDialog
{
public:
    enum { IDD = IDD_COMPANIES };
    CListCtrl ctrlCompaniesList;

    CompaniesDialog(CWnd* parentWnd) : CDialog(IDD)
    {
        Create(IDD, parentWnd);
    }

    ~CompaniesDialog() {}

    virtual void DoDataExchange(CDataExchange* pDX)
    {
        DDX_Control(pDX, IDC_COMPANIES, ctrlCompaniesList);
    }

    virtual BOOL OnInitDialog()
    {
        CDialog::OnInitDialog();

        // Setup the list
        //ListView_SetExtendedListViewStyle(ctrlCompaniesList, LVS_EX_GRIDLINES);
        ctrlCompaniesList.InsertColumn(0, L"ID", LVCFMT_LEFT, -1, 0);
        ctrlCompaniesList.InsertColumn(1, L"Name", LVCFMT_LEFT, -1, 1);
        ctrlCompaniesList.InsertColumn(1, L"Created at", LVCFMT_LEFT, -1, 1);
        ctrlCompaniesList.InsertColumn(1, L"HQ address", LVCFMT_LEFT, -1, 1);

        LoadCompanies();
    }

    void LoadCompanies()
    {
        ctrlCompaniesList.DeleteAllItems();

        // Retrieve companies from db
        Program* program = static_cast<Program*>(AfxGetApp());
        CRecordset recSet(program->db);
        CString query(
            "SELECT c.id, c.name, c.created_at, o.country, o.city, o.street, o.street_number"
            "FROM companies c"
            "LEFT JOIN offices o ON c.headquarters_id = o.id"
        );

        recSet.Open(CRecordset::forwardOnly, query, CRecordset::readOnly);

        while (!recSet.IsEOF())
        {
            Company company;
            recSet.GetFieldValue(L"c.id", company.id);
            recSet.GetFieldValue(L"c.name", company.name);
            recSet.GetFieldValue(L"c.created_at", company.createdAt);
            CString temp;
            recSet.GetFieldValue(L"o.country", temp);           company.hqAddress += temp;
            recSet.GetFieldValue(L"o.city", temp);              company.hqAddress += L", " + temp;
            recSet.GetFieldValue(L"o.street", temp);            company.hqAddress += L", " + temp;
            recSet.GetFieldValue(L"o.street_number", temp);     company.hqAddress += L", " + temp;

            ctrlCompaniesList.InsertItem(0, company.id, 0);
            ctrlCompaniesList.SetItemText(0, 1, company.name);
            ctrlCompaniesList.SetItemText(0, 2, company.createdAt);
            ctrlCompaniesList.SetItemText(0, 3, company.hqAddress);

            recSet.MoveNext();
        }
    }

    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedCreateCompany()
    {
        // Open create company dialog
    }
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
    Program() : CWinApp(), db(nullptr), activeDialog(nullptr) {}
    ~Program() 
    {
        if (db)
        {
            db->Close();
            delete db;
        }
    }

    BOOL InitInstance()
    {
        m_pMainWnd = new MainFrame;
        m_pMainWnd->ShowWindow(SW_SHOW);
        m_pMainWnd->UpdateWindow();

        if (!activeDialog)
        {
            activeDialog = new MainDialog(m_pMainWnd);
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

    void SwitchToCompaniesView()
    {
        delete activeDialog;
        activeDialog = nullptr;
        activeDialog = new CompaniesDialog(m_pMainWnd);
    }

    bool ConnectToDb(DBType dbType, CString server, CString dbName, CString uid, CString pwd)
    {
        if (!db)
        {
            db = new CDatabase();
        }

        CString connStr;
        CString driverStr;

        switch (dbType)
        {
        case SQLServer:
            driverStr.SetString(L"{ODBC Driver 17 for SQL Server}");
            break;
        case MSAccess:
            driverStr.SetString(L"{MICROSOFT ACCESS DRIVER (*.mdb)}");
            break;
        }

        connStr.Format(L"(ODBC;Driver=%s;Server=%s;Database=%s;UID=%s;PWD=%s)", driverStr, server, dbName, uid, pwd);

        OutputDebugString(connStr + L"\n");
        
        BOOL successful = db->Open(NULL, FALSE, FALSE, connStr, TRUE);
        if (!successful)
        {
            OutputDebugString(L"Failed to connect to database\n");
            return false;
        }

        return true;
    }

    CDatabase* db;

protected:
    CDialog* activeDialog;
};


// Implementations

void Test1Dialog::OnBnClickedSwitchTo2nd()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToTest2View();
}

void Test2Dialog::OnBnClickedSwitchTo1st()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToTest1View();
}

void MainDialog::OnBnClickedConnect()
{
    UpdateData(TRUE);
    Program* program = static_cast<Program*>(AfxGetApp());
    bool success = program->ConnectToDb(SQLServer, valServer, valDatabaseName, valUsername, valPassword);
    if (!success) return;
    program->SwitchToCompaniesView();
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

BEGIN_MESSAGE_MAP(CompaniesDialog, CDialog)
    ON_BN_CLICKED(IDC_CREATE_COMPANY, &CompaniesDialog::OnBnClickedCreateCompany)
END_MESSAGE_MAP()

Program program;

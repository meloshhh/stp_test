#include "Program.h"
#include "MainFrame.h"
#include "MainDialog.h"
#include "CompaniesDialog.h"

Program::Program() : CWinApp(), db(nullptr), activeDialog(nullptr)
{

}

Program::~Program()
{
    if (db)
    {
        db->Close();
        delete db;
    }
}

BOOL Program::InitInstance()
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

void Program::SwitchToCompaniesView()
{
    delete activeDialog;
    activeDialog = nullptr;
    activeDialog = new CompaniesDialog(m_pMainWnd);
}

bool Program::ConnectToDb(DBType dbType, CString server, CString dbName, CString uid, CString pwd)
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

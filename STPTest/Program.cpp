#include "Program.h"
#include "MainFrame.h"
#include "MainDialog.h"
#include "CompaniesDialog.h"
#include "OfficesDialog.h"

Program::Program() : CWinApp(), db(nullptr), activeDialog(nullptr), frame(nullptr)
{

}

Program::~Program()
{
    if (db != nullptr)
    {
        if (db->IsOpen())
        {
            db->Close();
        }
        delete db;
        db = nullptr;
        OutputDebugString(L"Db connection closed and mem freed\n");
    }

    if (activeDialog != nullptr)
    {
        delete activeDialog;
        activeDialog = nullptr;
    }

    /*if (frame != nullptr)
    {
        delete frame;
        frame = nullptr;
    }*/
}

BOOL Program::InitInstance()
{
    frame = new MainFrame();
    m_pMainWnd = frame;
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
    activeDialog->EndDialog(IDCANCEL);
    delete activeDialog;
    activeDialog = nullptr;
    activeDialog = new CompaniesDialog(m_pMainWnd);
}

void Program::SwitchToOfficesView()
{
    activeDialog->EndDialog(IDCANCEL);
    delete activeDialog;
    activeDialog = nullptr;
    activeDialog = new OfficesDialog(m_pMainWnd);
}

void Program::SwitchToEmployeesView()
{
    activeDialog->EndDialog(IDCANCEL);
    delete activeDialog;
    activeDialog = nullptr;
    //activeDialog = new EmployeesDialog(m_pMainWnd);
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

    connStr.Format(L"ODBC;Driver=%s;Server=%s;Database=%s;UID=%s;PWD=%s", driverStr, server, dbName, uid, pwd);

    OutputDebugString(connStr);
    OutputDebugString(L"\n");

    BOOL successful = db->Open(NULL, FALSE, FALSE, connStr, TRUE);
    if (successful == FALSE)
    {
        OutputDebugString(L"Failed to connect to database\n");
        return false;
    }

    return true;
}

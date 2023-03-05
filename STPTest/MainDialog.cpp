#include "MainDialog.h"
#include "Program.h"
#include "DataTypes.h"

MainDialog::MainDialog(CWnd* parentWnd) : CDialog(IDD),
valServer(L""),
valDatabaseName(L""),
valUsername(L""),
valPassword(L"")
{
    Create(IDD, parentWnd);
}

MainDialog::~MainDialog() {}

void MainDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SERVER, valServer);
    DDX_Text(pDX, IDC_DATABASE_NAME, valDatabaseName);
    DDX_Text(pDX, IDC_USERNAME, valUsername);
    DDX_Text(pDX, IDC_PASSWORD, valPassword);
}

void MainDialog::OnBnClickedConnect()
{
    UpdateData(TRUE);
    Program* program = static_cast<Program*>(AfxGetApp());
    bool success = program->ConnectToDb(SQLServer, valServer, valDatabaseName, valUsername, valPassword);
    if (!success)
    {
        MessageBox(L"Failed to connect to DB");
        return;
    }
    program->SwitchToCompaniesView();
}

BOOL MainDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    valServer = L"127.0.0.1";
    valDatabaseName = L"stp_test";
    valUsername = "sa";
    UpdateData(FALSE);

    return TRUE;
}

void MainDialog::OnOK()
{
    OnBnClickedConnect();
    OutputDebugString(L"Main dialog OK\n");
}

BEGIN_MESSAGE_MAP(MainDialog, CDialog)
    ON_BN_CLICKED(IDC_CONNECT, OnBnClickedConnect)
END_MESSAGE_MAP()
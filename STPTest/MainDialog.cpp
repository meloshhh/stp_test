#include "MainDialog.h"
#include "Program.h"
#include "DataTypes.h"

MainDialog::MainDialog(CWnd* parentWnd) : CDialog(IDD)
    , valServer(_T(""))
{
    Create(IDD, parentWnd);
}

MainDialog::~MainDialog() {}

void MainDialog::DoDataExchange(CDataExchange* pDX)
{
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
    if (!success) return;
    program->SwitchToCompaniesView();
}

BEGIN_MESSAGE_MAP(MainDialog, CDialog)
    ON_BN_CLICKED(IDC_CONNECT, &MainDialog::OnBnClickedConnect)
END_MESSAGE_MAP()
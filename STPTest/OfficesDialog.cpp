#include "OfficesDialog.h"
#include "Program.h"

OfficesDialog::OfficesDialog(CWnd* parentWnd) : CDialog(IDD)
{
	Create(IDD, parentWnd);
}

OfficesDialog::~OfficesDialog()
{
}

void OfficesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OFFICES_LIST, ctrlOfficesList);
}

BOOL OfficesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

    // Setup the list
    ListView_SetExtendedListViewStyle(ctrlOfficesList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    ctrlOfficesList.InsertColumn(0, L"ID", LVCFMT_LEFT, -1, 0);
    ctrlOfficesList.InsertColumn(1, L"Country", LVCFMT_LEFT, -1, 1);
    ctrlOfficesList.InsertColumn(2, L"City", LVCFMT_LEFT, -1, 2);
    ctrlOfficesList.InsertColumn(3, L"Street", LVCFMT_LEFT, -1, 3);
    ctrlOfficesList.InsertColumn(4, L"Street number", LVCFMT_LEFT, -1, 4);
    ctrlOfficesList.InsertColumn(5, L"Company ID", LVCFMT_LEFT, -1, 5);

    CRect rect;
    ctrlOfficesList.GetWindowRect(&rect);
    for (int i = 0; i < ctrlOfficesList.GetHeaderCtrl()->GetItemCount(); ++i)
    {
        ctrlOfficesList.SetColumnWidth(i, (int)floor(rect.Width() * 0.166f));
    }

    LoadOffices();

	return TRUE;
}

void OfficesDialog::LoadOffices()
{
}

void OfficesDialog::OnOK()
{
}

void OfficesDialog::OnBnClickedCompanies()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToCompaniesView();
}

void OfficesDialog::OnBnClickedOffices()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToOfficesView();
}

void OfficesDialog::OnBnClickedEmployees()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToEmployeesView();
}

void OfficesDialog::OnBnClickedCreateOffice()
{
}

void OfficesDialog::OnBnClickedEditOffice()
{
}

void OfficesDialog::OnBnClickedDeleteOffice()
{
}

BEGIN_MESSAGE_MAP(OfficesDialog, CDialog)
    ON_BN_CLICKED(IDC_CREATE_OFFICE, &OfficesDialog::OnBnClickedCreateOffice)
    ON_BN_CLICKED(IDC_EDIT_OFFICE, &OfficesDialog::OnBnClickedEditOffice)
    ON_BN_CLICKED(IDC_DEL_COMPANY, &OfficesDialog::OnBnClickedDeleteOffice)
    ON_BN_CLICKED(IDC_COMPANIES, &OfficesDialog::OnBnClickedCompanies)
    ON_BN_CLICKED(IDC_OFFICES, &OfficesDialog::OnBnClickedOffices)
    ON_BN_CLICKED(IDC_EMPLOYEES, &OfficesDialog::OnBnClickedEmployees)
END_MESSAGE_MAP()

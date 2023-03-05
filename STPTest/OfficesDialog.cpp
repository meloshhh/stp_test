#include "OfficesDialog.h"
#include "Program.h"
#include "OfficeDialog.h"
#include "Utilities/Validator.h"
#include "SimplePopupDialog.h"

OfficesDialog::OfficesDialog(CWnd* parentWnd) : CDialog(IDD),
offices()
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
    ctrlOfficesList.DeleteAllItems();

    CString query(
        "SELECT * "
        "FROM offices"
    );

    Office::Read(offices, query);

    for (int i = 0; i < offices.GetSize(); ++i)
    {
        ctrlOfficesList.InsertItem(i, offices[i].id, 0);
        ctrlOfficesList.SetItemText(i, 1, offices[i].country);
        ctrlOfficesList.SetItemText(i, 2, offices[i].city);
        ctrlOfficesList.SetItemText(i, 3, offices[i].street);
        ctrlOfficesList.SetItemText(i, 4, offices[i].streetNumber);
        ctrlOfficesList.SetItemText(i, 5, offices[i].companyId);
    }
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
    OfficeDialog modal(nullptr);
    modal.DoModal();

    LoadOffices();
}

void OfficesDialog::OnBnClickedEditOffice()
{
    int selection = ctrlOfficesList.GetSelectionMark();
    if (selection < 0)
    {
        DISPLAY_VAL_ERR(L"You must select an item from the list")
        return;
    }

    OfficeDialog modal(&offices[selection]);
    modal.DoModal();

    LoadOffices();

    ctrlOfficesList.SetItemState(selection, LVIS_SELECTED, LVIS_SELECTED);
    ctrlOfficesList.SetSelectionMark(selection);
    ctrlOfficesList.SetFocus();
}

void OfficesDialog::OnBnClickedDeleteOffice()
{
    int selection = ctrlOfficesList.GetSelectionMark();
    if (selection < 0)
    {
        DISPLAY_VAL_ERR(L"You must select an item from the list")
            return;
    }

    Office::Delete(&offices[selection]);

    LoadOffices();
}

BEGIN_MESSAGE_MAP(OfficesDialog, CDialog)
    ON_BN_CLICKED(IDC_CREATE_OFFICE, &OfficesDialog::OnBnClickedCreateOffice)
    ON_BN_CLICKED(IDC_EDIT_OFFICE, &OfficesDialog::OnBnClickedEditOffice)
    ON_BN_CLICKED(IDC_DEL_OFFICE, &OfficesDialog::OnBnClickedDeleteOffice)
    ON_BN_CLICKED(IDC_COMPANIES, &OfficesDialog::OnBnClickedCompanies)
    ON_BN_CLICKED(IDC_OFFICES, &OfficesDialog::OnBnClickedOffices)
    ON_BN_CLICKED(IDC_EMPLOYEES, &OfficesDialog::OnBnClickedEmployees)
END_MESSAGE_MAP()

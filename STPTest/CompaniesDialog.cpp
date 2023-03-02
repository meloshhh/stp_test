#include "CompaniesDialog.h"
#include "Program.h"
#include "DataTypes.h"
#include "CompanyDialog.h"
#include "Utilities/Validator.h"
#include "SimplePopupDialog.h"
#include "Models/Company.h"

CompaniesDialog::CompaniesDialog(CWnd* parentWnd) : CDialog(IDD)
{
    Create(IDD, parentWnd);
}

CompaniesDialog::~CompaniesDialog() {}

void CompaniesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMPANIES_LIST, ctrlCompaniesList);
}

BOOL CompaniesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Setup the list
    ListView_SetExtendedListViewStyle(ctrlCompaniesList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    ctrlCompaniesList.InsertColumn(0, L"ID", LVCFMT_LEFT, -1, 0);
    ctrlCompaniesList.InsertColumn(1, L"Name", LVCFMT_LEFT, -1, 1);
    ctrlCompaniesList.InsertColumn(2, L"Created at", LVCFMT_LEFT, -1, 2);
    ctrlCompaniesList.InsertColumn(3, L"Headquarters ID", LVCFMT_LEFT, -1, 3);

    CRect rect;
    ctrlCompaniesList.GetWindowRect(&rect);
    for (int i = 0; i < ctrlCompaniesList.GetHeaderCtrl()->GetItemCount(); ++i)
    {
        ctrlCompaniesList.SetColumnWidth(i, (int)floor(rect.Width() * 0.25f - 1));
    }

    LoadCompanies();

    return TRUE;
}

void CompaniesDialog::LoadCompanies()
{
    ctrlCompaniesList.DeleteAllItems();

    CString query(
        "SELECT * "
        "FROM companies"
    );
    Company::ReadAll(companies, query);
    
    for (int i = 0; i < companies.GetSize(); ++i)
    {
        ctrlCompaniesList.InsertItem(i, companies[i].id, 0);
        ctrlCompaniesList.SetItemText(i, 1, companies[i].name);
        ctrlCompaniesList.SetItemText(i, 2, companies[i].createdAt);
        ctrlCompaniesList.SetItemText(i, 3, companies[i].headquartersId);
    }
}

void CompaniesDialog::OnOK()
{

}

void CompaniesDialog::OnBnClickedCreateCompany()
{
    CompanyDialog modal(nullptr);
    modal.DoModal();

    LoadCompanies();
}

void CompaniesDialog::OnBnClickedEditCompany()
{
    int selection = ctrlCompaniesList.GetSelectionMark();
    if (selection < 0)
    {
        DISPLAY_VAL_ERR(L"You must select an item from the list")
        return;
    }
    CompanyDialog modal(&companies[selection]);
    modal.DoModal();

    LoadCompanies();
}

void CompaniesDialog::OnBnClickedDeleteCompany()
{
    int selection = ctrlCompaniesList.GetSelectionMark();
    if (selection < 0)
    {
        DISPLAY_VAL_ERR(L"You must select an item from the list")
        return;
    }

    Program* program = static_cast<Program*>(AfxGetApp());
    
    program->db->ExecuteSQL(
        "DELETE FROM companies WHERE id = " + companies[selection].id
    );

    LoadCompanies();
}

void CompaniesDialog::OnBnClickedCompanies()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToCompaniesView();
}

void CompaniesDialog::OnBnClickedOffices()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToOfficesView();
}

void CompaniesDialog::OnBnClickedEmployees()
{
    Program* program = static_cast<Program*>(AfxGetApp());
    program->SwitchToEmployeesView();
}

BEGIN_MESSAGE_MAP(CompaniesDialog, CDialog)
    ON_BN_CLICKED(IDC_CREATE_COMPANY, &CompaniesDialog::OnBnClickedCreateCompany)
    ON_BN_CLICKED(IDC_EDIT_COMPANY, &CompaniesDialog::OnBnClickedEditCompany)
    ON_BN_CLICKED(IDC_DEL_COMPANY, &CompaniesDialog::OnBnClickedDeleteCompany)
    ON_BN_CLICKED(IDC_COMPANIES, &CompaniesDialog::OnBnClickedCompanies)
    ON_BN_CLICKED(IDC_OFFICES, &CompaniesDialog::OnBnClickedOffices)
    ON_BN_CLICKED(IDC_EMPLOYEES, &CompaniesDialog::OnBnClickedEmployees)
END_MESSAGE_MAP()

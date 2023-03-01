#include "CompaniesDialog.h"
#include "Program.h"
#include "DataTypes.h"
#include "CreateCompanyDialog.h"

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
    ListView_SetExtendedListViewStyle(ctrlCompaniesList, LVS_EX_GRIDLINES);

    ctrlCompaniesList.InsertColumn(0, L"ID", LVCFMT_LEFT, -1, 0);
    ctrlCompaniesList.InsertColumn(1, L"Name", LVCFMT_LEFT, -1, 1);
    ctrlCompaniesList.InsertColumn(2, L"Created at", LVCFMT_LEFT, -1, 1);
    ctrlCompaniesList.InsertColumn(3, L"HQ address", LVCFMT_LEFT, -1, 1);

    for (int i = 0;i < ctrlCompaniesList.GetHeaderCtrl()->GetItemCount();++i)
        ctrlCompaniesList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

    LoadCompanies();

    return TRUE;
}

void CompaniesDialog::LoadCompanies()
{
    ctrlCompaniesList.DeleteAllItems();

    // Retrieve companies from db
    Program* program = static_cast<Program*>(AfxGetApp());
    CRecordset recSet(program->db);
    CString query(
        "SELECT c.id, c.name, c.created_at, o.country, o.city, o.street, o.street_number "
        "FROM companies c "
        "LEFT JOIN offices o ON c.headquarters_id = o.id"
    );

    recSet.Open(CRecordset::forwardOnly, query, CRecordset::readOnly);

    while (!recSet.IsEOF())
    {
        Company company;
        recSet.GetFieldValue(L"id", company.id);
        recSet.GetFieldValue(L"name", company.name);
        recSet.GetFieldValue(L"created_at", company.createdAt);
        CString temp;
        recSet.GetFieldValue(L"country", temp);           company.hqAddress += temp;
        recSet.GetFieldValue(L"city", temp);              company.hqAddress += L", " + temp;
        recSet.GetFieldValue(L"street", temp);            company.hqAddress += L", " + temp;
        recSet.GetFieldValue(L"street_number", temp);     company.hqAddress += L", " + temp;

        ctrlCompaniesList.InsertItem(0, company.id, 0);
        ctrlCompaniesList.SetItemText(0, 1, company.name);
        ctrlCompaniesList.SetItemText(0, 2, company.createdAt);
        ctrlCompaniesList.SetItemText(0, 3, company.hqAddress);

        recSet.MoveNext();
    }
}

void CompaniesDialog::OnOK()
{

}

void CompaniesDialog::OnBnClickedCreateCompany()
{
    CreateCompanyDialog modal;
    modal.DoModal();

    LoadCompanies();
}

BEGIN_MESSAGE_MAP(CompaniesDialog, CDialog)
    ON_BN_CLICKED(IDC_CREATE_COMPANY, &CompaniesDialog::OnBnClickedCreateCompany)
END_MESSAGE_MAP()

#include "CompaniesDialog.h"
#include "Program.h"
#include "DataTypes.h"

BEGIN_MESSAGE_MAP(CompaniesDialog, CDialog)
    ON_BN_CLICKED(IDC_CREATE_COMPANY, &CompaniesDialog::OnBnClickedCreateCompany)
END_MESSAGE_MAP()

CompaniesDialog::CompaniesDialog(CWnd* parentWnd) : CDialog(IDD)
{
    Create(IDD, parentWnd);
}

CompaniesDialog::~CompaniesDialog() {}

void CompaniesDialog::DoDataExchange(CDataExchange* pDX)
{
    DDX_Control(pDX, IDC_COMPANIES, ctrlCompaniesList);
}

BOOL CompaniesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Setup the list
    //ListView_SetExtendedListViewStyle(ctrlCompaniesList, LVS_EX_GRIDLINES);
    ctrlCompaniesList.InsertColumn(0, L"ID", LVCFMT_LEFT, -1, 0);
    ctrlCompaniesList.InsertColumn(1, L"Name", LVCFMT_LEFT, -1, 1);
    ctrlCompaniesList.InsertColumn(1, L"Created at", LVCFMT_LEFT, -1, 1);
    ctrlCompaniesList.InsertColumn(1, L"HQ address", LVCFMT_LEFT, -1, 1);

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

void CompaniesDialog::OnBnClickedCreateCompany()
{
    // Open create company dialog as a modal
}
#include "CreateCompanyDialog.h"
#include "Program.h"

CreateCompanyDialog::CreateCompanyDialog() : CDialog(IDD)
, valName(L"")
, valHq(L"")
, offices()
{
	//Create(IDD, nullptr);
}

CreateCompanyDialog::~CreateCompanyDialog()
{
	//
}

void CreateCompanyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_C_NAME, valName);
	DDX_Text(pDX, IDC_C_HQ, valHq);
	DDX_Control(pDX, IDC_C_HQ, ctrlHq);
}

BOOL CreateCompanyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	LoadOffices();

	return TRUE;
}

void CreateCompanyDialog::LoadOffices()
{
	Program* program = static_cast<Program*>(AfxGetApp());
	CRecordset recSet(program->db);
	CString query(
		"SELECT id, country, city, street, street_number "
		"FROM offices"
	);

	recSet.Open(CRecordset::forwardOnly, query, CRecordset::readOnly);

	while (!recSet.IsEOF())
	{
		Office office;
		recSet.GetFieldValue(L"id", office.id);
		recSet.GetFieldValue(L"country", office.country);
		recSet.GetFieldValue(L"city", office.city);
		recSet.GetFieldValue(L"street", office.street);
		recSet.GetFieldValue(L"street_number", office.streetNumber);
		offices.Add(office);

		ctrlHq.AddString(office.city + L", " + office.country + L", " + office.city + L", " + office.street
			+ L", " + office.streetNumber);

		recSet.MoveNext();
	}
}

void CreateCompanyDialog::OnOK()
{
	UpdateData(TRUE);
	Program* program = static_cast<Program*>(AfxGetApp());

	int selection = ctrlHq.GetCurSel();
	Office office;

	CString query;
	query.Format(
		L"INSERT INTO companies (name, created_at, headquarters_id) "
		L"VALUES ('%s', '%s', ",
		valName,
		CTime::GetCurrentTime().FormatGmt(L"%F %T")
	);
	if (selection >= 0)
	{
		query.Append(offices[selection].id + L")");
	}
	else
	{
		query.Append(L"NULL)");
	}

	program->db->ExecuteSQL(query);

	EndDialog(IDOK);
}

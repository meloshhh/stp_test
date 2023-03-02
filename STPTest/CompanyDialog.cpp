#include "CompanyDialog.h"
#include "Program.h"
#include "Utilities/Validator.h"
#include "SimplePopupDialog.h"
#include "Models/Company.h"
#include "Models/Office.h"

CompanyDialog::CompanyDialog(Company* company = nullptr) : CDialog(IDD)
, valName(L"")
, company(company)
{
	//Create(IDD, nullptr);
}

CompanyDialog::~CompanyDialog()
{
	//
}

void CompanyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_C_NAME, valName);
	DDX_Control(pDX, IDC_C_HQ, ctrlHq);
	DDX_Control(pDX, IDC_HQ_LABEL, ctrlHqLabel);
}

BOOL CompanyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadOffices();

	if (company)
	{
		valName = company->name;
		for (int i = 0; i < offices.GetSize(); i++)
		{
			if (offices[i].id == company->headquartersId) ctrlHq.SetCurSel(i);
		}
		UpdateData(FALSE);
	}
	else
	{
		ctrlHq.ShowWindow(SW_HIDE);
		ctrlHqLabel.ShowWindow(SW_HIDE);
	}

	return TRUE;
}

void CompanyDialog::LoadOffices()
{
	if (!company) return;

	CString query(
		"SELECT * "
		"FROM offices "
		"WHERE company_id = " + company->id
	);

	Office::ReadOffices(offices, query);

	for (int i = 0; i < offices.GetSize(); ++i)
	{
		ctrlHq.AddString(offices[i].id);
	}
}

void CompanyDialog::OnOK()
{
	UpdateData(TRUE);

	// Validation
	if (!Validator::String(valName, "required")) 
	{ 
		DISPLAY_VAL_ERR(L"Name is invalid");
		return; 
	}

	if (!company)
	{
		Company::Create(valName);
	}
	else
	{
		int selection = ctrlHq.GetCurSel();
		Company::Update(company, valName, selection >= 0 ? &offices[selection] : nullptr);
	}

	EndDialog(IDOK);
}

#include "CompanyDialog.h"
#include "Program.h"
#include "Utilities/Validator.h"
#include "SimplePopupDialog.h"

CompanyDialog::CompanyDialog(Company* company = nullptr) : CDialog(IDD),
valName(L""),
offices(),
company(company)
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
		if (company->headquartersId.IsEmpty())
		{
			ctrlHq.SetCurSel(0);
		}
		else
		{
			for (int i = 0; i < offices.GetSize(); i++)
			{
				if (offices[i].id == company->headquartersId) ctrlHq.SetCurSel(i + 1);
			}
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

	Office::Read(offices, query);

	ctrlHq.AddString(L"/");
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
		Company::Update(company, valName, selection >= 1 ? &offices[selection - 1] : nullptr);
	}

	EndDialog(IDOK);
}

#include "OfficeDialog.h"
#include "Utilities/Validator.h"
#include "SimplePopupDialog.h"

OfficeDialog::OfficeDialog(Office* office = nullptr) : CDialog(IDD)
, valCountry(L"")
, valCity(L"")
, valStreet(L"")
, valStreetNo(L"")
, companies()
, office(office)
{

}

OfficeDialog::~OfficeDialog()
{
}

void OfficeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_O_COUNTRY, valCountry);
	DDX_Text(pDX, IDC_O_CITY, valCity);
	DDX_Text(pDX, IDC_O_STREET, valStreet);
	DDX_Text(pDX, IDC_O_STREET_NO, valStreetNo);
	DDX_Control(pDX, IDC_O_COMPANY, ctrlCompany);
}

BOOL OfficeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadCompanies();

	if (companies.GetSize() == 0)
	{
		EndDialog(IDCANCEL);
		DISPLAY_VAL_ERR(L"You must first create at least 1 company")
	}

	if (office)
	{
		valCountry = office->country;
		valCity = office->city;
		valStreet = office->street;
		valStreetNo = office->streetNumber;

		for (int i = 0; i < companies.GetSize(); i++)
		{
			if (companies[i].id == office->companyId) ctrlCompany.SetCurSel(i);
		}


		UpdateData(FALSE);
	}
	else
	{
		//
	}

	return TRUE;
}

void OfficeDialog::LoadCompanies()
{
	CString query(
		"SELECT * "
		"FROM companies "
	);

	Company::Read(companies, query);

	for (int i = 0; i < companies.GetSize(); ++i)
	{
		ctrlCompany.AddString(companies[i].id);
	}

	if (companies.GetSize() > 0)
	{
		ctrlCompany.SetCurSel(0);
	}
}

void OfficeDialog::OnOK()
{
	UpdateData(TRUE);
	int sel = ctrlCompany.GetCurSel();

	if (!office)
	{
		Office::Create(valCountry, valCity, valStreet, valStreetNo, companies[sel].id);
	}
	else
	{
		Office::Update(office, valCountry, valCity, valStreet, valStreetNo, companies[sel].id);
	}

	EndDialog(IDOK);
}

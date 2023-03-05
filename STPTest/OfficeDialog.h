#pragma once

#include <afxwin.h>
#include "resource.h"
#include "Models/Company.h"
#include "Models/Office.h"

class OfficeDialog : public CDialog
{
public:
	enum { IDD = IDD_OFFICE };

	CString valCountry;
	CString valCity;
	CString valStreet;
	CString valStreetNo;

	CComboBox ctrlCompany;

	Office* office;
	CArray<Company, Company> companies;



	OfficeDialog(Office* office);

	~OfficeDialog();

	void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog();

	void LoadCompanies();

	void OnOK();
};


#pragma once

#include <afxwin.h>
#include "resource.h"
#include <odbcinst.h>
#include <afxdb.h>
#include "Models/Office.h"
#include "Models/Company.h"

class CompaniesDialog;

class CompanyDialog : public CDialog
{
public:
	enum { IDD = IDD_COMPANY };

	CString valName;
	CStatic ctrlHqLabel;
	CComboBox ctrlHq;
	CArray<Office, Office> offices;
	Company* company;




	CompanyDialog(Company* company);

	~CompanyDialog();

	void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog();

	void LoadOffices();

	void OnOK();
};


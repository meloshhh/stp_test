#pragma once

#include <afxwin.h>
#include "resource.h"
#include <odbcinst.h>
#include <afxdb.h>
#include "DataTypes.h"

class CompaniesDialog;

class CreateCompanyDialog : public CDialog
{
public:
	enum { IDD = IDD_CREATE_COMPANY };

	CString valName;
	CString valHq;
	CComboBox ctrlHq;
	CArray<Office, Office> offices;




	CreateCompanyDialog();

	~CreateCompanyDialog();

	void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog();

	void LoadOffices();

	void OnOK();
};


#pragma once

#include <afxwin.h>
#include "resource.h"
#include <afxlistctrl.h>
#include "Models/Office.h"


class OfficesDialog : public CDialog
{
public:
	enum { IDD = IDD_OFFICES };

	CListCtrl ctrlOfficesList;

	CArray<Office, Office> offices;



	OfficesDialog(CWnd* parentWnd);

	~OfficesDialog();

	void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog();

	void LoadOffices();

	void OnOK();
protected:
	afx_msg void OnBnClickedCompanies();
	afx_msg void OnBnClickedOffices();
	afx_msg void OnBnClickedEmployees();
	afx_msg void OnBnClickedCreateOffice();
	afx_msg void OnBnClickedEditOffice();
	afx_msg void OnBnClickedDeleteOffice();
	DECLARE_MESSAGE_MAP()
};


#pragma once

#include <afxwin.h>
#include "resource.h"

class SimplePopupDialog : public CDialog
{
public:
	enum { IDD = IDD_SIMPLE_POPUP };
	CString msg;
	CString valMessage;



	SimplePopupDialog(CString msg);

	~SimplePopupDialog();

	void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog();
};


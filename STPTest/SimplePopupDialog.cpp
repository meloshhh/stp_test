#include "SimplePopupDialog.h"

SimplePopupDialog::SimplePopupDialog(CString msg) : CDialog(IDD)
, msg(msg)
{
}

SimplePopupDialog::~SimplePopupDialog()
{
}

void SimplePopupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MESSAGE, valMessage);
}

BOOL SimplePopupDialog::OnInitDialog()
{
	valMessage = msg;
	UpdateData(FALSE);

	return TRUE;
}

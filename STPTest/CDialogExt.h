#pragma once

#include <afxwin.h>

class CDialogExt : public CDialog
{
public:
	CDialogExt(UINT idd);

	virtual void ResizeToParent();
};


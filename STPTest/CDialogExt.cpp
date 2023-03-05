#include "CDialogExt.h"

CDialogExt::CDialogExt(UINT idd) : CDialog(idd)
{
}


void CDialogExt::ResizeToParent()
{
	CRect rect;
	GetParent()->GetWindowRect(&rect);
	MoveWindow(0, 0, rect.Width() - 20, rect.Height() - 20);
}

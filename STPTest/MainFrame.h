#pragma once

#include <afxwin.h>

class MainFrame : public CFrameWnd 
{
public:
    MainFrame();

protected:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    DECLARE_MESSAGE_MAP()
};
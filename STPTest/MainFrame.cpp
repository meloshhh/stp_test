#include "MainFrame.h"
#include "Program.h"

MainFrame::MainFrame()
{
    Create(NULL, L"STP Test Program", WS_OVERLAPPEDWINDOW);
}

void MainFrame::OnSize(UINT nType, int cx, int cy)
{
    Program* program = static_cast<Program*>(AfxGetApp());
    if (program->activeDialog)
    {
        program->activeDialog->ResizeToParent();
    }
}

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
    ON_WM_SIZE()
END_MESSAGE_MAP()

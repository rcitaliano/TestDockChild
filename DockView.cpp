// DockView.cpp : implementation file
//

#include "stdafx.h"
#include "TestDockChild.h"
#include "DockView.h"


// CDockView

IMPLEMENT_DYNAMIC(CDockView, CDockablePane)

CDockView::CDockView()
{
    m_View = nullptr;
}

CDockView::~CDockView()
{
}


BEGIN_MESSAGE_MAP(CDockView, CDockablePane)
        ON_WM_SIZE()
END_MESSAGE_MAP()


int CDockView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rectDummy;
    rectDummy.SetRectEmpty();

    // Create view:
    const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

    if (!m_View->Create(L"CTestDockChildView",L"CTestDockChildView",dwViewStyle,rectDummy,this,4,m_pContext))
    {
        TRACE0("Failed to create file view\n");
        return -1;      // fail to create
    }

    //AdjustLayout();

    return 0;
}

void CDockView::AdjustLayout()
{
    if (GetSafeHwnd() == NULL)
    {
        return;
    }

    CRect rectClient;
    GetClientRect(rectClient);
    if (m_View != nullptr && m_View->GetSafeHwnd())
    {
        m_View->SetWindowPos(NULL, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
    }
}
void CDockView::OnSize(UINT nType, int cx, int cy)
{
    CDockablePane::OnSize(nType, cx, cy);
    AdjustLayout();
}
// CDockView message handlers



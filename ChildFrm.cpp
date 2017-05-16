// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "TestDockChild.h"

#include "ChildFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    if(TRUE != CMDIChildWndEx::OnCreateClient(lpcs,pContext))
        return FALSE;

    CMainFrame* mainFrame = (CMainFrame*)(AfxGetMainWnd());
    // enable Visual Studio 2005 style docking window behavior
    CDockingManager::SetDockingMode(DT_SMART);
    // enable Visual Studio 2005 style docking window auto-hide behavior
    EnableAutoHidePanes(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);

    // create docking windows
    if (!CreateDockingWindows(pContext))
    {
        TRACE0("Failed to create docking windows\n");
        return -1;
    }

    return TRUE;
}
#ifndef PARENT_DOCKING
//#define PARENT_DOCKING GetMainFrame()
#define PARENT_DOCKING this
#endif

BOOL CChildFrame::CreateDockingWindows(CCreateContext* pContext)
{
    BOOL bNameValid;

    EnableDocking(CBRS_ALIGN_LEFT);
    // Create class view
    CString strClassView;
    bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
    ASSERT(bNameValid);
    if (!m_wndClassView.Create(strClassView, PARENT_DOCKING, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
    //if (!m_wndClassView.Create(strClassView, PARENT_DOCKING, CSize(200,200), TRUE, ID_VIEW_CLASSVIEW))
    {
        TRACE0("Failed to create Class View window\n");
        return FALSE; // failed to create
    }

    EnableDocking(CBRS_ALIGN_BOTTOM);
    // Create file view
    CString strFileView;
    bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
    ASSERT(bNameValid);
    if (!m_wndFileView.Create(strFileView, PARENT_DOCKING, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
    //if (!m_wndFileView.Create(strFileView, PARENT_DOCKING, CSize(200,200), TRUE, ID_VIEW_CLASSVIEW))
    {
        TRACE0("Failed to create File View window\n");
        return FALSE; // failed to create
    }

    EnableDocking(CBRS_ALIGN_RIGHT);
    // Create output window
    CString strOutputWnd;
    bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
    ASSERT(bNameValid);
    if (!m_wndOutput.Create(strOutputWnd, PARENT_DOCKING, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
    //if (!m_wndOutput.Create(strOutputWnd, PARENT_DOCKING, CSize(200,200), TRUE, ID_VIEW_CLASSVIEW))
    {
        TRACE0("Failed to create Output window\n");
        return FALSE; // failed to create
    }

    // Create properties window
    CString strPropertiesWnd;
    bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
    ASSERT(bNameValid);
    if (!m_wndProperties.Create(strPropertiesWnd, PARENT_DOCKING, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
    //if (!m_wndProperties.Create(strPropertiesWnd, PARENT_DOCKING, CSize(200,200), TRUE, ID_VIEW_CLASSVIEW))
    {
        TRACE0("Failed to create Properties window\n");
        return FALSE; // failed to create
    }

    m_wndDockView.m_pContext = pContext;
    if (!m_wndDockView.Create(L"DockView", PARENT_DOCKING, CRect(0, 0, 200, 200), TRUE, ID_DOCKING_WINDOW_4, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI,AFX_CBRS_REGULAR_TABS,AFX_DEFAULT_DOCKING_PANE_STYLE,pContext))
        //if (!m_wndProperties.Create(strPropertiesWnd, PARENT_DOCKING, CSize(200,200), TRUE, ID_VIEW_CLASSVIEW))
    {
        TRACE0("Failed to create Properties window\n");
        return FALSE; // failed to create
    }
    m_wndDockView.EnableDocking(CBRS_ALIGN_ANY);
    m_wndDockView.RecalcLayout();
    DockPane(&m_wndDockView);

    SetDockingWindowIcons(theApp.m_bHiColorIcons);


    m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
    m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
    m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
    m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
//     PARENT_DOCKING->AddPane(&m_wndFileView);
//     PARENT_DOCKING->AddPane(&m_wndClassView); 
//     PARENT_DOCKING->AddPane(&m_wndOutput);
//     PARENT_DOCKING->AddPane(&m_wndProperties);
// 
//     PARENT_DOCKING->DockPane(&m_wndFileView);
//     PARENT_DOCKING->DockPane(&m_wndClassView);   
//     PARENT_DOCKING->DockPane(&m_wndOutput);
//     PARENT_DOCKING->DockPane(&m_wndProperties);
     
//      PARENT_DOCKING->DockPane(&m_wndFileView,   ID_VIEW_FILEVIEW);
//      PARENT_DOCKING->DockPane(&m_wndOutput,     ID_VIEW_OUTPUTWND);
//      PARENT_DOCKING->DockPane(&m_wndProperties, ID_VIEW_PROPERTIESWND);
//      PARENT_DOCKING->DockPane(&m_wndClassView,  ID_VIEW_CLASSVIEW);

//     m_wndFileView.RecalcLayout();
//     m_wndClassView.RecalcLayout();
//     m_wndOutput.RecalcLayout();
//     m_wndProperties.RecalcLayout();
    RecalcLayout();
    return TRUE;
}

void CChildFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
    HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    m_wndFileView.SetIcon(hFileViewIcon, FALSE);

    HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    m_wndClassView.SetIcon(hClassViewIcon, FALSE);

    HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

    HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
    m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

    GetMainFrame()->UpdateMDITabbedBarsIcons();
}

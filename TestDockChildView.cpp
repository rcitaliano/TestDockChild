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

// TestDockChildView.cpp : implementation of the CTestDockChildView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TestDockChild.h"
#endif

#include "TestDockChildDoc.h"
#include "TestDockChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDockChildView

IMPLEMENT_DYNCREATE(CTestDockChildView, CView)

BEGIN_MESSAGE_MAP(CTestDockChildView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTestDockChildView construction/destruction

CTestDockChildView::CTestDockChildView()
{
	// TODO: add construction code here

}

CTestDockChildView::~CTestDockChildView()
{
}

BOOL CTestDockChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestDockChildView drawing

void CTestDockChildView::OnDraw(CDC* pDC)
{
	CTestDockChildDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
    CRect rect;
    GetClientRect(rect);
    pDC->Draw3dRect(rect,RGB(255,0,0),RGB(255,0,0));
	// TODO: add draw code for native data here
}

void CTestDockChildView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestDockChildView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestDockChildView diagnostics

#ifdef _DEBUG
void CTestDockChildView::AssertValid() const
{
	CView::AssertValid();
}

void CTestDockChildView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDockChildDoc* CTestDockChildView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDockChildDoc)));
	return (CTestDockChildDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestDockChildView message handlers

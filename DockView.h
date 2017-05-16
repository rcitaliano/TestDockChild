#pragma once


// CDockView
#include "TestDockChildDoc.h"
#include "TestDockChildView.h"

class CDockView : public CDockablePane
{
	DECLARE_DYNAMIC(CDockView)

public:
	CDockView();
	virtual ~CDockView();

    CTestDockChildView* m_View;

    void AdjustLayout();
    CCreateContext* m_pContext;
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};



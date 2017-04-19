// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// OpenGLRibbontoSiNongView.h : interface of the COpenGLRibbontoSiNongView class
//

#pragma once

#include "DataShow.h"
#include "GenerateRandomPoint.h"
#include "CreDrawDatas.h"
class COpenGLRibbontoSiNongView : public CView
{
protected: // create from serialization only
	COpenGLRibbontoSiNongView();
	DECLARE_DYNCREATE(COpenGLRibbontoSiNongView)

// Attributes
public:
	COpenGLRibbontoSiNongDoc* GetDocument() const;

// Operations
public:
	
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~COpenGLRibbontoSiNongView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
private://the OpenGL variable
CDataShow m_DataShowPro;
CreDrawDatas datas;
Point *m_GussianRandomPoint;
bool flag_DrawBox;
Point pp;
bool flag_GussianSimu;
bool flag_DrawPoint;
bool flag_DrawGps;
int flag_points;
int flag_lines;
int flag_rectangle;


DWORD Num_GussianRandomPoint;
double m_GussianSigma;
bool DrawBox();
bool DrawGussianPoint();
bool DrawPoint(double corX,double corY);
bool DrawGPSPointonetoone();
bool Drawpoint();
bool Drawline();
bool Drawrectangle();
vector <Point> m_GpsDataBuffer;
vector <Point> m_DrawGpsData;
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonDrawbox();
	afx_msg void OnButtonDrawcoordi();
	afx_msg void OnButtonDrawgussianpoint();
	afx_msg void OnEditPointX();
	afx_msg void OnEditPointY();
	afx_msg void OnGussianGradient();
	afx_msg void OnGussianNum();
	afx_msg void OnGussianR();
	afx_msg void OnGussianSigmar();
	afx_msg void OnGussianSigmatheta();
	afx_msg void OnButtonClearallpoint();
	afx_msg void OnButtonDrawunsortedgps();
	afx_msg void OnButtonSortgps();
	afx_msg void One();
	afx_msg void OnButtonReadgpsfile();
	afx_msg void OnPoint();
	afx_msg void OnLine();
	afx_msg void OnRectangle();
};

#ifndef _DEBUG  // debug version in OpenGLRibbontoSiNongView.cpp
inline COpenGLRibbontoSiNongDoc* COpenGLRibbontoSiNongView::GetDocument() const
   { return reinterpret_cast<COpenGLRibbontoSiNongDoc*>(m_pDocument); }
#endif


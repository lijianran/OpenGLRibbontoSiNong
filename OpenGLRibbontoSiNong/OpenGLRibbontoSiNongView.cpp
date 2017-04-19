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

// OpenGLRibbontoSiNongView.cpp : implementation of the COpenGLRibbontoSiNongView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGLRibbontoSiNong.h"
#endif
#include <GL\freeglut.h>
#include "OpenGLRibbontoSiNongDoc.h"
#include "OpenGLRibbontoSiNongView.h"
#include "MainFrm.h"
#include "Toponology.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.1415926
// COpenGLRibbontoSiNongView

IMPLEMENT_DYNCREATE(COpenGLRibbontoSiNongView, CView)

BEGIN_MESSAGE_MAP(COpenGLRibbontoSiNongView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLRibbontoSiNongView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
//	ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_RBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_MOUSEWHEEL()
ON_WM_MOUSEHWHEEL()
ON_WM_CREATE()
ON_WM_SIZE()
ON_COMMAND(ID_BUTTON_DRAWBOX, &COpenGLRibbontoSiNongView::OnButtonDrawbox)
ON_COMMAND(ID_BUTTON_DRAWCOORDI, &COpenGLRibbontoSiNongView::OnButtonDrawcoordi)
ON_COMMAND(ID_BUTTON_DRAWGUSSIANPOINT, &COpenGLRibbontoSiNongView::OnButtonDrawgussianpoint)
ON_COMMAND(ID_EDIT_POINT_X, &COpenGLRibbontoSiNongView::OnEditPointX)
ON_COMMAND(ID_EDIT_POINT_Y, &COpenGLRibbontoSiNongView::OnEditPointY)
ON_COMMAND(ID_GUSSIAN_GRADIENT, &COpenGLRibbontoSiNongView::OnGussianGradient)
ON_COMMAND(ID_GUSSIAN_NUM, &COpenGLRibbontoSiNongView::OnGussianNum)
ON_COMMAND(ID_GUSSIAN_R, &COpenGLRibbontoSiNongView::OnGussianR)
ON_COMMAND(ID_GUSSIAN_SIGMAR, &COpenGLRibbontoSiNongView::OnGussianSigmar)
ON_COMMAND(ID_GUSSIAN_SIGMATHETA, &COpenGLRibbontoSiNongView::OnGussianSigmatheta)
ON_COMMAND(ID_BUTTON_CLEARALLPOINT, &COpenGLRibbontoSiNongView::OnButtonClearallpoint)
ON_COMMAND(ID_BUTTON_DRAWUNSORTEDGPS, &COpenGLRibbontoSiNongView::OnButtonDrawunsortedgps)
ON_COMMAND(ID_BUTTON_SORTGPS, &COpenGLRibbontoSiNongView::OnButtonSortgps)
ON_COMMAND(ID_BUTTON_READGPSFILE, &COpenGLRibbontoSiNongView::OnButtonReadgpsfile)
ON_COMMAND(ID_POINT, &COpenGLRibbontoSiNongView::OnPoint)
ON_COMMAND(ID_LINE, &COpenGLRibbontoSiNongView::OnLine)
ON_COMMAND(ID_RECTANGLE, &COpenGLRibbontoSiNongView::OnRectangle)
END_MESSAGE_MAP()

// COpenGLRibbontoSiNongView construction/destruction

COpenGLRibbontoSiNongView::COpenGLRibbontoSiNongView()
{
	// TODO: add construction code here
	flag_DrawBox = 0;
	flag_DrawPoint = 0;
	flag_GussianSimu = 0;
	flag_DrawGps = 0;
	flag_points = 0;
	flag_lines = 0;
	flag_rectangle = 0;
	

}

COpenGLRibbontoSiNongView::~COpenGLRibbontoSiNongView()
{
}

BOOL COpenGLRibbontoSiNongView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

// COpenGLRibbontoSiNongView drawing

void COpenGLRibbontoSiNongView::OnDraw(CDC* /*pDC*/)
{
	COpenGLRibbontoSiNongDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: add draw code for native data here
}


// COpenGLRibbontoSiNongView printing

void COpenGLRibbontoSiNongView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLRibbontoSiNongView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLRibbontoSiNongView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLRibbontoSiNongView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


void COpenGLRibbontoSiNongView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLRibbontoSiNongView diagnostics

#ifdef _DEBUG
void COpenGLRibbontoSiNongView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLRibbontoSiNongView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLRibbontoSiNongDoc* COpenGLRibbontoSiNongView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLRibbontoSiNongDoc)));
	return (COpenGLRibbontoSiNongDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLRibbontoSiNongView message handlers


void COpenGLRibbontoSiNongView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CView::OnPaint() for painting messages
	HWND hWnd = this->GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	wglMakeCurrent(NULL, NULL);  //释放设备当前使用的上下文
	wglMakeCurrent(hDC, m_DataShowPro.m_hGLContext);//指定一个OpenGL渲染上下文(hglrc)调用线程的当前呈现上下文(dc)
	//绘图区域，图层管理
	m_DataShowPro.InitialScene(dc, hDC);//给datashow.cpp中传递 当前上下文描述表 和其窗口句柄

	//画格网部分
	//开始画图
	//Draw_compass(20,-15,0.0); // 罗盘
	m_DataShowPro.Draw_grid(5); // 网格
	//m_DataShowPro.Draw_Road_Center_Point();//坐标系
	m_DataShowPro.Draw_circle(5, 5);//画圆盘坐标系
	m_DataShowPro.Draw_coordinate();//画直角坐标轴和箭头
	if (flag_DrawBox == 1)
	{
		DrawBox();
	}
	if (flag_DrawPoint == 1)
	{
		DrawPoint(pp.x,pp.y);
	}
	if (flag_GussianSimu == 1)
	{
		DrawGussianPoint();
	}
	if (flag_DrawGps == 1)
	{
		DrawGPSPointonetoone();
	}
	if (flag_points == 1 || flag_points == 2)
	{
		Drawpoint();
	}
	if (flag_lines == 1 || flag_lines == 2)
	{
		Drawline();
	}
	if (flag_rectangle == 1 || flag_rectangle == 2)
	{
		Drawrectangle();
	}
	glPopMatrix();
	SwapBuffers(dc.m_ps.hdc);
	::ReleaseDC(hWnd, hDC);
}



//void COpenGLRibbontoSiNongView::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CView::OnLButtonDblClk(nFlags, point);
//}


void COpenGLRibbontoSiNongView::OnLButtonDown(UINT nFlags, CPoint point)     //鼠标左键按下
{
	// TODO: Add your message handler code here and/or call default

	GLfloat winx, winy, winz;
	GLdouble posx, posy, posz;

	winx = (float)point.x;
	winy = (float)m_DataShowPro.viewport[3] - (float)point.y;
	glReadPixels((int)winx, (int)winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);   /* 获取像素深度 */
	gluUnProject(winx, winy, winz, m_DataShowPro.mvmatrix, m_DataShowPro.projmatrix, m_DataShowPro.viewport, &posx, &posy, &posz); /* 获取三维坐标 */

	CPoint a;
	if (flag_points == 1)
	{
		a.x = posx*(m_DataShowPro.camPos[2] / -900);
		a.y = posy*(m_DataShowPro.camPos[2] / -900);
		datas.onepoint.push_back(a);
		SendMessage(WM_PAINT);
	}
	if (flag_lines == 1)
	{
		a.x = posx*(m_DataShowPro.camPos[2]/-900);
		a.y = posy*(m_DataShowPro.camPos[2]/-900);
		datas.begin_end.begin = a;
	}
	if (flag_rectangle == 1)
	{
		a.x = posx*(m_DataShowPro.camPos[2] / -900);
		a.y = posy*(m_DataShowPro.camPos[2] / -900);
		datas.begin_end.begin = a;
	}
	m_DataShowPro.OnLButtonDown(nFlags, point);
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void COpenGLRibbontoSiNongView::OnLButtonUp(UINT nFlags, CPoint point)     //鼠标左键弹起
{
	// TODO: Add your message handler code here and/or call default
	GLfloat winx, winy, winz;
	GLdouble posx, posy, posz;

	winx = (float)point.x;
	winy = (float)m_DataShowPro.viewport[3] - (float)point.y;
	glReadPixels((int)winx, (int)winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);   /* 获取像素深度 */
	gluUnProject(winx, winy, winz, m_DataShowPro.mvmatrix, m_DataShowPro.projmatrix, m_DataShowPro.viewport, &posx, &posy, &posz); /* 获取三维坐标 */

	CPoint a;
	if (flag_lines == 1)
	{
		a.x = posx*(m_DataShowPro.camPos[2] / -900);
		a.y = posy*(m_DataShowPro.camPos[2] / -900);
		datas.begin_end.end = a;
		datas.line.push_back(datas.begin_end);
		SendMessage(WM_PAINT);
	}
	if (flag_rectangle == 1)
	{
		a.x = posx*(m_DataShowPro.camPos[2] / -900);
		a.y = posy*(m_DataShowPro.camPos[2] / -900);
		datas.begin_end.end = a;
		datas.juxing.push_back(datas.begin_end);
		SendMessage(WM_PAINT);
	}
	m_DataShowPro.OnLButtonUp(nFlags, point);
	ReleaseCapture();
	PostMessage(WM_PAINT, 0, 0);
	CView::OnLButtonUp(nFlags, point);
}


void COpenGLRibbontoSiNongView::OnRButtonDown(UINT nFlags, CPoint point)    //鼠标右键按下
{
	// TODO: Add your message handler code here and/or call default
	m_DataShowPro.OnRButtonDown(nFlags, point);
	//UpdateWindow();
	m_DataShowPro.m_nButtonFlag = rightDown;
	SetCapture();
	CView::OnRButtonDown(nFlags, point);
}

void COpenGLRibbontoSiNongView::OnRButtonUp(UINT /* nFlags */, CPoint point)    //鼠标右键弹起
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLRibbontoSiNongView::OnMouseMove(UINT nFlags, CPoint point)     //鼠标移动
{
	// TODO: Add your message handler code here and/or call default
	if (m_DataShowPro.mouseleftdown)
	{
		m_DataShowPro.OnMouseMove(nFlags, point);
		PostMessage(WM_PAINT, 0, 0);
	}
	CView::OnMouseMove(nFlags, point);
}

BOOL COpenGLRibbontoSiNongView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)    //鼠标滑轮
{
	// TODO: Add your message handler code here and/or call default
	m_DataShowPro.OnMouseWheel(nFlags, zDelta, pt);
	PostMessage(WM_PAINT, 0, 0);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void COpenGLRibbontoSiNongView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	// TODO: Add your message handler code here and/or call default

	CView::OnMouseHWheel(nFlags, zDelta, pt);
}


int COpenGLRibbontoSiNongView::OnCreate(LPCREATESTRUCT lpCreateStruct)  //创建窗口时调用
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	m_DataShowPro.OnCreate(hWnd);
	// TODO:  Add your specialized creation code here

	return 0;
}


void COpenGLRibbontoSiNongView::OnSize(UINT nType, int cx, int cy)    //窗口大小的改变
{
	int a = cx;
	int b = cy;
	CView::OnSize(nType, cx, cy);
	m_DataShowPro.OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
}


void COpenGLRibbontoSiNongView::OnButtonDrawbox()                    //点击<画正方形>
{
	flag_DrawBox = 1;
	SendMessage(WM_PAINT);
	// TODO: Add your command handler code here
}
bool COpenGLRibbontoSiNongView::DrawBox()                               //画正方形
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f); 
	glVertex3f(2.0f, 2.0f, -2.0f); 
	glVertex3f(-2.0f, 2.0f, -2.0f);
	glVertex3f(-2.0f, 2.0f, 2.0f);
	glVertex3f(2.0f, 2.0f, 2.0f);
	// 颜色改为蓝色
	// 四边形的右上顶点 (顶面) // 四边形的左上顶点 (顶面) // 四边形的左下顶点 (顶面)
	// 四边形的右下顶点 (顶面)
	glColor3f(1.0f, 0.0f, 0.0f); // 颜色改成橙色 
	glVertex3f( 2.0f,-2.0f, 2.0f); // 四边形的右上顶点(底面)
	glVertex3f(-2.0f, -2.0f, 2.0f);
	glVertex3f(-2.0f, -2.0f, -2.0f); 
	glVertex3f(2.0f, -2.0f, -2.0f);
    // 四边形的左上顶点(底面) // 四边形的左下顶点(底面) // 四边形的右下顶点(底面)
	glColor3f(1.0f, 0.0f, 1.0f); 
	glVertex3f(2.0f, 2.0f, 2.0f); 
	glVertex3f(-2.0f, 2.0f, 2.0f);
	glVertex3f(-2.0f, -2.0f, 2.0f);
	glVertex3f(2.0f, -2.0f, 2.0f);
	// 颜色改成红色
	// 四边形的右上顶点(前面) // 四边形的左上顶点(前面)
	// 四边形的左下顶点(前面) // 四边形的右下顶点(前面)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, -2.0f, -2.0f);
	glVertex3f(-2.0f, -2.0f, -2.0f);
	glVertex3f(-2.0f, 2.0f, -2.0f);
	glVertex3f(2.0f, 2.0f, -2.0f);
	// 颜色改成黄色
	// 四边形的右上顶点(后面) // 四边形的左上顶点(后面) // 四边形的左下顶点(后面)
	// 四边形的右下顶点(后面)
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-2.0f, 2.0f, 2.0f); 
	glVertex3f(-2.0f, 2.0f, -2.0f);
	glVertex3f(-2.0f, -2.0f, -2.0f);
	glVertex3f(-2.0f, -2.0f, 2.0f);
	// 颜色改成蓝色
	// 四边形的右上顶点(左面) // 四边形的左上顶点(左面)
	// 四边形的左下顶点(左面) // 四边形的右下顶点(左面)
	glColor3f(0.0f, 1.0f, 1.0f); 
	glVertex3f(2.0f, 2.0f, -2.0f);
	glVertex3f(2.0f, 2.0f, 2.0f); 
	glVertex3f(2.0f, -2.0f, 2.0f);
	glVertex3f(2.0f, -2.0f, -2.0f);
	glEnd();
	return TRUE;
	// 颜色改成紫罗兰色
	// 四边形的右上顶点(右面) // 四边形的左上顶点(右面) // 四边形的左下顶点(右面)
	// 四边形的右下顶点(右面) // 立方体绘制结束
}

void COpenGLRibbontoSiNongView::OnButtonDrawcoordi()                    //点击<画坐标>,获取点的数据
{
	double Corx;
	double Cory;
	          //从ribbon中获取数据
	CMFCRibbonBar*pRibbon = ((CMainFrame*)AfxGetMainWnd())->GetRibbonBar();
	ASSERT_VALID(pRibbon);
	CMFCRibbonEdit *pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbon->FindByID(ID_EDIT_POINT_X));
	Corx = atof(pEdit->GetEditText());
	pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbon->FindByID(ID_EDIT_POINT_Y));
	Cory = atof(pEdit->GetEditText());
	pp.x = Corx;
	pp.y = Cory;
	flag_DrawPoint = 1;
	SendMessage(WM_PAINT);
	// TODO: Add your command handler code here
}

bool COpenGLRibbontoSiNongView::DrawPoint(double corX, double corY)               //画点坐标
{
	glPointSize(100);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINT);
	glVertex3d(corX, corY, 1.0);
	glEnd();
	return true;
}

bool COpenGLRibbontoSiNongView::DrawGussianPoint()                           //高斯画图
{
	glPointSize(3);
	glColor3f(1, 0, 0);
	for (int i = 0; i<Num_GussianRandomPoint; i++)
	{
		glBegin(GL_POINTS);
		glVertex3f(m_GussianRandomPoint[i].x, m_GussianRandomPoint[i].y, 0.0);
		glEnd();
	}
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(100.0*cos(m_GussianSigma), 100.0*sin(m_GussianSigma), 0);
	glEnd();
	return true;
}
void COpenGLRibbontoSiNongView::OnButtonDrawgussianpoint()                       //点击<高斯>
{
	srand(GetTickCount());
	double SigmaRadius;//ThegemaRadius，ThegemaTangent需要进行调整的变量
	double SigmaTheta;
	double Radius;
	double Theta0;
	int NumofPoint;
	      //从ribbon中获取数据
	CMFCRibbonBar *pRibbon = ((CMainFrame*)AfxGetMainWnd())->GetRibbonBar();
	ASSERT_VALID(pRibbon);
	CMFCRibbonEdit *pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbon->FindByID(ID_GUSSIAN_NUM));
	NumofPoint = atoi(pEdit->GetEditText());

	pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbon->FindByID(ID_GUSSIAN_SIGMAR));
	SigmaRadius = atof(pEdit->GetEditText());

	pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbon->FindByID(ID_GUSSIAN_SIGMATHETA));
	SigmaTheta = atof(pEdit->GetEditText());

	pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbon->FindByID(ID_GUSSIAN_R));
	Radius = atof(pEdit->GetEditText());

	pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbon->FindByID(ID_GUSSIAN_GRADIENT));
	Theta0 = atof(pEdit->GetEditText()) *PI / 180.0;

	//实验抛点时，centerpoint取零点
	Point CenterofPoint;
	CenterofPoint.x = 0;
	CenterofPoint.y = 0;
	CenterofPoint.angle = PI / 2;
	m_GussianRandomPoint = new Point[NumofPoint];
	CGenerateRandomPoint randompoint(SigmaRadius, SigmaTheta, Radius, Theta0, CenterofPoint);

	for (int i = 0; i<NumofPoint; i++)
	{
		m_GussianRandomPoint[i] = randompoint.GetRandomPoint();
	}
	
	flag_GussianSimu = 1;
	m_GussianSigma = Theta0;
	Num_GussianRandomPoint = NumofPoint;
	SendMessage(WM_PAINT, NULL);

	// TODO: Add your command handler code here
}


void COpenGLRibbontoSiNongView::OnEditPointX()
{
	// TODO: Add your command handler code here
}


void COpenGLRibbontoSiNongView::OnEditPointY()
{
	// TODO: Add your command handler code here
}


void COpenGLRibbontoSiNongView::OnGussianGradient()
{
	// TODO: Add your command handler code here
}


void COpenGLRibbontoSiNongView::OnGussianNum()
{
	// TODO: Add your command handler code here
}


void COpenGLRibbontoSiNongView::OnGussianR()
{
	// TODO: Add your command handler code here
}

void COpenGLRibbontoSiNongView::OnGussianSigmar()
{
	// TODO: Add your command handler code here
}

void COpenGLRibbontoSiNongView::OnGussianSigmatheta()
{
	// TODO: Add your command handler code here
}

void COpenGLRibbontoSiNongView::OnButtonClearallpoint()               //点击<清除所有点>
{
	flag_DrawBox = 0;
	flag_DrawPoint = 0;
	flag_GussianSimu = 0;
	flag_DrawGps = 0;
	flag_points = 0;
	flag_lines = 0;
	flag_rectangle = 0;
	SendMessage(WM_PAINT);
	// TODO: Add your command handler code here
}

void COpenGLRibbontoSiNongView::OnButtonDrawunsortedgps()              //点击<画GPS>
{
	flag_DrawGps = 1;
	vector<Point> vec;
	m_DrawGpsData = vec;
	for (int i = 0; i < m_GpsDataBuffer.size(); i++)
	{
		m_DrawGpsData.push_back(m_GpsDataBuffer[i]);
		SendMessage(WM_PAINT);
		Sleep(1);
	}
	// TODO: Add your command handler code here
}

void COpenGLRibbontoSiNongView::OnButtonSortgps()                //点击<排序>
{
	vector<Point> sortedGps;
	Point InitialPoint;
	InitialPoint.x = 0;
	InitialPoint.y = 0;
	double velocity_max = 100;//
	double dt = 0.01;//0.01的取样间隔
	double step_max = 10;
	sortedGps.push_back(InitialPoint);
	//找第二个点
	double mindis = 1000000;
	Point secondpoint;
	for (int i = 0; i < m_GpsDataBuffer.size(); i++)
	{
		double dis = CToponology::Distance_2(InitialPoint, m_GpsDataBuffer[i]);
		if (dis < mindis&&dis > 0.05*0.05)//这是为了避免找到初始位置的停车时候的重复点
		{
			mindis = dis;
			secondpoint = m_GpsDataBuffer[i];
		}
	}
	sortedGps.push_back(secondpoint);
	for (int i = 0; i < sortedGps.size(); i++)
	{
		sortedGps[0].angle =
			CToponology::AngleNormalnize1(atan2(sortedGps[1].y - sortedGps[0].y,
				sortedGps[1].x - sortedGps[0].x));
		sortedGps[1].angle = sortedGps[0].angle;
	}
	for (int i = 0; i < m_GpsDataBuffer.size(); i++)
	{
		Point curPoint = sortedGps[sortedGps.size() - 1];
		Point lastPoint = sortedGps[sortedGps.size() - 2];
		Point choosepoint;
		mindis = 1000000;
		vector<Point> nearpoint;//存那些满足条件的点的
		for (int j = 0; j < m_GpsDataBuffer.size(); j++)
		{
			Point ppoint = m_GpsDataBuffer[j];
			double angle1 = CToponology::AngleNormalnize1(atan2(ppoint.y - curPoint.y,
				ppoint.x - curPoint.x));//当前点向新找的点的连线角
			//现在要求两个点的差值的cos值
			double cosangle = cos(fabs(angle1 - curPoint.angle));
			double dis = CToponology::Distance_2(curPoint, ppoint);
			//首先小于这个阈值的以及角度对的数据都存进来吧，然后挑一个距离最小的
			if (/*cosangle>0&&*/dis < step_max*step_max&&dis>0.00001)
			{
				if (cosangle>0)
				{
					nearpoint.push_back(ppoint);
				}
			}
		}
		for (int j = 0; j < nearpoint.size(); j++)
		{
			double dis = CToponology::Distance_2(curPoint, nearpoint[j]);
			if (dis < mindis)//这是为了避免找到初始位置的停车时候的重复点
			{
				mindis = dis;
				choosepoint = nearpoint[j];
			}
		}
		if (nearpoint.size()==0)
		{
			continue;
		}
		else
		{
			choosepoint.angle = CToponology::AngleNormalnize1(atan2(choosepoint.y - curPoint.y,
				choosepoint.x - curPoint.x));
			sortedGps.push_back(choosepoint);
		}
	}
	m_GpsDataBuffer = sortedGps;
	// TODO: Add your command handler code here
}

bool COpenGLRibbontoSiNongView::DrawGPSPointonetoone()                        //画GPS
{
	glPointSize(5);
	glColor3f(1, 0, 0);
	for (int i = 0; i<m_DrawGpsData.size(); i++)
	{
		glBegin(GL_POINTS);
		glVertex3f(m_DrawGpsData[i].x, m_DrawGpsData[i].y, 0.0);
		glEnd();
	}
	return true;
}



void COpenGLRibbontoSiNongView::OnButtonReadgpsfile()               //读GPS文件
{
	Point InitialPoint;
	InitialPoint.x = 246345.71525;
	InitialPoint.y = 3381886.44137;
	CFileDialog flg(TRUE);      //显示文件读取对话框
	if (flg.DoModal()==IDOK)   //IDOK为显示对话框成功
	{
		FILE *fp;
		fopen_s(&fp, flg.GetPathName(), "r");
		while (!feof(fp))
		{
			double a = 0;
			double b = 0;
			fscanf_s(fp, "%lf\t%lf\n", &a, &b);
			Point gp;
			gp.x = a - InitialPoint.x;
			gp.y = b - InitialPoint.y;
			m_GpsDataBuffer.push_back(gp);
		}
	}
	// TODO: Add your command handler code here
}



/****************************画图操作************************************/
void COpenGLRibbontoSiNongView::OnPoint()
{
	// TODO: 在此添加命令处理程序代码
	flag_points = 1;
	m_DataShowPro.n = FALSE;
	flag_lines = flag_rectangle = 2;
	SendMessage(WM_PAINT);
}

bool COpenGLRibbontoSiNongView::Drawpoint()
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(10);
	for (int i = 0; i < datas.onepoint.size(); i++)
	{	
		glBegin(GL_POINTS);
		glVertex3f(datas.onepoint[i].x, datas.onepoint[i].y, 0);
		glEnd();
	}
	return true;
}



void COpenGLRibbontoSiNongView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	flag_lines = 1;
	m_DataShowPro.n = FALSE;
	flag_points = flag_rectangle = 2;
	SendMessage(WM_PAINT);
}

bool COpenGLRibbontoSiNongView::Drawline()
{
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(10);
	for (int i = 0; i < datas.line.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex3f(datas.line[i].begin.x, datas.line[i].begin.y, 0);
		glVertex3f(datas.line[i].end.x, datas.line[i].end.y, 0);
		glEnd();
	}
	return true;
}


void COpenGLRibbontoSiNongView::OnRectangle()
{
	// TODO: 在此添加命令处理程序代码
	flag_rectangle = 1;
	m_DataShowPro.n = FALSE;
	flag_lines = flag_points = 2;
}

bool COpenGLRibbontoSiNongView::Drawrectangle()
{
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(10);
	for (int i = 0; i < datas.juxing.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex3f(datas.juxing[i].begin.x, datas.juxing[i].begin.y, 0);
		glVertex3f(datas.juxing[i].begin.x, datas.juxing[i].end.y, 0);

		glVertex3f(datas.juxing[i].begin.x, datas.juxing[i].end.y, 0);
		glVertex3f(datas.juxing[i].end.x, datas.juxing[i].end.y, 0);

		glVertex3f(datas.juxing[i].end.x, datas.juxing[i].end.y, 0);
		glVertex3f(datas.juxing[i].end.x, datas.juxing[i].begin.y, 0);

		glVertex3f(datas.juxing[i].end.x, datas.juxing[i].begin.y, 0);
		glVertex3f(datas.juxing[i].begin.x, datas.juxing[i].begin.y, 0);
		glEnd();
	}
	return true;
}
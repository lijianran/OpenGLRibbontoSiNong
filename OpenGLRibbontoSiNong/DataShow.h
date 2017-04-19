#pragma once
// OpenGL 头文件
#include <vector>
using namespace std;
#include "glu.h"
#include "GLAUX.H"



enum ButtonType
{
	leftDown=0,
	rightDown=1,
	other=2

};
typedef struct 
{
	float x;
	float y;
	float z;

}PointShow;
//// 历史视角位置
//struct ViewFocusM
//{
//	float x_move,   y_move;	               //记录模型平移
//	float m_zoom;                          //放大倍率
//	float x_rotate,  y_rotate,  z_rotate;  //记录模型旋转
//};
typedef void((*DrawPoint)(vector<PointShow>));

class CDataShow
{
public:
	CDataShow(void);
	~CDataShow(void);
private:
	BOOL m_bSnapScreen;
	BOOL m_bDrawPoints;
	float m_eyex, m_eyey,  m_eyez; 
	float m_centerx,  m_centery, m_centerz; 
	float m_upx, m_upy, m_upz;
	int m_GLPixelIndex;       //像素格式索引号

	float x_rotate,y_rotate,z_rotate;  //记录模型旋转
	float m_zoom;				//缩放比例
	float x_rotate_save,y_rotate_save,z_rotate_save; 
	float x_move_save,y_move_save;
	int x_lbefore,y_lbefore;          //记录鼠标按下时的坐标位置
	int x_rbefore,y_rbefore;
	int z_before1,z_before2;
	int winX,winY;
	int m_NumPixel;
	int snapid;
public:	
	BOOL n;
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];


	// 绘图设置
	HGLRC m_hGLContext;                 // 窗口着色描述表句柄
	void InitialScene(CPaintDC& dc,HDC hDC);
	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
    int OnCreate(HWND hWnd);
	void SetOneViewFocus(int index); // 重置视角


	void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);          //鼠标获取的数据
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
    void OnRButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);

	int m_nButtonFlag;
	// 画画
	void Draw_grid (int meters_per_grid);
	void Draw_compass(double x,double y,double z);
	void Draw_Road_Center_Point();
	void Draw_coordinate();
	void Draw_current_vehicle(float x, float y , float tht);
	void OnSize(UINT nType, int cx, int cy);
	//画图回调函数
private:
	DrawPoint m_fpointFunc;
public:
	int SetPointCallback(DrawPoint dpFunc){ m_fpointFunc=dpFunc;};
	void SetSceneRot(int axis,int value,BOOL increment,BOOL apply);
	void SetCamPos(int axis,int value,BOOL increment,BOOL apply);
	float x_move, y_move;		//记录模型平移
	float camRot[3];
	float camPos[3];
	float sceneRot[3];
	float scenePos[3];
	BOOL mouserightdown;
	BOOL mouseleftdown;
    CPoint mouseprevpoint;
	
	void SetView(float f);
	void Draw_circle(int radious, int meters_per_difference);
};



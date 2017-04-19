#pragma once
// OpenGL ͷ�ļ�
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
//// ��ʷ�ӽ�λ��
//struct ViewFocusM
//{
//	float x_move,   y_move;	               //��¼ģ��ƽ��
//	float m_zoom;                          //�Ŵ���
//	float x_rotate,  y_rotate,  z_rotate;  //��¼ģ����ת
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
	int m_GLPixelIndex;       //���ظ�ʽ������

	float x_rotate,y_rotate,z_rotate;  //��¼ģ����ת
	float m_zoom;				//���ű���
	float x_rotate_save,y_rotate_save,z_rotate_save; 
	float x_move_save,y_move_save;
	int x_lbefore,y_lbefore;          //��¼��갴��ʱ������λ��
	int x_rbefore,y_rbefore;
	int z_before1,z_before2;
	int winX,winY;
	int m_NumPixel;
	int snapid;
public:	
	BOOL n;
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];


	// ��ͼ����
	HGLRC m_hGLContext;                 // ������ɫ��������
	void InitialScene(CPaintDC& dc,HDC hDC);
	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
    int OnCreate(HWND hWnd);
	void SetOneViewFocus(int index); // �����ӽ�


	void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);          //����ȡ������
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
    void OnRButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);

	int m_nButtonFlag;
	// ����
	void Draw_grid (int meters_per_grid);
	void Draw_compass(double x,double y,double z);
	void Draw_Road_Center_Point();
	void Draw_coordinate();
	void Draw_current_vehicle(float x, float y , float tht);
	void OnSize(UINT nType, int cx, int cy);
	//��ͼ�ص�����
private:
	DrawPoint m_fpointFunc;
public:
	int SetPointCallback(DrawPoint dpFunc){ m_fpointFunc=dpFunc;};
	void SetSceneRot(int axis,int value,BOOL increment,BOOL apply);
	void SetCamPos(int axis,int value,BOOL increment,BOOL apply);
	float x_move, y_move;		//��¼ģ��ƽ��
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




#include "StdAfx.h"
#include "DataShow.h"
#define  _USE_MATH_DEFINES//定义带参数宏max(a,b)  要文本现max(a,b)格式文本论a b何种
                          //类型 均替换(((a)>(b))?(a):(b))格式文本 再进行编译
#include <math.h>

static void draw_letter_N ()
{
	
	glBegin (GL_QUADS);        //画四边形  "N"

	glVertex3f (-1.0, 8.5, 0);
	glVertex3f (-0.5, 8.5, 0);
	glVertex3f (-0.5, 10.5, 0);
	glVertex3f (-1.0, 10.5, 0);

	glVertex3f (1.0, 8.5, 0);
	glVertex3f (0.5, 8.5, 0);
	glVertex3f (0.5, 10.5, 0);
	glVertex3f (1.0, 10.5, 0);

	glVertex3f (-0.5, 10.5, 0);
	glVertex3f (-1.0, 10.5, 0);
	glVertex3f (0.5, 8.5, 0);
	glVertex3f (1.0, 8.5, 0);

	glEnd ();
}


CDataShow::CDataShow(void)             //datashow类构造函数
{
	n = TRUE;

	camPos[0]=0.0f;
	camPos[1]=0.0f;
	camPos[2]=-25.0f;
	camRot[0]=-50.0f;
	camRot[1]=0.0f;
	camRot[2]=0.0f;

	scenePos[0]=0.0f;
	scenePos[1]=0.0f;
	scenePos[2]=0.0f;
    sceneRot[0]=0.0f;
	sceneRot[1]=0.0f;
	sceneRot[2]=0.0f;

	mouseprevpoint.x=0;
	mouseprevpoint.y=0;

	mouserightdown=FALSE;
	mouseleftdown=FALSE;
	
	//显示每部分的开关
	m_bDrawPoints=TRUE;

	// 视点选择的位置
	m_eyex=0,  m_eyey=0,  m_eyez=80; 
	m_centerx=0,  m_centery=0, m_centerz=0; 
	m_upx=0,  m_upy=1, m_upz=0;

	///////////Snap Screen //////////
	m_bSnapScreen= FALSE;
	///////////////////////////////

	// OpenGL
	m_hGLContext = NULL;
	m_GLPixelIndex = 0;


	//记录模型平移
	x_move = 0;
	y_move = 0;
	//记录模型旋转
	x_rotate=0;
	y_rotate=0;
	z_rotate=0;  

	//缩放比例
	m_zoom=1;				

	//记录鼠标按下时的坐标位置
	x_lbefore=0,y_lbefore=0;          
	x_rbefore=0,y_rbefore=0;
	z_before1=0,z_before2=0;
	m_nButtonFlag=other;
	m_NumPixel= 5;
	//SetCamPos(2, 50, TRUE, TRUE);
}

CDataShow::~CDataShow(void)
{
}



// CMainControlDlg 消息处理程序

BOOL CDataShow::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	//初始化pixelDesc像素格式
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	
	pixelDesc.dwFlags = \
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;
	//表明应用程序使用OpenGL函数来绘制窗口
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;
	//m_GLPixelIndex是像素格式索引号
	m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc); //调用ChoosePixelFormat()选择一个像素格式
	if(m_GLPixelIndex == 0) // Choose default
	{
		m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
			return FALSE;
	}
	
	if(!SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc))//调用SetPixelFormat()设置像素格式
		return FALSE;
	
	return TRUE;
}


//********************************************
// CreateViewGLContext
// Create an OpenGL rendering context
//********************************************
BOOL CDataShow::CreateViewGLContext(HDC hDC)   ////产生RC并使之成为当前RC
{
	m_hGLContext = wglCreateContext(hDC);      //创建一个新的opengl渲染着色描述表
	
	if(m_hGLContext==NULL)
		return FALSE;
	
	if(wglMakeCurrent(hDC,m_hGLContext)==FALSE)//使一个指定的opengl渲染 加载到 当前上下文句柄
		return FALSE;
	
	return TRUE;  
}

void CDataShow::InitialScene(CPaintDC& dc,HDC hDC)                     //保存实例，以便重绘。
{
	glClearColor(0.0,0.0,0.078,1); //0.192 0.078
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //表示清除颜色缓冲以及深度缓冲
	glMatrixMode(GL_MODELVIEW);    //指定哪一个矩阵使当前矩阵	 GL_MODELVIEW☞模型视景矩阵
	glLoadIdentity();//与glMatrixMode一起使用，将当前的用户坐标系的原点移动到屏幕中心，复位操作

	glPushMatrix();//将当前矩阵保存入堆栈顶（保存当前矩阵）

	if (n)
	{
		glTranslatef(x_move,y_move,0);//鼠标移动造成的位移
	}
	glTranslatef(camPos[0],camPos[1],camPos[2]);//放大缩小  通过移动物体来实现放大缩小
	//glScalef(0.1, 0.1, 0.1);  

	glRotatef(camRot[0],1.0f,0.0f,0.0f);
	glRotatef(camRot[1],0.0f,1.0f,0.0f);
	glRotatef(camRot[2],0.0f,0.0f,1.0f);
	//::glPushMatrix();
	glTranslatef(scenePos[0],scenePos[1],scenePos[2]);	//无用
	glRotatef(sceneRot[0],1.0f,0.0f,0.0f);//绕x轴旋转
	glRotatef(sceneRot[1],0.0f,1.0f,0.0f);//绕y轴旋转
	glRotatef(sceneRot[2],0.0f,0.0f,1.0f);//绕z轴旋转

	glGetIntegerv(GL_VIEWPORT, viewport);   /* 获取三个矩阵 */
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	



	//开始画图
	//Draw_compass(20,-15,0.0); // 罗盘
	//Draw_grid(10); // 网格
	//Draw_Road_Center_Point();
	//Draw_circle(10,10);
	//Draw_coordinate();
	//::glPopMatrix();
	//
	//
	//m_fpointFunc();
	////SwapBuffers(dc.m_ps.hdc);
	
	//wglMakeCurrent(NULL,NULL);
}

/************************************************************************/
/*                       鼠标按键操作响应                               */
/************************************************************************/
void CDataShow::OnLButtonDown(UINT nFlags, CPoint point)                     //左键按下
{
	// TODO: Add your message handler code here and/or call default
	x_lbefore=point.x;
	y_lbefore=point.y;

	//mouseleftdown=TRUE;
	//mouseprevpoint.x=point.x;
	//mouseprevpoint.y=point.y;

    //SetCapture();
}
void CDataShow::OnLButtonUp(UINT nFlags, CPoint point)                     //左键弹起
{
	// TODO: Add your message handler code here and/or call default

	//x_move += (point.x - x_lbefore) / 50;
	//y_move += (y_lbefore - point.y) / 50;

	x_move += (point.x - x_lbefore) / 10;   //获取鼠标位移值
	y_move += (y_lbefore - point.y) / 10;   //用来移动模型

	//this->InitialScene();

	//mouseleftdown=FALSE;
	//SetSceneRot(0,(point.y-mouseprevpoint.y),TRUE,TRUE);//改变绕x轴旋转的角度     完成移动鼠标中的最后一次任务
	//SetSceneRot(2,(point.x-mouseprevpoint.x),TRUE,TRUE);//改变绕z轴旋转的角度
}
void CDataShow::OnRButtonDown(UINT nFlags, CPoint point)                //右键按下
{
	mouserightdown = TRUE;
	mouseprevpoint.x = point.x;
	mouseprevpoint.y = point.y;

	x_rbefore=point.x;
	y_rbefore=point.y;
}
void CDataShow::OnRButtonUp(UINT nFlags, CPoint point)                   //右键弹起
{
	y_rotate -= (point.x - x_rbefore) / 100;        //模型旋转
	x_rotate -= (y_rbefore - point.y) / 100;

	if (x_rotate > 360)
		x_rotate=x_rotate - 360;
	if (x_rotate < -360)
		x_rotate=x_rotate + 360;
	if (y_rotate > 360)
		y_rotate=y_rotate - 360;
	if (y_rotate < -360)
		y_rotate=y_rotate + 360;

	mouserightdown = FALSE;
	SetSceneRot(0, (point.y - mouseprevpoint.y), TRUE, TRUE);//改变绕x轴旋转的角度     完成移动鼠标中的最后一次任务
	SetSceneRot(2, (point.x - mouseprevpoint.x), TRUE, TRUE);//改变绕z轴旋转的角度
}

BOOL CDataShow::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)     //由view类响应鼠标滑轮消息转入  缩放
{
	// TODO: Add your message handler code here and/or call default
	bool zoomin = (zDelta>0);   //向上滑动为真，向下滑动为假
	float zoomratio = zDelta / 60.0;//向上滑动为正数，向下滑动为负数
	//TRACE("OnMouseWheel %f\n",zoomratio);
	if (zoomin>0)//向上滑动（放大）
	{
		m_zoom = m_zoom*(1 + zoomratio);
	}
	else//向下滑动（缩小）
	{
		m_zoom = m_zoom / (1 - zoomratio);
	}
	SetCamPos(2, zoomratio, TRUE, TRUE);
	//	this->RenderScene();
	return 1;
}


void CDataShow::OnMouseMove(UINT nFlags, CPoint point)                    //鼠标移动
{
	if (mouserightdown)     //右键按下为真，弹起为假
	{
		SetSceneRot(0, (point.y - mouseprevpoint.y), TRUE, TRUE);
		SetSceneRot(2, (point.x - mouseprevpoint.x), TRUE, TRUE);
	}
	else if (mouseleftdown)     //左键按下为真，弹起为假          按住左键来旋转
	{
		SetSceneRot(0, (point.y - mouseprevpoint.y), TRUE, TRUE);
		SetSceneRot(2, (point.x - mouseprevpoint.x), TRUE, TRUE);
	}
	mouseprevpoint.x = point.x;   //不断改变起点
	mouseprevpoint.y = point.y;
}




void CDataShow::SetOneViewFocus(int index)  //重置视角
{
	//记录模型平移
	//x_move=m_ViewfocusM[index].x_move;
	//y_move=m_ViewfocusM[index].y_move;
	////缩放比例
	//m_zoom=m_ViewfocusM[index].m_zoom;
	////记录模型旋转
	//x_rotate=m_ViewfocusM[index].x_rotate;
	//y_rotate=m_ViewfocusM[index].y_rotate;
	//z_rotate=m_ViewfocusM[index].z_rotate;
}

void CDataShow::Draw_compass(double x,double y,double z)                     //画罗盘
{
//    int viewport[4];
//    int pos[2] = { -50, -50 };
//    int radius = 35;
//
//    double carpos[3] = { 0, 0, 0 };
//    double heading = 0, variance = 0;
//
//
//    /* Find the world x,y coordinates for the compass, given we want it
//     * near the side of the viewport. */
//    glGetIntegerv (GL_VIEWPORT, viewport);
//
//    /* Find the world x,y coordinates for the edge of the compass, so
//     * we can compute how large to make it in world coordinates. */
//    double x2=0, y2=0;
//
//    glDisable (GL_DEPTH_TEST);
//    glEnable (GL_BLEND);
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    /* Draw the compass at the right place, size, and orientation */
//    glPushMatrix ();
//    glTranslatef (x, y, z);
//
////  double scale = sqrt ((x2-x)*(x2-x) + (y2-y)*(y2-y));
//
//	double scale = 3.0;
//    glScalef (scale, scale, scale);
//
//    glRotatef (heading * 180 / M_PI + 90, 0, 0, 1);
//
//    GLUquadricObj * q = gluNewQuadric ();
//
//    /* Draw an error bar indicating one standard deviation of the
//     * heading error.  If it's above the threshold, make it red. */
//
//    glColor4f (0.8, 0.2, 0.2, 0.7);
//    double std_deg = sqrt (variance) * 180 / M_PI;
//    gluPartialDisk (q, 1.0, 1.1, 50, 1,
//            90 - std_deg, 2 * std_deg);
//
//    /* Draw the circle for the compass */
//    glColor4f (1.0, 1.0, 1.0, 0.2);
//    gluDisk (q, 0, 1.0, 20, 1);
//    gluDeleteQuadric (q);
//
//    /* Draw the arrow on the compass */
//    glLineWidth (2.0);
//    glColor4f (1.0, 1.0, 1.0, 1.0);
//    glBegin (GL_LINES);
//    glVertex3f (-0.5, 0, 0);
//    glVertex3f ( 0.5, 0, 0);
//
//    glVertex3f (0, 0.5, 0);
//    glVertex3f (0, -0.5, 0);
//
//    glVertex3f (0.25, 0.25, 0);
//    glVertex3f (0.5, 0, 0);
//
//    glVertex3f (0.25, -0.25, 0);
//    glVertex3f (0.5, 0, 0);
//    glEnd ();
//
//    /* Draw tick marks around the compass (15 degree increments) */
//    glLineWidth (1.0);
//    int i;
//    for (i = 30; i <= 330; i += 15) 
//	{
//        glPushMatrix ();
//        glRotatef (i, 0, 0, 1);
//        glBegin (GL_LINES);
//        glVertex3f (0.95, 0, 0.0);
//        glVertex3f (((i % 45) == 0) ? 0.75 : 0.85, 0, 0.0);
//        glEnd ();
//        glPopMatrix ();
//    }
//
//    /* Draw the letter N */
//    glColor4f (0.2, 1.0, 0.6, 1.0);
//    glTranslatef (0.75, 0, 0);
//    glScalef (0.2, 0.2, 0.2);
//    glRotatef (90, 0, 0, 1);
//    draw_letter_N();
//
//    glDisable (GL_BLEND);
//
//    glPopMatrix ();
	glColor3f(1,0,0);
	glBegin(GL_QUADS);
	glEnd();
}

void CDataShow::Draw_grid (int meters_per_grid)               //画网格   由view类onPaint调用   5
{
	double pos[3]={0,0,0};
	double grids_per_screen = 10;

	int num_lines = 200;
	//ceil函数包含于math.h头文件中，用于返回大于或者等于指定表达式的最小整数
	double grid_ox = ceil (pos[0] / meters_per_grid) * meters_per_grid;
	double grid_oy = ceil (pos[1] / meters_per_grid) * meters_per_grid;
	double grid_oz = pos[2];

	glPushMatrix ();//将当前矩阵压入栈中，当前矩阵不清零，其下的操作和显示在当前矩阵下继续进行
	glTranslatef (grid_ox, grid_oy, grid_oz);   //移动

	//glColor4f(0.1, 0.2, 0.1, 0.5);
	glColor3f (0.3, 0.3, 0.3);
	glEnable(GL_BLEND);//用于启动各种功能，由参数决定     GL_BLEND：色彩混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//表示用1.0减去源颜色的alpha值来作为因子
	//glBlendFunc()设置颜色混合透明度叠加计算
	//GL_SRC_ALPHA：表示使用源颜色的alpha值来作为因子
	glDisable(GL_DEPTH_TEST);//用于关闭各种功能，由参数决定     
	        //GL_DEPTH_TEST  进行深度比较和深度缓冲
	glBegin(GL_LINES);    //画多条线   把每一个顶点作为一个独立的线段，
	                                 //顶点2n－1和2n之间共定义了n条线段，总共绘制N/2条线段
	glVertex2f((+num_lines/2)*meters_per_grid, (-num_lines/2)*meters_per_grid);
	glVertex2f((+num_lines/2)*meters_per_grid, (+num_lines/2)*meters_per_grid);
	glVertex2f((+num_lines/2)*meters_per_grid, (+num_lines/2)*meters_per_grid);
	glVertex2f((-num_lines/2)*meters_per_grid, (+num_lines/2)*meters_per_grid);
	glEnd();

	glLineWidth (1);
	glEnable (GL_DEPTH_TEST);
	glBegin (GL_LINES);
	//glColor3f (0.3, 0.3, 0.3);

	for (int i=0; i<num_lines; i++) 
	{
		glVertex2f ((-num_lines/2 + i) * meters_per_grid,
			- num_lines/2 * meters_per_grid);
		glVertex2f ((-num_lines/2 + i) * meters_per_grid,
			num_lines/2 * meters_per_grid);

		glVertex2f (- num_lines/2 * meters_per_grid,
			(-num_lines/2 + i) * meters_per_grid);
		glVertex2f (num_lines/2 * meters_per_grid,
			(-num_lines/2 + i) * meters_per_grid);
	}
	glEnd();
	glDisable (GL_DEPTH_TEST);
	glDisable (GL_BLEND);

	glPopMatrix ();      //还原到使用glpPushMrtrix()入栈前的矩阵，复原
}


int CDataShow::OnCreate(HWND hWnd)         //响应VIEW.CPP中的创建窗口函数
{
	
	// TODO:  在此添加您专用的创建代码
	HDC hDC = ::GetDC(hWnd);
	
	if(SetWindowPixelFormat(hDC)==FALSE)   //设置像素格式
		return 0;

	if(CreateViewGLContext(hDC)==FALSE)    //创建上下文渲染描述表，
		return 0;						   ////创建渲染描述表之前应该仙设置设备描述表的像素格式

	return 0;
}

void CDataShow::OnSize(UINT nType, int cx, int cy)      //窗口变化
{
	glViewport(0,0,cx,cy);
	GLdouble aspect_ratio;
	aspect_ratio=(GLdouble)cx/(GLdouble)cy;
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	gluPerspective(90.0f,aspect_ratio,10.0f,900.0f);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	glDrawBuffer(GL_BACK);
}

void CDataShow::SetCamPos(int axis,int value,BOOL increment,BOOL apply)   //鼠标滑轮进行缩放
{
	if (increment)
	{
		camPos[axis] -= (float)value*camPos[axis] / 100;
	}
	else
	{
		camPos[axis]=(float)value/2;
	}
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();       //将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
}

void CDataShow::SetSceneRot(int axis,int value,BOOL increment,BOOL apply)   //0 2   移动数值   true true
{
	/*if (increment)
	{
	sceneRot[axis]+=(sceneRot[axis]>=360)?(-360+value/2):value/2;
	}
	else
	{
	sceneRot[axis]+=(sceneRot[axis]>=360)?(-360+value/2):value/2;
	}*/

	sceneRot[axis]+=(sceneRot[axis]>=360)?(-360+value/2):value/2;            //旋转角度的改变
}

void CDataShow::SetView(float f)       //无用
{
	camPos[0] = 0.0f;
	camPos[1] = 0.0f;
	camPos[2] = -60.0f;
	camRot[0] = -70.0f;
	camRot[1] = 0.0f;
	camRot[2] = 0.0f;

	scenePos[0] = 0.0f;
	scenePos[1] = 0.0f;
	scenePos[2] = 0.0f;
	sceneRot[0] = 0.0f;
	sceneRot[1] = 0.0f;
	sceneRot[2] = 0.0f;
}


void CDataShow::Draw_circle(int radious, int meters_per_difference)           //5  5 画圆盘坐标系
{
	glLineWidth(1);
	glColor3f (0.3, 0.3, 0.3);
	glBegin(GL_LINE_STRIP);//绘制从第一个顶点到最后一个顶点依次相连的一组线段，
	                       //第n和n+1个顶点定义了线段n，总共绘制n－1条线段
	GLfloat step = 0.1f;
	GLfloat angle;
	for (int i = 0;i<meters_per_difference*10;i += meters_per_difference)
	{
		for (angle = 0.0f;angle <= 2.0f*3.1415926f;angle += step)
		{
			glVertex3f((radious+i)*sin(angle),(radious+i)*cos(angle),0);   //和角公式
		}
		glVertex3f((radious+i)*sin(2.0f*3.1415926f),(radious+i)*cos(2.0f*3.1415926f),0);  //旋转
	}
	glEnd();
}


void CDataShow::Draw_coordinate() //画坐标系和箭头
{	
	glLineWidth(1);

	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(6,0,0);
	glEnd();
	glBegin(GL_TRIANGLES);  //画三角形
	glVertex3f(6,-0.5,0);
	glVertex3f(6,0.5,0);
	glVertex3f(8,0,0);
	glEnd();

	glColor3f(1,1,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,6,0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5,6,0);
	glVertex3f(0.5,6,0);
	glVertex3f(0,8,0);
	glEnd();

	draw_letter_N();  //画四边形   "N"
	//glutSolidCone(0.5,1.5,20,20);//画圆锥
}
void CDataShow::Draw_Road_Center_Point() //坐标系
{
	/*glLineWidth(3);

	glBegin(GL_LINES);
	glColor3f(0,1,0);
	glVertex3d(0,0,0);
	glVertex3d(10,0,0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(10,1,0);
	glVertex3f(10,-1,0);
	glVertex3f(12,0,0);
	glEnd();*/

	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glColor3f(1,1,0);
	glTranslatef(40,30,15);
	glutSolidSphere(2,50,50);
	glTranslatef(-40,-30,-15);
	glDisable(GL_LIGHTING);*/

	/*glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,10,0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(1,10,0);
	glVertex3f(-1.0,10,0);
	glVertex3f(0,12.0,0);
	glEnd();*/
}

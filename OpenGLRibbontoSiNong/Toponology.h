#pragma once
//#include "Obstacle.h"
#include <vector>
using namespace std;
class CToponology
{
public:
	CToponology(void);
	~CToponology(void);
public:

	static double Distance(Point m1,Point m2);

	static double Distance_2(Point m1,Point m2);

	static double cosangle(Point m1,Point m2,Point m3);

	static double multiply(Point sp,Point ep,Point op) ;

	//判断线段与线段是否相交
	static bool intersect(LINESEG u,LINESEG v);//1 is intersect,0 is not

	
	static bool InsideConvexPolygon(int vcount,Point polygon[],Point q); // 可用于三角形！ 
	static bool InsideConvexPolygon(int vcount,vector<Point> polygon,Point q) ;
	//返回1表示相交，返回0表示不相交
	static bool CurveInsects(Point Up[],Point Down[],LINESEG u);

	////判断点是否在障碍物（多个）内的，在障碍物内返回1，不在返回0;

	static double AngleNormalnize1(double phi);

	static double AngleNormalnize2(double phi);

	static double AngleNormalnize_jiaodu(double phi);
	//老版追随，之后会更改

	static bool PolygonOverPolygon(vector<double>vertX, vector<double>vertY, vector<double>_vertX, vector<double>_vertY);//判断两多边形是否相交

	static bool PolygonOverPolygon(vector<Point>vert1, vector<Point>vert2);

	static bool LineSegOverLineSeg(double x1,double y1,double x2,double y2,double u1,double v1,double u2,double v2);//判断段段(x1,y1)-(x2,y2)和线段(u1,v1)-(u2,v2)是否相交

	static bool PointInPolygon(vector<double>vertX, vector<double>vertY,double x,double y);


	static short MiddlePiont_Shan(double firMidPoint_x,double firMidPoint_y);
	//高斯坐标转换
};




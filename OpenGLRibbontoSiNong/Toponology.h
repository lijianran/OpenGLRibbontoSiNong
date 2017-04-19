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

	//�ж��߶����߶��Ƿ��ཻ
	static bool intersect(LINESEG u,LINESEG v);//1 is intersect,0 is not

	
	static bool InsideConvexPolygon(int vcount,Point polygon[],Point q); // �����������Σ� 
	static bool InsideConvexPolygon(int vcount,vector<Point> polygon,Point q) ;
	//����1��ʾ�ཻ������0��ʾ���ཻ
	static bool CurveInsects(Point Up[],Point Down[],LINESEG u);

	////�жϵ��Ƿ����ϰ��������ڵģ����ϰ����ڷ���1�����ڷ���0;

	static double AngleNormalnize1(double phi);

	static double AngleNormalnize2(double phi);

	static double AngleNormalnize_jiaodu(double phi);
	//�ϰ�׷�棬֮������

	static bool PolygonOverPolygon(vector<double>vertX, vector<double>vertY, vector<double>_vertX, vector<double>_vertY);//�ж���������Ƿ��ཻ

	static bool PolygonOverPolygon(vector<Point>vert1, vector<Point>vert2);

	static bool LineSegOverLineSeg(double x1,double y1,double x2,double y2,double u1,double v1,double u2,double v2);//�ж϶ζ�(x1,y1)-(x2,y2)���߶�(u1,v1)-(u2,v2)�Ƿ��ཻ

	static bool PointInPolygon(vector<double>vertX, vector<double>vertY,double x,double y);


	static short MiddlePiont_Shan(double firMidPoint_x,double firMidPoint_y);
	//��˹����ת��
};




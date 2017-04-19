#pragma once
#include "stdafx.h"
class CGenerateRandomPoint
{
public:
	CGenerateRandomPoint(void);
	~CGenerateRandomPoint(void);
	//���ع��캯�����и�ֵ
	//SigmaR �Ǹ�˹��������ľ��������SigmaT�Ǹ�˹��������ĺ��������R���׵��ʼλ��һ��ȡ0��theta�ǳ�ʼ����point���׵����ģ�һ���ǳ���ǰλ�õ�
	CGenerateRandomPoint(double sigmaR,double sigmaT,double R,double theta, Point point)
	{SigmaRadius=sigmaR;SigmaTheta=sigmaT;Radius=R;Theta0=theta;CenterPoint=point;}
	
private:
	double SigmaRadius;//ThegemaRadius��ThegemaTangent��Ҫ���е����ı���
	double SigmaTheta;
	double Radius;
	double Theta0;
	Point CenterPoint;
	 
	Point GeneGussianRandomPoint(Point CenterofRoad,double RoadWidth);
	double Gaussrand(float miu, float sigma);

public:
	inline Point GetRandomPoint(){return GeneGussianRandomPoint(CenterPoint,Radius);}
};


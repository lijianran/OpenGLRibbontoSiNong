#pragma once
#include "stdafx.h"
class CGenerateRandomPoint
{
public:
	CGenerateRandomPoint(void);
	~CGenerateRandomPoint(void);
	//重载构造函数进行赋值
	//SigmaR 是高斯随机参数的径向变量，SigmaT是高斯随机参数的横向变量，R是抛点初始位移一般取0，theta是初始方向，point是抛点中心，一般是车当前位置点
	CGenerateRandomPoint(double sigmaR,double sigmaT,double R,double theta, Point point)
	{SigmaRadius=sigmaR;SigmaTheta=sigmaT;Radius=R;Theta0=theta;CenterPoint=point;}
	
private:
	double SigmaRadius;//ThegemaRadius，ThegemaTangent需要进行调整的变量
	double SigmaTheta;
	double Radius;
	double Theta0;
	Point CenterPoint;
	 
	Point GeneGussianRandomPoint(Point CenterofRoad,double RoadWidth);
	double Gaussrand(float miu, float sigma);

public:
	inline Point GetRandomPoint(){return GeneGussianRandomPoint(CenterPoint,Radius);}
};


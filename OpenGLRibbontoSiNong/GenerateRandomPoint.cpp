#include "stdafx.h"
#include "GenerateRandomPoint.h"
CGenerateRandomPoint::CGenerateRandomPoint(void)
{
}


CGenerateRandomPoint::~CGenerateRandomPoint(void)
{
}
double CGenerateRandomPoint::Gaussrand(float miu, float sigma)
{
	static double V1, V2, S;
	static int phase = 0;
	double X;
	if ( phase == 0 ) 
	{
		do {		

			double U2 = (double)rand() / RAND_MAX;

			double U1 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while(S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	} 
	else
	{
		X = V2 * sqrt(-2 * log(S) / S);
	}

	phase = 1 - phase;

	return (float)X;
}

Point CGenerateRandomPoint::GeneGussianRandomPoint(Point CenterofRoad,double RoadWidth)
{
	Point RandomPoint;

	double RadiusRandom=0;
	double ThetaRandom=0;
	double Radius=0;
	double Theta=0;
	double X0=0,Y0=0;
	double IndexRandom=0;

	X0=CenterofRoad.x;
	Y0=CenterofRoad.y;


	RadiusRandom=Gaussrand(0,1);//调用产生正太随机数的函数产生符号标准正太分布的随机数；
	ThetaRandom=Gaussrand(0,1);
	Radius=SigmaRadius*fabs(RadiusRandom)+RoadWidth;
	Theta=SigmaTheta*ThetaRandom+Theta0;
	RandomPoint.x=X0+Radius*cos(Theta);//generate random point using polar coordinates
	RandomPoint.y=Y0+Radius*sin(Theta);
	RandomPoint.angle=0;
	return RandomPoint;
}


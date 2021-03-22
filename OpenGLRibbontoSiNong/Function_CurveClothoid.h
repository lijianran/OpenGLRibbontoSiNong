#pragma once
#include "stdafx.h"


class CCurveClothoid
{
public:
	CCurveClothoid(void);
	~CCurveClothoid(void);
public:
	static void FresnelCS(double *FresnelC,double *FresnelS,double y);
	static void intXY(double *X,double *Y,int nk,double a,double b,double c);
	static void FresnelCSk(int nk,double t,double *FresnelC,double *FresnelS);
	static void evalXYaLarge(double *X,double *Y,int nk,double a,double b);
	static double S(double mu,double nu,double b);
	static void evalXYazero(double*X,double*Y,int nk,double b);
	static void evalXYaSmall(double *X,double *Y,int nk,double a,double b,double p);
	static double normalizeAngle(double phi_in);
	static void findA(double &A,double Aguess,double delta,double phi0,double tol);
	static double guessA(double phi0,double phi1);


	static void buildClothoid(double &k, double &dk, double &L, double x0, double y0, double theta0, double x1, double y1, double theta1, double tol);
	static void buildClothoid(double &k, double &dk, double &L, Point point1, Point point2, double tol);
	static void pointsOnClothoid(Point XY[], double x0, double y0, double theta0, double kappa, double dkappa, double L, int npts);
	static void pointsOnClothoid(Point XY[], Point point, double kappa, double dkappa, double L, int npts);
};


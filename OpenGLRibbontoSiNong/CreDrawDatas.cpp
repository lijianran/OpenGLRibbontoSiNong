#include "stdafx.h"
#include "CreDrawDatas.h"
#include<cmath>

CreDrawDatas::CreDrawDatas()
{
	choice = 0;
}


CreDrawDatas::~CreDrawDatas()
{
}

double CreDrawDatas::JudgePoint(double x, double y, double x1, double y1, double x2, double y2)
{
	double cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
	if (cross <= 0) 
		return (sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)));

	double d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	if (cross >= d2) 
		return (sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2)));

	double r = cross / d2;
	double px = x1 + (x2 - x1) * r;
	double py = y1 + (y2 - y1) * r;
	return (sqrt((x - px) * (x - px) + (py - y) * (py - y)));
}


#pragma once
#include"stdafx.h"
//#include<GL\freeglut.h>
#include<GL\glut.h>
#include <vector>
using namespace std;

struct points
{
	Point begin;
	Point end;
	int id;
};

struct lines
{
	Point begin;
	Point end;
	int id;
};

struct lineload
{
	Point begin;
	Point end;
	double dx, dy;
	int id;
};

struct wandao
{
	Point xy[100];
	Point begin;
	Point end;
	int id;
	double k;
	double dk;
	double L;
};

class CreDrawDatas
{
public:
	CreDrawDatas();
	~CreDrawDatas();


public:
	points begin_end;
	wandao m;

	double a1, b1, a2, b2;
	vector<Point> onepoint;
	vector<lines> line;
	vector<points> juxing;
	vector<points> circle;
	vector<points> quxian;
	vector<lineload> lineloads;
	vector<wandao> wandaos;


	int choice;

	bool leftdown;
	bool mousemove;
	
public:
	double JudgePoint(double x, double y, double x1, double y1, double x2, double y2);
};




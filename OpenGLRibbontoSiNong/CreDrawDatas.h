#pragma once
#include"stdafx.h"
#include <vector>
using namespace std;

struct points
{
	CPoint begin;
	CPoint end;
};

class CreDrawDatas
{
public:
	CreDrawDatas();
	~CreDrawDatas();


public:
	vector<CPoint> onepoint;
	points begin_end;
	vector<points> line;
	vector<points> juxing;
	vector<points> circle;

};




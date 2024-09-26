#pragma once
#include"Point2D.h"
class Arc {
public:
	Arc();
	Arc(Point2D A, Point2D B, Point2D O);
	Arc& operator=(const Arc& other);
	bool operator<(const Arc& other) const;
	bool operator==(const Arc& other) const;
	~Arc();
public:
	Point2D A;
	Point2D B;
	Point2D O;
	Point2D M;
	double r;
};
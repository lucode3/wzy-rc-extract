#pragma once
#include<iostream>
#include"Point.h"

class Point2D {
public:
	Point2D() {};
	Point2D(double x, double y);
	Point2D(long id, double x, double y);
	Point2D(const Point2D& other) : id(other.id), x(other.x), y(other.y) {};
	bool operator==(const Point2D& other) const;
	~Point2D();
public:
	long id;
	float x;
	float y;
};
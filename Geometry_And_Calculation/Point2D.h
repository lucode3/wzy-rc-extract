#pragma once
#include<iostream>

class Point2D {
public:
	Point2D();
	Point2D(double x, double y);
	Point2D(long id, double x, double y);
	Point2D(const Point2D& other);
	Point2D& operator=(const Point2D& other);
	bool operator==(const Point2D& other) const;
	bool operator<(const Point2D& other) const;
	~Point2D();
public:
	long id;
	double x;
	double y;
};
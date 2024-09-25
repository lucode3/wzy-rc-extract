#pragma once
#include<iostream>
#include"Entity.h"

class Triangle : public Entity {
public:
	Triangle();
	Triangle(long id, Point2D p1, Point2D p2, Point2D p3);
	Triangle& operator=(const Triangle& other);
	~Triangle();
public:
	Point2D p1;
	Point2D p2;
	Point2D p3;
	Point2D circum_center;
	double circum_r;
	Point2D centroid;
};
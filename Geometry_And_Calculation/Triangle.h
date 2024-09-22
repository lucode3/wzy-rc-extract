#pragma once
#include"Entity.h"

class Triangle : public Entity {
public:
	Triangle(long id, Point2D p1, Point2D p2, Point2D p3);
	~Triangle();
public:
	Point2D p1;
	Point2D p2;
	Point2D p3;
};
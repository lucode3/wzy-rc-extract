#pragma once
#include"Point2D.h"

class Segment {
public:
	Segment() {};
	Segment(Point2D p1, Point2D p2);
	Segment(long id, Point2D p1, Point2D p2);
	Segment(const Segment& other);
	bool operator==(const Segment& other) const;
	bool operator<(const Segment& other) const;
	~Segment();

public:
	long id;
	Point2D p1;
	Point2D p2;
};

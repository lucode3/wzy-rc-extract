#include"Segment.h"

Segment::Segment(Point2D p1, Point2D p2) {
	this->id = -1;
	if (p1.x < p2.x) {
		this->p1 = p1;
		this->p2 = p2;
	}
	else {
		this->p2 = p1;
		this->p1 = p2;
	}
}

Segment::Segment(long id, Point2D p1, Point2D p2) {
	this->id = id;
	if (p1.x < p2.x) {
		this->p1 = p1;
		this->p2 = p2;
	}
	else {
		this->p2 = p1;
		this->p1 = p2;
	}
}

bool Segment::operator==(const Segment& other) const {
	if (p1 == other.p1 && p2 == other.p2)
		return true;
	else
		return false;
}

Segment::~Segment() {

}
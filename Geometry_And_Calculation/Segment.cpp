#include"Segment.h"

Segment::Segment(Point2D p1, Point2D p2) {
	this->id = -1;
	if (p1.x < p2.x) {
		this->p1 = p1;
		this->p2 = p2;
	}
	else if (p1.x > p2.x) {
		this->p2 = p1;
		this->p1 = p2;
	}
	else {
		if (p1.y < p2.y) {
			this->p1 = p1;
			this->p2 = p2;
		}
		else {
			this->p1 = p2;
			this->p2 = p1;
		}
	}
}

Segment::Segment(long id, Point2D p1, Point2D p2) {
	this->id = id;
	if (p1.x < p2.x) {
		this->p1 = p1;
		this->p2 = p2;
	}
	else if(p1.x > p2.x){
		this->p2 = p1;
		this->p1 = p2;
	}
	else {
		if (p1.y < p2.y) {
			this->p1 = p1;
			this->p2 = p2;
		}
		else {
			this->p1 = p2;
			this->p2 = p1;
		}
	}
}

Segment::Segment(const Segment& other) : id(other.id), p1(other.p1), p2(other.p2) {

}

bool Segment::operator==(const Segment& other) const {
	if (p1 == other.p1 && p2 == other.p2)
		return true;
	else
		return false;
}

bool Segment::operator<(const Segment& other)const {
	if (p1 == other.p1) {
		return p2 < other.p2;
	}
	return p1 < other.p1;
}

Segment::~Segment() {

}
#include"Point2D.h"

Point2D::Point2D(double x, double y) {
	this->id = -1;
	this->x = x;
	this->y = y;
}

Point2D::Point2D(long id, double x, double y) {
	this->id = id;
	this->x = x;
	this->y = y;
}

bool Point2D::operator==(const Point2D& other) const {
	if (std::abs(x - other.x) < 1e-30 && std::abs(y - other.y) < 1e-30) {
		return true;
	}
	else {
		return false;
	}
}

Point2D::~Point2D() {

}
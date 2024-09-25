#include"Point2D.h"

Point2D::Point2D() {

}
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
Point2D::Point2D(const Point2D& other) : id(other.id), x(other.x), y(other.y) {}

Point2D& Point2D::operator=(const Point2D& other) {
	this->id = other.id;
	this->x = other.x;
	this->y = other.y;
	return *this;
}

bool Point2D::operator==(const Point2D& other) const {
	if (x == other.x && y == other.y) {
		return true;
	}
	else {
		return false;
	}
}

bool Point2D::operator<(const Point2D& other) const {
	if (x == other.x) {
		return y < other.y; // 如果 x 相等，则比较 y
	}
	return x < other.x; // 否则比较 x
}

Point2D::~Point2D() {

}
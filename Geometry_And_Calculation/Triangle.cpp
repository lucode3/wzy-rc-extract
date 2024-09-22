#include"Triangle.h"

Triangle::Triangle(long id, Point2D p1, Point2D p2, Point2D p3) : Entity(id) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

Triangle::~Triangle() {

}
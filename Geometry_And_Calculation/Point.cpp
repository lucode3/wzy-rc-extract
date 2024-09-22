#include"Point.h"

Point::Point(long id) {
	this->id = id;
}

void Point::add_entity(long entity_id) {
	this->entities.insert(entity_id);
}

Point::~Point() {

}
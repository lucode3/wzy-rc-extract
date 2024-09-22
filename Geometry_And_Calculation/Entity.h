#pragma once
#include"Point2D.h"

class Entity {
public:
	Entity(long id);
	virtual ~Entity();
public:
	long id;
};
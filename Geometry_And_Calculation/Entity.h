#pragma once
#include"Point2D.h"

class Entity {
public:
	Entity();
	Entity(long id);
	virtual ~Entity();
public:
	long id;
};
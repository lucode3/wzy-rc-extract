#pragma once
#include<unordered_set>

class Point {
public:
	Point(long id);
	void add_entity(long entity_id);
	virtual bool operator==(const Point & other) const = 0;
	virtual ~Point();
	
public:
	long id;
	std::unordered_set<long> entities;
};

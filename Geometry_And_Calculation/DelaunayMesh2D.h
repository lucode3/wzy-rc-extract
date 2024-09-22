#pragma once
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<map>
#include<algorithm>
#include<vector>
#include <chrono>
#include"Mesh.h"
#include"Triangle.h"
#include"Point2D.h"
#include"Segment.h"
#include"Entity.h"
#include"FindUnionSet.h"
#include"Draw.h"

class DelaunayMesh2D : public Mesh {
public:
	DelaunayMesh2D(int window_x_begin, int window_x_end, int window_y_begin, int window_y_end);
	~DelaunayMesh2D();
	float cross(const Point2D& a, const Point2D& b, const Point2D& c);
	
public:
	void contraint_normalize(std::vector<std::vector<double>>& cps, std::vector<std::vector<double>>& css);


public:
	Draw* drawer;
	std::unordered_map<long, Point2D> constraint_points;
	std::unordered_map<long, Segment> constraint_segments;
	std::map<Segment, std::vector<long>> es_segments;
	std::map<long, Triangle> triangles;


};
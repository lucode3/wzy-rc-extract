#pragma once
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<map>
#include<algorithm>
#include<queue>
#include<vector>
#include <chrono>
#include"Mesh.h"
#include"Triangle.h"
#include"Point2D.h"
#include"Segment.h"
#include"Entity.h"
#include"FindUnionSet.h"
#include"Draw.h"

namespace std {
	template<>
	struct hash<Point2D> {
		size_t operator()(const Point2D& p) const {
			return hash<double>()(p.x) ^ hash<double>()(p.y);
		}
	};
	template<>
	struct hash<Segment> {
		size_t operator()(const Segment& s) const {
			return std::hash<Point2D>()(s.p1) ^ std::hash<Point2D>()(s.p2);
		}
	};
	template<>
	struct hash<std::pair<Segment, Segment>> {
		std::size_t operator()(const std::pair<Segment, Segment>& p) const {
			hash<Segment> segmentHash;
			return segmentHash(p.first) ^ segmentHash(p.second);
		}
	};
}

class DelaunayMesh2D{
public:
	DelaunayMesh2D(int window_x_begin, int window_x_end, int window_y_begin, int window_y_end);
	~DelaunayMesh2D();
	double cross(const Point2D& a, const Point2D& b, const Point2D& c);
	double calculate_angle(const Point2D& A, const Point2D& B, const Point2D& C);
	Point2D find_line_circle_intersection(Point2D& A, Point2D& B, double r);
public:
	void contraint_normalize(std::vector<std::vector<double>>& cps, std::vector<std::vector<double>>& css);
	long search_triangle(Point2D& point);
	long search_triangle_by_distance(Point2D& point);
	void cavity(Point2D& point);
	double local_feature_size(Point2D& CP, std::unordered_set<Point2D>& points, std::unordered_set<Segment>& segments);
	void control_circle_segmentation(std::unordered_set<Point2D>& points, std::unordered_set<Segment>& segments);
	std::vector<Triangle> get_cavity_triangles(Point2D& point);
	bool in_circum(Triangle& t, Point2D& p);
	bool in_triangle(Triangle& t, Point2D& p);
	long get_es_triangle(Segment& s, long cur);
	void del_triangle(Triangle& t);
	void add_triangle(Triangle& t);
	void sort_cavity_points(std::vector<Point2D>& cavity_points, Point2D& center);
	Triangle add_init_Triangle();
	void boundary_subdivision();



public:
	Draw* drawer;
	std::unordered_map<long, Point2D> constraint_points;
	std::unordered_map<long, Segment> constraint_segments;
	std::unordered_set<Segment> css;
	std::map<Segment, std::vector<long>> es_segments;
	std::map<long, Triangle> triangles;
	std::queue<Segment> subdivide_segments;
	long triangle_id_count = 0;
	long segment_id_count = 0;
	long point_id_count = 0;

};
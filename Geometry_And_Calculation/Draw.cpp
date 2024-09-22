#include"Draw.h"

Draw::Draw(int window_x_begin, int window_x_end, int window_y_begin, int window_y_end) {
	this->window_x_begin = window_x_begin;
	this->window_x_end = window_x_end;
	this->window_y_begin = window_y_begin;
	this->window_y_end = window_y_end;
}
Draw::~Draw() {

}

void Draw::plot_points_and_segments(std::unordered_set<Point2D>& points, std::unordered_set<Segment>& segments) {
	std::cout << "points.size = " << points.size() << std::endl;
	for (auto& it : points) {
		std::cout << "id: " << it.id << " (" << it.x << " , " << it.y << ")" << std::endl;
		plt::plot({ it.x }, { it.y }, "ro");  // 'r' 表示红色，'o' 表示点

	}
	std::cout << "segments.size = " << segments.size() << std::endl;
	for (auto& it : segments) {
		std::cout << "id: " << it.id << " (" << it.p1.x << " ," << it.p1.y << ")  (" << it.p2.x << "," << it.p2.y << ")" << std::endl;
		float x1 = it.p1.x;
		float y1 = it.p1.y;
		float x2 = it.p2.x;
		float y2 = it.p2.y;
		// 绘制每条线段
		plt::plot({ x1, x2 }, { y1, y2 }, "b-");  // 蓝色线条.
	}
	// 设置图的范围（可选）
	plt::xlim(this->window_x_begin, this->window_x_end);  // 设置 x 轴范围
	plt::ylim(this->window_y_begin, this->window_y_end);  // 设置 y 轴范围
	// 显示绘图
	plt::show();
}

void Draw::plot_points_and_segments(std::unordered_map<long, Point2D>& points, std::unordered_map<long, Segment>& segments) {
	std::cout << "points.size = " << points.size() << std::endl;
	for (auto it = points.begin(); it != points.end(); it++) {
		std::cout << "id: " << it->first << " (" << it->second.x << " , " << it->second.y << ")" << std::endl;
		plt::plot({ it->second.x }, { it->second.y }, "ro");  // 'r' 表示红色，'o' 表示点

	}
	std::cout << "segments.size = " << segments.size() << std::endl;
	for (auto it = segments.begin(); it != segments.end(); it++) {
		std::cout << "id: " << it->first << " (" << it->second.p1.x << " ," << it->second.p1.y << ")  (" << it->second.p2.x << "," << it->second.p2.y << ")" << std::endl;
		float x1 = it->second.p1.x;
		float y1 = it->second.p1.y;
		float x2 = it->second.p2.x;
		float y2 = it->second.p2.y;
		// 绘制每条线段
		plt::plot({ x1, x2 }, { y1, y2 }, "b-");  // 蓝色线条.
	}
	// 设置图的范围（可选）
	plt::xlim(this->window_x_begin, this->window_x_end);  // 设置 x 轴范围
	plt::ylim(this->window_y_begin, this->window_y_end);  // 设置 y 轴范围
	// 显示绘图
	plt::show();
}
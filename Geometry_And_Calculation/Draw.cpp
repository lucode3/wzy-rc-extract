#include"Draw.h"

Draw::Draw(int window_x_begin, int window_x_end, int window_y_begin, int window_y_end) {
	this->window_x_begin = window_x_begin;
	this->window_x_end = window_x_end;
	this->window_y_begin = window_y_begin;
	this->window_y_end = window_y_end;
}
Draw::~Draw() {

}

void Draw::plot_triangles(std::map<long, Triangle>& triangles, std::string color) {
	for (auto it = triangles.begin(); it != triangles.end(); it++) {
		Point2D A = it->second.p1;
		Point2D B = it->second.p2;
		Point2D C = it->second.p3;
		std::vector<double> x1 = { A.x, B.x }; // AB边的x坐标
		std::vector<double> y1 = { A.y, B.y }; // AB边的y坐标

		std::vector<double> x2 = { B.x, C.x }; // BC边的x坐标
		std::vector<double> y2 = { B.y, C.y }; // BC边的y坐标

		std::vector<double> x3 = { C.x, A.x }; // CA边的x坐标
		std::vector<double> y3 = { C.y, A.y }; // CA边的y坐标

		// 绘制三条边
		plt::plot(x1, y1, color); // 蓝色实线表示边
		plt::plot(x2, y2, color);
		plt::plot(x3, y3, color);
	}

}
void Draw::plot_triangles(std::vector<Triangle>& triangles, std::string color) {
	for (auto it : triangles) {
		Point2D A = it.p1;
		Point2D B = it.p2;
		Point2D C = it.p3;
		std::vector<double> x1 = { A.x, B.x }; // AB边的x坐标
		std::vector<double> y1 = { A.y, B.y }; // AB边的y坐标

		std::vector<double> x2 = { B.x, C.x }; // BC边的x坐标
		std::vector<double> y2 = { B.y, C.y }; // BC边的y坐标

		std::vector<double> x3 = { C.x, A.x }; // CA边的x坐标
		std::vector<double> y3 = { C.y, A.y }; // CA边的y坐标

		// 绘制三条边
		plt::plot(x1, y1, color); // 蓝色实线表示边
		plt::plot(x2, y2, color);
		plt::plot(x3, y3, color);
	}
}

void Draw::plot_point(Point2D& p) {
	plt::plot({ p.x }, { p.y }, "ro");
}
void Draw::plot_segment(Segment& s) {
	double x1 = s.p1.x;
	double y1 = s.p1.y;
	double x2 = s.p2.x;
	double y2 = s.p2.y;
	// 绘制每条线段
	plt::plot({ x1, x2 }, { y1, y2 }, "b-"); 
}

void Draw::plot_triangle(Triangle& triangle) {
	Point2D A = triangle.p1;
	Point2D B = triangle.p2;
	Point2D C = triangle.p3;
	std::vector<double> x1 = { A.x, B.x }; // AB边的x坐标
	std::vector<double> y1 = { A.y, B.y }; // AB边的y坐标

	std::vector<double> x2 = { B.x, C.x }; // BC边的x坐标
	std::vector<double> y2 = { B.y, C.y }; // BC边的y坐标

	std::vector<double> x3 = { C.x, A.x }; // CA边的x坐标
	std::vector<double> y3 = { C.y, A.y }; // CA边的y坐标

	// 绘制三条边
	plt::plot(x1, y1, "g-"); // 蓝色实线表示边
	plt::plot(x2, y2, "g-");
	plt::plot(x3, y3, "g-");
	
}
void Draw::plot_show() {
	//// 设置图的范围（可选）
	//plt::xlim(this->window_x_begin, this->window_x_end);  // 设置 x 轴范围
	//plt::ylim(this->window_y_begin, this->window_y_end);  // 设置 y 轴范围
	//// 显示绘图
	//plt::show();


	// 设置图形显示
	plt::axis("equal"); // 保持x和y轴的比例相同
	plt::show();
}
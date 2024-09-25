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
		std::vector<double> x1 = { A.x, B.x }; // AB�ߵ�x����
		std::vector<double> y1 = { A.y, B.y }; // AB�ߵ�y����

		std::vector<double> x2 = { B.x, C.x }; // BC�ߵ�x����
		std::vector<double> y2 = { B.y, C.y }; // BC�ߵ�y����

		std::vector<double> x3 = { C.x, A.x }; // CA�ߵ�x����
		std::vector<double> y3 = { C.y, A.y }; // CA�ߵ�y����

		// ����������
		plt::plot(x1, y1, color); // ��ɫʵ�߱�ʾ��
		plt::plot(x2, y2, color);
		plt::plot(x3, y3, color);
	}

}
void Draw::plot_triangles(std::vector<Triangle>& triangles, std::string color) {
	for (auto it : triangles) {
		Point2D A = it.p1;
		Point2D B = it.p2;
		Point2D C = it.p3;
		std::vector<double> x1 = { A.x, B.x }; // AB�ߵ�x����
		std::vector<double> y1 = { A.y, B.y }; // AB�ߵ�y����

		std::vector<double> x2 = { B.x, C.x }; // BC�ߵ�x����
		std::vector<double> y2 = { B.y, C.y }; // BC�ߵ�y����

		std::vector<double> x3 = { C.x, A.x }; // CA�ߵ�x����
		std::vector<double> y3 = { C.y, A.y }; // CA�ߵ�y����

		// ����������
		plt::plot(x1, y1, color); // ��ɫʵ�߱�ʾ��
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
	// ����ÿ���߶�
	plt::plot({ x1, x2 }, { y1, y2 }, "b-"); 
}

void Draw::plot_triangle(Triangle& triangle) {
	Point2D A = triangle.p1;
	Point2D B = triangle.p2;
	Point2D C = triangle.p3;
	std::vector<double> x1 = { A.x, B.x }; // AB�ߵ�x����
	std::vector<double> y1 = { A.y, B.y }; // AB�ߵ�y����

	std::vector<double> x2 = { B.x, C.x }; // BC�ߵ�x����
	std::vector<double> y2 = { B.y, C.y }; // BC�ߵ�y����

	std::vector<double> x3 = { C.x, A.x }; // CA�ߵ�x����
	std::vector<double> y3 = { C.y, A.y }; // CA�ߵ�y����

	// ����������
	plt::plot(x1, y1, "g-"); // ��ɫʵ�߱�ʾ��
	plt::plot(x2, y2, "g-");
	plt::plot(x3, y3, "g-");
	
}
void Draw::plot_show() {
	//// ����ͼ�ķ�Χ����ѡ��
	//plt::xlim(this->window_x_begin, this->window_x_end);  // ���� x �᷶Χ
	//plt::ylim(this->window_y_begin, this->window_y_end);  // ���� y �᷶Χ
	//// ��ʾ��ͼ
	//plt::show();


	// ����ͼ����ʾ
	plt::axis("equal"); // ����x��y��ı�����ͬ
	plt::show();
}
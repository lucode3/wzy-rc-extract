#include"Triangle.h"

Triangle::Triangle() {

}

Triangle& Triangle::operator=(const Triangle& other) {
	this->id = other.id;
	this->p1 = other.p1;
	this->p2 = other.p2;
	this->p3 = other.p3;
	this->circum_center = other.circum_center;
	this->circum_r = circum_r;
	return *this;
}


Triangle::Triangle(long id, Point2D p1, Point2D p2, Point2D p3) : Entity(id) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	// 提取各个点的坐标
	double x1 = p1.x, y1 = p1.y;
	double x2 = p2.x, y2 = p2.y;
	double x3 = p3.x, y3 = p3.y;

	// 计算D（分母）
	double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

	//极端情况，三个点是共线的，此时设该特殊"三角形"的外接圆是圆心为原点且半径无穷大，这样使得后续它一定会被空洞算法合并掉
	if (D == 0) {
		return;
	}
	// 计算圆心的坐标（center.x, center.y）
	this->circum_center.x = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / D;
	this->circum_center.y = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / D;
	// 计算三角形的面积
	double area = 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
	// 计算三角形的边长
	double a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));  // BC
	double b = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));  // AC
	double c = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));  // AB
	// 计算外接圆的半径
	this->circum_r = (a * b * c) / (4 * area);
	
	//计算三角形重心
	this->centroid.x = (p1.x + p2.x + p3.x) / 3.0;
	this->centroid.y = (p1.y + p2.y + p3.y) / 3.0;
	
	this->R_L_min = circum_r / std::min(std::min(a, b), c);
}



Triangle::~Triangle() {

}
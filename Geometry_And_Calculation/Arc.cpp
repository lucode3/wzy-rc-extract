#include"Arc.h"

Arc::Arc() {

}

Arc::Arc(Point2D A, Point2D B, Point2D O) {
	// 计算 A 和 B 相对于圆心 O 的角度
	this->A = A;
	this->B = B;
	this->O = O;
	double theta_A = atan2(A.y - O.y, A.x - O.x);
	double theta_B = atan2(B.y - O.y, B.x - O.x);
	// 计算顺时针角度
	if (theta_B < theta_A) {
		theta_B += 2 * 3.1415926; // 添加 2π
	}
	// 计算中间角度
	double theta_M = (theta_A + theta_B) / 2.0;
	// 计算半径
	double ra = sqrt(pow(A.x - O.x, 2) + pow(A.y - O.y, 2));
	// 计算中点坐标
	this->M.x = O.x + ra * cos(theta_M);
	this->M.y = O.y + ra * sin(theta_M);
	this->r = std::sqrt(std::pow(A.x - M.x, 2) + std::pow(A.y - M.y, 2));

}
Arc& Arc::operator=(const Arc& other) {
	this->A = other.A;
	this->B = other.B;
	this->O = other.O;
	this->M = other.M;
	this->r = other.r;
	return *this;
}
bool Arc::operator<(const Arc& other) const {
	if (this->O == other.O) {
		if (this->A == other.A) {
			return this->B < other.B;
		}
		else {
			return this->A < other.A;
		}
	}
	else {
		return this->O < other.O;
	}
}

bool Arc::operator==(const Arc& other) const {
	if (this->A == other.A && this->B == other.B && this->O == other.O)
		return true;
	else
		return false;
}
Arc::~Arc() {

}
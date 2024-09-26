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
	// ��ȡ�����������
	double x1 = p1.x, y1 = p1.y;
	double x2 = p2.x, y2 = p2.y;
	double x3 = p3.x, y3 = p3.y;

	// ����D����ĸ��
	double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

	//����������������ǹ��ߵģ���ʱ�������"������"�����Բ��Բ��Ϊԭ���Ұ뾶���������ʹ�ú�����һ���ᱻ�ն��㷨�ϲ���
	if (D == 0) {
		return;
	}
	// ����Բ�ĵ����꣨center.x, center.y��
	this->circum_center.x = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / D;
	this->circum_center.y = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / D;
	// ���������ε����
	double area = 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
	// ���������εı߳�
	double a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));  // BC
	double b = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));  // AC
	double c = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));  // AB
	// �������Բ�İ뾶
	this->circum_r = (a * b * c) / (4 * area);
	
	//��������������
	this->centroid.x = (p1.x + p2.x + p3.x) / 3.0;
	this->centroid.y = (p1.y + p2.y + p3.y) / 3.0;
	
	this->R_L_min = circum_r / std::min(std::min(a, b), c);
}



Triangle::~Triangle() {

}
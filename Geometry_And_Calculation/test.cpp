#include<iostream>
#include<vector>
#include"DelaunayMesh2D.h"
#include"Point2D.h"
#include"Segment.h"


#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

// �����ά��Ľṹ��
struct Point {
	double x, y;
};

// �жϵ��Ƿ����߶ε���ࣨ�������߷���
bool isLeft(Point p1, Point p2, Point p) {
	return ((p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y)) > 0;
}

// ʹ�����߷��жϵ��Ƿ��ڶ�����ڲ�
bool isInsidePolygon(Point polygon[], int n, Point p) {
	bool inside = false;
	for (int i = 0, j = n - 1; i < n; j = i++) {
		if (((polygon[i].y > p.y) != (polygon[j].y > p.y)) &&
			(p.x < (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)) {
			inside = !inside;
		}
	}
	return inside;
}

// �ڶ�����ڲ����������
Point generateRandomPoint(Point polygon[], int n) {
	double minX = polygon[0].x, maxX = polygon[0].x;
	double minY = polygon[0].y, maxY = polygon[0].y;

	// �ҵ�����εı߽緶Χ
	for (int i = 1; i < n; ++i) {
		if (polygon[i].x < minX) minX = polygon[i].x;
		if (polygon[i].x > maxX) maxX = polygon[i].x;
		if (polygon[i].y < minY) minY = polygon[i].y;
		if (polygon[i].y > maxY) maxY = polygon[i].y;
	}

	Point randomPoint;
	do {
		// �����ڱ߽緶Χ�ڵ������
		randomPoint.x = minX + static_cast<double>(rand()) / RAND_MAX * (maxX - minX);
		randomPoint.y = minY + static_cast<double>(rand()) / RAND_MAX * (maxY - minY);
	} while (!isInsidePolygon(polygon, n, randomPoint));

	return randomPoint;
}

// ���ɶ������㲢��std::vector<std::vector<double>>����ʽ����
std::vector<std::vector<double>> generateRandomPoints(int numPoints) {
	// ����������ĸ�����
	Point polygon[] = { {0.0, 0.0}, {1.0, 1.0}, {1.0, 2.0}, {0.0, 2.0} };
	int n = sizeof(polygon) / sizeof(polygon[0]);

	std::vector<std::vector<double>> cps;  // ���ڴ洢���

	for (int i = 0; i < numPoints; ++i) {
		Point randomPoint = generateRandomPoint(polygon, n);
		cps.push_back({ randomPoint.x, randomPoint.y });
	}

	return cps;
}


int main() {
	//test case 1
	//std::vector<std::vector<double>> cps = { {2.5, 2.5}, {2.6, 2.6}, {2.0, 2.0}, {1.0, 1.0}};
	//std::vector<std::vector<double>> css = { {1.0, 1.0, 2.0, 2.0}, {1.0, 1.0, 3.0, 3.0}, {2.0, 2.0, 1.0, 1.0} ,
	//									{1.5, 1.5, 1.0, 2.5}, {1.0, 2.0, 3.0, 2.5},{6.0, 6.0, 8.0, 8.0},{1.0, 6.0, 3.0, 8.0},
	//									{2.0, 8.0, 2.6, 0.0} };

	//test case 2
	std::vector<std::vector<double>> cps = { {0.6, 0.7},{0.24 ,1.0},{0.18 ,1.23},{0.46 ,1.83},{0.32, 0.7} ,{0.16, 0.5},{0.0, 0.4},{0.0, 0.8} };
	
	//srand(time(0));  // �����������
	//std::vector<std::vector<double>> cps = generateRandomPoints(2);
	std::vector<std::vector<double>> css = { {0.0, 0.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 2.0}, {1.0, 2.0, 0.0, 2.0} ,{0.0, 2.0, 0.0, 0.0},
										  {1.0, 1.0, 0.51, 1.5}, {0.6, 1.0, 0.7, 1.86},{0.0, 1.64, 1.0, 1.73} };
	
	
	auto start = std::chrono::high_resolution_clock::now();
	DelaunayMesh2D mesh(0, 10, 0, 10);

	mesh.contraint_normalize(cps, css);

	//########### contraint_normalize result ###########
	for (auto it = mesh.constraint_segments.begin(); it != mesh.constraint_segments.end(); it++) {
		mesh.drawer->plot_segment(it->second);
	}
	for (auto it = mesh.constraint_points.begin(); it != mesh.constraint_points.end(); it++) {
		mesh.drawer->plot_point(it->second);
	}
	mesh.drawer->plot_show();


	mesh.boundary_subdivision();

	//########### boundary_subdivision result ###########
	mesh.drawer->plot_triangles(mesh.triangles, "k-");
	for (auto it : mesh.css) {
		if (mesh.es_segments.find(it) == mesh.es_segments.end()) {
			mesh.drawer->plot_segment(it);
		}
	}
	//for (auto it = mesh.constraint_points.begin(); it != mesh.constraint_points.end(); it++) {
	//	mesh.drawer->plot_point(it->second);
	//}
	mesh.drawer->plot_show();



	// ��¼����ʱ��
	auto end = std::chrono::high_resolution_clock::now();

	// ��������ʱ�䣬��λΪ΢��
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	// �������ʱ��
	std::cout << "Execution time: " << duration << " microseconds" << std::endl;
	//std::cout << mesh.es_segments.size() << std::endl;

}
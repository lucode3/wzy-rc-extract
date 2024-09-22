#include<iostream>
#include<vector>
#include"DelaunayMesh2D.h"
#include"Point2D.h"
#include"Segment.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main() {
	std::vector<std::vector<double>> cps = { {2.5, 2.5}, {2.6, 2.6}, {2.0, 2.0}, {1.0, 1.0}};
	//std::vector<std::vector<double>> css = { {1.0, 1.0, 2.0, 2.0}, {1.0, 1.0, 3.0, 3.0}, {2.0, 2.0, 1.0, 1.0} ,
	//										{1.5, 1.5, 1.0, 2.5} };
	std::vector<std::vector<double>> css = { {1.0, 1.0, 2.0, 2.0}, {1.0, 1.0, 3.0, 3.0}, {2.0, 2.0, 1.0, 1.0} ,
										{1.5, 1.5, 1.0, 2.5}, {1.0, 2.0, 3.0, 2.5},{6.0, 6.0, 8.0, 8.0},{1.0, 6.0, 3.0, 8.0},
										{2.0, 8.0, 2.6, 0.0} };
	clock_t start = clock();
	DelaunayMesh2D mesh(0, 10, 0, 10);
	mesh.contraint_normalize(cps, css);
	clock_t end = clock();
	double time_taken = (double)(end- start) / CLOCKS_PER_SEC;
	std::cout << time_taken << "s\n";

}
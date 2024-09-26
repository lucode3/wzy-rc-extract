//��vs 2017��C++��Ŀ��ʹ��matplotlibcpp����pythonһ����ͼ��ָ��

//�ٰ�װpython�汾��Ҫ��64λ�汾����Ӧvs��Release x64ģʽ

//��vs����ҳ��1.  C/C++ -> ���� -> ���Ӱ���Ŀ¼ : ���python��includeĿ¼
//			  2.  ������ -> ���� -> ���ӿ�Ŀ¼ : ���python��libsĿ¼
//            3.  ������ -> ���� -> ���������� : ���python.lib�ļ�(����python36.lib��Ӧ�ô�����libsĿ¼��)

//�۰�python.dll�ļ�����һ�ݵ�C�̵�windowsĿ¼��

//�����python�����ú���Ҫpip install matplotlib���ģ��

//��github����matplotlibcpp���������Ŀ�㵽����

//��vs����ҳ��1.  C/C++ -> ���� -> ���Ӱ���Ŀ¼ : ���matplotlibcpp��Ŀ��matplotlibcpp.h���ڵ�Ŀ¼

//��matplotlibcpp.h�е��������д���Ҫע�͵�(340�����ҵ�λ��)��ע: �п��ܲ���ע��������������б������Գ��������
//template <> struct select_npy_type<long long> { const static NPY_TYPES type = NPY_INT64; };
//template <> struct select_npy_type<unsigned long long> { const static NPY_TYPES type = NPY_UINT64; };

//��vs����ҳ��1.  C/C++ -> ���� -> C++���Ա�׼ : ѡ��C++17

//��������ϲ���󣬾Ϳ���#include"matplotlibcpp.h" ,ʹ���书������ͼ��

#pragma once
#include<unordered_set>
#include<unordered_map>
#include<string>
#include"Point2D.h"
#include"Segment.h"
#include"Triangle.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

class Draw {
public:
	Draw(int window_x_begin, int window_x_end, int window_y_begin, int window_y_end);
	~Draw();
	void plot_triangles(std::map<long, Triangle>& triangles, std::string color);
	void plot_triangles(std::vector<Triangle>& triangles, std::string color);
	void plot_triangle(Triangle& triangle);
	void plot_point(Point2D& p);
	void plot_segment(Segment& s);
	void plot_cir(Point2D& center, double r);
	void plot_show();
public:
	int window_x_begin;
	int window_x_end;
	int window_y_begin;
	int window_y_end;
};



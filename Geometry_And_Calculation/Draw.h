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
#include"Point2D.h"
#include"Segment.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

class Draw {
public:
	Draw(int window_x_begin, int window_x_end, int window_y_begin, int window_y_end);
	~Draw();
	void plot_points_and_segments(std::unordered_set<Point2D>& points, std::unordered_set<Segment>& segments);
	void plot_points_and_segments(std::unordered_map<long, Point2D>& points, std::unordered_map<long, Segment>& segments);
public:
	int window_x_begin;
	int window_x_end;
	int window_y_begin;
	int window_y_end;
};



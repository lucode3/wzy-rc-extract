//在vs 2017的C++项目中使用matplotlibcpp来像python一样画图的指南

//①安装python版本需要是64位版本，对应vs的Release x64模式

//②vs属性页中1.  C/C++ -> 常规 -> 附加包含目录 : 添加python的include目录
//			  2.  链接器 -> 常规 -> 附加库目录 : 添加python的libs目录
//            3.  链接器 -> 输入 -> 附加依赖项 : 添加python.lib文件(例如python36.lib，应该存在与libs目录下)

//③把python.dll文件拷贝一份到C盘的windows目录下

//④完成python的配置后，需要pip install matplotlib这个模块

//⑤github上搜matplotlibcpp，把这个项目搞到本地

//⑥vs属性页中1.  C/C++ -> 常规 -> 附加包含目录 : 添加matplotlibcpp项目中matplotlibcpp.h所在的目录

//⑦matplotlibcpp.h中的下面两行代码要注释掉(340行左右的位置)，注: 有可能不用注掉，但如果运行有报错，可以尝试这个。
//template <> struct select_npy_type<long long> { const static NPY_TYPES type = NPY_INT64; };
//template <> struct select_npy_type<unsigned long long> { const static NPY_TYPES type = NPY_UINT64; };

//⑧vs属性页中1.  C/C++ -> 语言 -> C++语言标准 : 选择C++17

//⑨完成以上步骤后，就可以#include"matplotlibcpp.h" ,使用其功能来绘图了

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



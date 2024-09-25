#include"DelaunayMesh2D.h"

DelaunayMesh2D::DelaunayMesh2D(int window_x_begin, int window_x_end, int window_y_begin, int window_y_end) {
	drawer = new Draw(window_x_begin, window_x_end, window_y_begin, window_y_end);
}

DelaunayMesh2D::~DelaunayMesh2D() {
	delete drawer;
}

//计算AB与AC的叉积，从而判断C与AB的位置关系
double DelaunayMesh2D::cross(const Point2D& a, const Point2D& b, const Point2D& c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double DelaunayMesh2D::calculate_angle(const Point2D& A, const Point2D& B, const Point2D& C) {
	// 计算向量AB和AC
	double BAx = B.x - A.x;
	double BAy = B.y - A.y;
	double CAx = C.x - A.x;
	double CAy = C.y - A.y;
	double dot_product = BAx * CAx + BAy * CAy;
	double BA_length = sqrt(BAx * BAx + BAy * BAy);
	double CA_length = sqrt(CAx * CAx + CAy * CAy);
	if (BA_length == 0 || CA_length == 0) {
		return -2.0; // 返回-1表示角度无法定义
	}
	double cos_theta = dot_product / (BA_length * CA_length);
	return cos_theta;
}

Point2D DelaunayMesh2D::find_line_circle_intersection(Point2D& A, Point2D& B, double r) {
	double dis_x = B.x - A.x;
	double dis_y = B.y - A.y;
	if (dis_x == 0.0) {
		if (dis_y > 0) {
			Point2D intersection(A.x, A.y + r);
			return intersection;
		}
		else {
			Point2D intersection(A.x, A.y - r);
			return intersection;
		}
	}
	double k = dis_y / dis_x;
	double delt_x;
	double delt_y;
	if (dis_x < 0)
		delt_x = - r / std::sqrt(k * k + 1);
	else
		delt_x = r / std::sqrt(k * k + 1);
	delt_y = k * delt_x;
	Point2D intersection(A.x + delt_x, A.y + delt_y);
	return intersection;
}

void DelaunayMesh2D::contraint_normalize(std::vector<std::vector<double>>& cps, std::vector<std::vector<double>>& css) {
	std::unordered_set<Point2D> points;
	std::unordered_set<Segment> segments;

	//处理重复线段与存储端点到限制点集中

	for (int i = 0; i < css.size(); i++) {
		Point2D p1(css[i][0], css[i][1]);
		Point2D p2(css[i][2], css[i][3]);
		points.insert(p1);
		points.insert(p2);
		Segment s(p1, p2);
		segments.insert(s);
	}

	//处理线段之间的共线问题

	std::unordered_map<double, std::vector<Segment>> k_map;
	for (auto& segment : segments) {
		double k;
		if (segment.p2.x == segment.p1.x) {
			k = std::numeric_limits<double>::max(); // 用特殊值表示垂直线段
		}
		else {
			k = (segment.p2.y - segment.p1.y) / (segment.p2.x - segment.p1.x);
		}
		if (k_map.find(k) != k_map.end()) {
			k_map[k].push_back(segment);
		}
		else {
			std::vector<Segment> temp;
			temp.push_back(segment);
			k_map.insert(std::make_pair(k, temp));
		}
	}

	for (auto it = k_map.begin(); it != k_map.end(); it++) {
		if (it->second.size() == 1)
			continue;
		FindUnionSet fu_set(it->second.size());
		for (int i = 0; i < it->second.size(); i++) {
			for (int j = i + 1; j < it->second.size(); j++) {
				if (fu_set.is_same(i, j))
					continue;
				Segment s1 = it->second[i];
				Segment s2 = it->second[j];
				if (s2.p1.y - s1.p1.y == it->first * (s2.p1.x - s1.p1.x) && std::max(s1.p1.x, s2.p1.x) <= std::min(s1.p2.x, s2.p2.x)) {
					fu_set.union_set(i, j);
				}
			}
		}
		std::unordered_map<int, std::vector<int>> parts = fu_set.get_all_parts();
		for (auto part = parts.begin(); part != parts.end(); part++) {
			if (part->second.size() < 2)
				continue;
			Segment segment_cur = it->second[part->second[0]];
			Point2D max_x_point = segment_cur.p2;
			Point2D min_x_point = segment_cur.p1;
			points.erase(max_x_point);
			points.erase(min_x_point);
			segments.erase(segment_cur);
			for (int i = 1; i < part->second.size(); i++) {
				Segment segment_cur = it->second[part->second[i]];
				Point2D max_cur = segment_cur.p2;
				Point2D min_cur = segment_cur.p1;
				if (max_cur.x > max_x_point.x) {
					max_x_point = max_cur;
				}
				if (min_cur.x < min_x_point.x) {
					min_x_point = min_cur;
				}
				points.erase(max_cur);
				points.erase(min_cur);
				segments.erase(segment_cur);
			}
			points.insert(min_x_point);
			points.insert(max_x_point);
			Segment merge_segment(min_x_point, max_x_point);
			segments.insert(merge_segment);
		}
	}

	//处理线段之间的相交问题
	std::unordered_set<Segment> new_segments;
	std::unordered_set<Segment> erase_segments;
	std::unordered_set<std::pair<Segment, Segment>> done_pairs;
	bool iteration = true;
	while (iteration) {
		iteration = false;
		for (auto& segment1 : segments) {
			if (erase_segments.find(segment1) != erase_segments.end())
				continue;
			for (auto& segment2 : segments) {
				if (erase_segments.find(segment1) != erase_segments.end())
					break;
				if (done_pairs.find(std::make_pair(segment1, segment2)) != done_pairs.end())
					continue;
				if (erase_segments.find(segment2) != erase_segments.end())
					continue;
				if (segment1 == segment2)
					continue;
				double d1 = cross(segment1.p1, segment1.p2, segment2.p1);
				double d2 = cross(segment1.p1, segment1.p2, segment2.p2);
				double d3 = cross(segment2.p1, segment2.p2, segment1.p1);
				double d4 = cross(segment2.p1, segment2.p2, segment1.p2);

				if (std::abs(d1) < 1e-10 && segment2.p1.x > segment1.p1.x && segment2.p1.x < segment1.p2.x) { //segment2.p1在segment1上
					Segment new_segment11(segment1.p1, segment2.p1);
					Segment new_segment12(segment1.p2, segment2.p1);
					new_segments.insert(new_segment11);
					new_segments.insert(new_segment12);
					erase_segments.insert(segment1);
					continue;
				}else if (std::abs(d2) < 1e-10 && segment2.p2.x > segment1.p1.x && segment2.p2.x < segment1.p2.x) {//segment2.p2在segment1上
					Segment new_segment11(segment1.p1, segment2.p2);
					Segment new_segment12(segment1.p2, segment2.p2);
					new_segments.insert(new_segment11);
					new_segments.insert(new_segment12);
					erase_segments.insert(segment1);
					continue;
				}else if (std::abs(d3) < 1e-10 && segment1.p1.x > segment2.p1.x && segment1.p1.x < segment2.p2.x) { //segment1.p1在segment2上
					Segment new_segment21(segment2.p1, segment1.p1);
					Segment new_segment22(segment2.p2, segment1.p1);
					new_segments.insert(new_segment21);
					new_segments.insert(new_segment22);
					erase_segments.insert(segment2);
					continue;
				}else if (std::abs(d4) < 1e-10 && segment1.p2.x > segment2.p1.x && segment1.p2.x < segment2.p2.x) { //segment1.p2在segment2上
					Segment new_segment21(segment2.p1, segment1.p2);
					Segment new_segment22(segment2.p2, segment1.p2);
					new_segments.insert(new_segment21);
					new_segments.insert(new_segment22);
					erase_segments.insert(segment2);
					continue;
				}else if (d1*d2 < 0 && d3*d4 < 0) {//标准相交
					double t = std::abs(d1) / (std::abs(d1) + std::abs(d2));
					Point2D intersection(segment2.p1.x + t * (segment2.p2.x - segment2.p1.x), segment2.p1.y + t * (segment2.p2.y - segment2.p1.y));
					Segment new_segment11(segment1.p1, intersection);
					Segment new_segment12(segment1.p2, intersection);
					Segment new_segment21(segment2.p1, intersection);
					Segment new_segment22(segment2.p2, intersection);
					new_segments.insert(new_segment11);
					new_segments.insert(new_segment12);
					new_segments.insert(new_segment21);
					new_segments.insert(new_segment22);
					erase_segments.insert(segment1);
					erase_segments.insert(segment2);
					points.insert(intersection);
					continue;
				}
			
				done_pairs.insert(std::make_pair(segment1, segment2));
				done_pairs.insert(std::make_pair(segment2, segment1));
			}
		}
		if (new_segments.size() > 0) {
			iteration = true;
			for (auto& new_segment : new_segments) {
				segments.insert(new_segment);
			}
			for (auto& erase_segment : erase_segments) {
				segments.erase(erase_segment);
			}
			new_segments.clear();
			erase_segments.clear();
		}
	}


	//处理限制点集和原本限制边集中端点的插入
	for (int i = 0; i < cps.size(); i++) {
		Point2D p(cps[i][0], cps[i][1]);
		points.insert(p);
	}

	iteration = true;
	std::unordered_set<Point2D> done_points;
	while (iteration) {
		iteration = false;
		for (auto& point : points) {
			if (done_points.find(point) != done_points.end())
				continue;
			for (auto& segment : segments) {
				if (erase_segments.find(segment) != erase_segments.end())
					continue;
				double d = cross(segment.p1, segment.p2, point);
				if (std::abs(d) < 5e-10 && (point.x > segment.p1.x && point.x < segment.p2.x || point.y > segment.p1.y && point.y < segment.p2.y)) {
					Segment new_segment1(segment.p1, point);
					Segment new_segment2(segment.p2, point);
					new_segments.insert(new_segment1);
					new_segments.insert(new_segment2);
					erase_segments.insert(segment);
					done_points.insert(point);
					break;
				}
			}
		}
		if (new_segments.size() > 0) {
			iteration = true;
			for (auto& new_segment : new_segments) {
				segments.insert(new_segment);
			}
			for (auto& erase_segment : erase_segments) {
				segments.erase(erase_segment);
			}
			new_segments.clear();
			erase_segments.clear();
		}
	}

	//控制圆预处理，确保边界细分算法收敛
	control_circle_segmentation(points, segments);

	//对限定点集合和限定边集合进行编号
	std::unordered_map<Point2D, long> point_id;
	for (auto& point : points) {
		Point2D p(this->point_id_count, point.x, point.y);
		this->constraint_points.insert({ this->point_id_count, p });
		point_id.insert({ p, this->point_id_count });
		this->point_id_count += 1;
	}

	for (auto& segment : segments) {
		Point2D p1(point_id[segment.p1], segment.p1.x, segment.p1.y);
		Point2D p2(point_id[segment.p2], segment.p2.x, segment.p2.y);
		Segment s(segment_id_count, p1, p2);
		this->constraint_segments.insert({ segment_id_count, s });
		segment_id_count += 1;
	}

	this->css = segments;
	
}

double DelaunayMesh2D::local_feature_size(Point2D& CP, std::unordered_set<Point2D>& points, std::unordered_set<Segment>& segments) {
	double min_size = std::numeric_limits<double>::max();
	for (auto& point : points) {
		if (CP == point)
			continue;
		double cur_size = std::sqrt((CP.x - point.x) * (CP.x - point.x) + (CP.y - point.y) * (CP.y - point.y));
		if (cur_size > 0.0 && cur_size < min_size)
			min_size = cur_size;
	}
	for (auto& segment : segments) {
		if (CP == segment.p1 || CP == segment.p2)
			continue;
		double cur_size = point_to_segment_distance(CP, segment.p1, segment.p2);
		if(cur_size > 0.0 && cur_size < min_size)
			min_size = cur_size;
	}
	return min_size;
}

void DelaunayMesh2D::control_circle_segmentation(std::unordered_set<Point2D>& points, std::unordered_set<Segment>& segments) {
	std::map<Point2D, std::vector<Segment>> relative_segments;
	for (auto& segment : segments) {
		if (relative_segments.find(segment.p1) != relative_segments.end()) {
			relative_segments[segment.p1].push_back(segment);
		}
		else {
			std::vector<Segment> temp;
			temp.push_back(segment);
			relative_segments.insert({ segment.p1, temp });
		}
		if (relative_segments.find(segment.p2) != relative_segments.end()) {
			relative_segments[segment.p2].push_back(segment);
		}
		else {
			std::vector<Segment> temp;
			temp.push_back(segment);
			relative_segments.insert({ segment.p2, temp });
		}
	}

	for (auto it = relative_segments.begin(); it != relative_segments.end(); it++) {
		if (it->second.size() < 2)
			continue;
		Point2D A = it->first;
		bool segmentaion = false;
		for (int i = 0; i < it->second.size(); i++) {
			for (int j = i + 1; j < it->second.size(); j++) {
				Point2D B;
				Point2D C;
				if (it->second[i].p1 == A)
					B = it->second[i].p2;
				else
					B = it->second[i].p1;
				if (it->second[j].p1 == A)
					C = it->second[j].p2;
				else
					C = it->second[j].p1;
				double cos = calculate_angle(A, B, C);
				if (cos > 0.5) {
					segmentaion = true;
					break;
				}
			}
			if (segmentaion)
				break;
		}
		if (segmentaion) {
			double lfs = local_feature_size(A, points, segments);
			lfs /= 3.1;
			for (int i = 0; i < it->second.size(); i++) {
				Segment BC = it->second[i];
				Point2D other;
				if (it->second[i].p1 == A)
					other = BC.p2;
				else
					other = BC.p1;

				Point2D intersection = find_line_circle_intersection(A, other, lfs);

				Segment B_intersection(BC.p1, intersection);
				Segment C_intersection(BC.p2, intersection);
				segments.erase(BC);
				segments.insert(B_intersection);
				segments.insert(C_intersection);
				points.insert(intersection);
				for (int i = 0; i < relative_segments[other].size(); i++) {
					if (BC == relative_segments[other][i]) {
						Segment other_intersection(other, intersection);
						relative_segments[other][i] = other_intersection;
						break;
					}
				}
			}
		}
	}
}

bool DelaunayMesh2D::in_circum(Triangle& t, Point2D& p) {
	double delt_x = p.x - t.circum_center.x;
	double delt_y = p.y - t.circum_center.y;
	double distance = std::sqrt(delt_x * delt_x + delt_y * delt_y);
	if (distance <= t.circum_r)
		return true;
	else
		return false;
}

bool DelaunayMesh2D::in_triangle(Triangle& t, Point2D& P) {
	Point2D A = t.p1;
	Point2D B = t.p2;
	Point2D C = t.p3;
	double cross1 = cross(A, B, P);
	double cross2 = cross(B, C, P);
	double cross3 = cross(C, A, P);

	return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) ||
		(cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
}

long DelaunayMesh2D::get_es_triangle(Segment& s, long cur) {
	if (this->es_segments[s].size() == 1)
		return -1;
	if (this->es_segments[s][0] == cur)
		return this->es_segments[s][1];
	else
		return this->es_segments[s][0];
}

//实现删除一个三角形的功能，同步triangles和es_segment的相关处理
void DelaunayMesh2D::del_triangle(Triangle& t) {
	this->triangles.erase(t.id);
	Segment s1(t.p1, t.p2);
	Segment s2(t.p2, t.p3);
	Segment s3(t.p3, t.p1);
	if (this->es_segments[s1][0] == t.id) {
		this->es_segments[s1][0] = this->es_segments[s1][1];
		this->es_segments[s1].pop_back();
	}
	else {
		this->es_segments[s1].pop_back();
	}
	if (this->es_segments[s1].size() == 0) {
		this->es_segments.erase(s1);
		if(this->css.find(s1) != this->css.end())
			this->subdivide_segments.push(s1);
	}

	if (this->es_segments[s2][0] == t.id) {
		this->es_segments[s2][0] = this->es_segments[s2][1];
		this->es_segments[s2].pop_back();
	}
	else {
		this->es_segments[s2].pop_back();
	}
	if (this->es_segments[s2].size() == 0) {
		this->es_segments.erase(s2);
		if (this->css.find(s2) != this->css.end())
			this->subdivide_segments.push(s2);
	}

	if (this->es_segments[s3][0] == t.id) {
		this->es_segments[s3][0] = this->es_segments[s3][1];
		this->es_segments[s3].pop_back();
	}
	else {
		this->es_segments[s3].pop_back();
	}
	if (this->es_segments[s3].size() == 0) {
		this->es_segments.erase(s3);
		if (this->css.find(s3) != this->css.end())
			this->subdivide_segments.push(s3);
	}
		
}

//实现新增一个三角形的功能，同步triangles和es_segment的相关处理
void DelaunayMesh2D::add_triangle(Triangle& t) {
	this->triangles.insert({ this->triangle_id_count, t });
	Segment s1(t.p1, t.p2);
	Segment s2(t.p2, t.p3);
	Segment s3(t.p3, t.p1);
	if (this->es_segments.find(s1) != this->es_segments.end()) {
		this->es_segments[s1].push_back(this->triangle_id_count);
	}
	else {
		this->es_segments.insert({ s1, {this->triangle_id_count} });
	}

	if (this->es_segments.find(s2) != this->es_segments.end()) {
		this->es_segments[s2].push_back(this->triangle_id_count);
	}
	else {
		this->es_segments.insert({ s2, {this->triangle_id_count} });
	}

	if (this->es_segments.find(s3) != this->es_segments.end()) {
		this->es_segments[s3].push_back(this->triangle_id_count);
	}
	else {
		this->es_segments.insert({ s3, {this->triangle_id_count} });
	}
	this->triangle_id_count += 1;

}

std::vector<Triangle> DelaunayMesh2D::get_cavity_triangles(Point2D& point) {
	long triangle_id = search_triangle_by_distance(point);
	Triangle cur_tri = triangles[triangle_id];
	std::vector<Triangle> cavity_triangles;
	cavity_triangles.push_back(cur_tri);
	Segment s1(cur_tri.p1, cur_tri.p2);
	Segment s2(cur_tri.p2, cur_tri.p3);
	Segment s3(cur_tri.p3, cur_tri.p1);
	long es_triangle_id1 = get_es_triangle(s1, triangle_id);
	long es_triangle_id2 = get_es_triangle(s2, triangle_id);
	long es_triangle_id3 = get_es_triangle(s3, triangle_id);

	if (es_triangle_id1 != -1) {
		Triangle es_triangle1 = this->triangles[es_triangle_id1];
		if (in_circum(es_triangle1, point) )
			cavity_triangles.push_back(es_triangle1);
	}
	if (es_triangle_id2 != -1) {
		Triangle es_triangle2 = this->triangles[es_triangle_id2];
		if (in_circum(es_triangle2, point))
			cavity_triangles.push_back(es_triangle2);
	}
	if (es_triangle_id3 != -1) {
		Triangle es_triangle3 = this->triangles[es_triangle_id3];
		if (in_circum(es_triangle3, point))
			cavity_triangles.push_back(es_triangle3);
	}
	return cavity_triangles;
}

long DelaunayMesh2D::search_triangle_by_distance(Point2D& point) {
	bool search_all = false;
	std::unordered_set<long> visit;
	long cur_id = this->triangles.begin()->first;
	while (true) {
		Triangle cur = triangles[cur_id];
		if (in_triangle(cur, point))
			break;
		Segment s1(cur.p1, cur.p2);
		Segment s2(cur.p2, cur.p3);
		Segment s3(cur.p3, cur.p1);
		long es_t1 = get_es_triangle(s1, cur.id);
		long es_t2 = get_es_triangle(s2, cur.id);
		long es_t3 = get_es_triangle(s3, cur.id);
		double dis1 = std::numeric_limits<double>::max();
		double dis2 = std::numeric_limits<double>::max();
		double dis3 = std::numeric_limits<double>::max();
		if (es_t1 != -1 && visit.count(es_t1) == 0)
			dis1 = std::pow(triangles[es_t1].centroid.x - point.x, 2) + std::pow(triangles[es_t1].centroid.y - point.y, 2);
		if (es_t2 != -1 && visit.count(es_t2) == 0)
			dis2 = std::pow(triangles[es_t2].centroid.x - point.x, 2) + std::pow(triangles[es_t2].centroid.y - point.y, 2);
		if (es_t3 != -1 && visit.count(es_t3) == 0)
			dis3 = std::pow(triangles[es_t3].centroid.x - point.x, 2) + std::pow(triangles[es_t3].centroid.y - point.y, 2);
		if (dis1 == std::numeric_limits<double>::max() && dis2 == std::numeric_limits<double>::max() && dis3 == std::numeric_limits<double>::max()) {
			search_all = true;
			visit.insert(cur_id);
			break;
		}
		if (dis1 < dis2 && dis1 < dis3) {
			cur_id = es_t1;
		}
		else if (dis2 < dis1 && dis2 < dis3) {
			cur_id = es_t2;
		}
		else {
			cur_id = es_t3;
		}
		visit.insert(cur_id);
	}
	if (search_all) {
		for (auto& it = this->triangles.begin(); it != this->triangles.end(); it++) {
			if (visit.count(it->first))
				continue;
			if (in_triangle(it->second, point)) {
				cur_id = it->first;
				break;
			}
		}
	}
	return cur_id;
}

long DelaunayMesh2D::search_triangle(Point2D& point) {
	long cur_id = -1;
	for (auto& it = this->triangles.begin(); it != this->triangles.end(); it++) {
		if (in_triangle(it->second, point)) {
			cur_id = it->first;
			break;
		}
	}
	return cur_id;
}

void DelaunayMesh2D::sort_cavity_points(std::vector<Point2D>& cavity_points, Point2D& center) {
	std::unordered_map<long, double> angle_map;
	for (auto& p : cavity_points) {
		double deltaX = p.x - center.x;
		double deltaY = p.y - center.y;
		// 计算角度（以弧度为单位）
		double angle = atan2(deltaY, deltaX);
		angle = angle * 57.2957795; // 转换为度数
		// 处理负角度，使其在0到360度之间
		if (angle < 0) {
			angle += 360.0;
		}
		angle_map.insert({ p.id, angle });
	}
	std::sort(cavity_points.begin(), cavity_points.end(), [&angle_map](const Point2D& a, const Point2D& b) {
		return angle_map[a.id] < angle_map[b.id];
	});
}

void DelaunayMesh2D::cavity(Point2D& point) {
	std::vector<Triangle> cavity_triangles = get_cavity_triangles(point);

	for (auto& t : cavity_triangles) {
		del_triangle(t);
	}
	std::unordered_set<Point2D> alreay_exsit;
	std::vector<Point2D> cavity_points;
	for (auto& tri : cavity_triangles) {
		if (alreay_exsit.find(tri.p1) == alreay_exsit.end()) {
			cavity_points.push_back(tri.p1);
			alreay_exsit.insert(tri.p1);
		}
		if (alreay_exsit.find(tri.p2) == alreay_exsit.end()) {
			cavity_points.push_back(tri.p2);
			alreay_exsit.insert(tri.p2);
		}
		if (alreay_exsit.find(tri.p3) == alreay_exsit.end()) {
			cavity_points.push_back(tri.p3);
			alreay_exsit.insert(tri.p3);
		}
	}
	sort_cavity_points(cavity_points, point);

	for (int i = 0; i < cavity_points.size(); i++) {
		Point2D A = cavity_points[i];
		Point2D B = cavity_points[(i + 1) % cavity_points.size()];

		if (std::fabs(cross(A, B, point)) == 0) {
			throw std::invalid_argument("Error: The three vertices that make up a triangle are collinear!");
		}
		Triangle tria(this->triangle_id_count, A, B, point);
		add_triangle(tria);
	}
}

Triangle DelaunayMesh2D::add_init_Triangle() {
	Point2D p1(this->point_id_count, -10, -1.0);
	this->point_id_count += 1;
	Point2D p2(this->point_id_count, 0.0, 10);
	this->point_id_count += 1;
	Point2D p3(this->point_id_count, 10.0, -1.0);
	this->point_id_count += 1;
	Triangle init_triangle(triangle_id_count, p1, p2, p3);
	this->triangles.insert({ this->triangle_id_count, init_triangle });
	Segment s1(p1, p2);
	Segment s2(p2, p3);
	Segment s3(p3, p1);
	this->es_segments.insert({ s1, {this->triangle_id_count} });
	this->es_segments.insert({ s2, {this->triangle_id_count} });
	this->es_segments.insert({ s3, {this->triangle_id_count} });

	triangle_id_count += 1;
	return init_triangle;
}

void DelaunayMesh2D::boundary_subdivision() {
	add_init_Triangle();

	for (auto it = this->constraint_points.begin(); it != this->constraint_points.end(); it++) {
		cavity(it->second);
	}

	for (auto& s : this->css) {
		if (this->es_segments.find(s) == this->es_segments.end())
			this->subdivide_segments.push(s);
	}

	while (!this->subdivide_segments.empty()) {
		Segment cur = this->subdivide_segments.front();
		this->subdivide_segments.pop();
		if (this->es_segments.find(cur) != this->es_segments.end())
			continue;
		Point2D A = cur.p1;
		Point2D B = cur.p2;
		Point2D mid_point(this->point_id_count,(B.x + A.x) / 2, (B.y + A.y) / 2);
		this->constraint_points.insert({ this->point_id_count , mid_point });
		this->point_id_count += 1;

		cavity(mid_point);

		this->css.erase(cur);
		Segment s1(A, mid_point);
		Segment s2(B, mid_point);
		this->subdivide_segments.push(s1);
		this->subdivide_segments.push(s2);
		this->css.insert(s1);
		this->css.insert(s2);
	}	
}

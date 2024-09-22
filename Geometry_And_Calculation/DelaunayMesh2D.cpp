#include"DelaunayMesh2D.h"

DelaunayMesh2D::DelaunayMesh2D(int window_x_begin, int window_x_end, int window_y_begin, int window_y_end) : Mesh() {
	drawer = new Draw(window_x_begin, window_x_end, window_y_begin, window_y_end);
}

DelaunayMesh2D::~DelaunayMesh2D() {
	delete drawer;
}


namespace std {
	template<>
	struct hash<Point2D> {
		size_t operator()(const Point2D& p) const {
			return hash<double>()(p.x) ^ hash<double>()(p.y);
		}
 	};
	template<>
	struct hash<Segment> {
		size_t operator()(const Segment& s) const {
			return std::hash<Point2D>()(s.p1) ^ std::hash<Point2D>()(s.p2);
		}
	};
	template<>
	struct hash<std::pair<Segment, Segment>> {
		std::size_t operator()(const std::pair<Segment, Segment>& p) const {
			hash<Segment> segmentHash;
			return segmentHash(p.first) ^ segmentHash(p.second);
		}
	};
}


//计算AB与AC的叉积，从而判断C与AB的位置关系
float DelaunayMesh2D::cross(const Point2D& a, const Point2D& b, const Point2D& c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
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
		int k;
		if (segment.p2.x == segment.p1.x) {
			k = std::numeric_limits<int>::max(); // 用特殊值表示垂直线段
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

				//标准相交
				if (d1*d2 < 0 && d3*d4 < 0) {
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
				else {
					//segment2.p1在segment1上
					if (std::abs(d1) < 5e-10 && segment2.p1.x > segment1.p1.x && segment2.p1.x < segment1.p2.x) {
						Segment new_segment11(segment1.p1, segment2.p1);
						Segment new_segment12(segment1.p2, segment2.p1);
						new_segments.insert(new_segment11);
						new_segments.insert(new_segment12);
						erase_segments.insert(segment1);
						continue;
					}
					//segment2.p2在segment1上
					if (std::abs(d2) < 5e-10 && segment2.p2.x > segment1.p1.x && segment2.p2.x < segment1.p2.x) {
						Segment new_segment11(segment1.p1, segment2.p2);
						Segment new_segment12(segment1.p2, segment2.p2);
						new_segments.insert(new_segment11);
						new_segments.insert(new_segment12);
						erase_segments.insert(segment1);
						continue;
					}
					//segment1.p1在segment2上
					if (std::abs(d3) < 5e-10 && segment1.p1.x > segment2.p1.x && segment1.p1.x < segment2.p2.x) {
						Segment new_segment21(segment2.p1, segment1.p1);
						Segment new_segment22(segment2.p2, segment1.p1);
						new_segments.insert(new_segment21);
						new_segments.insert(new_segment22);
						erase_segments.insert(segment2);
						continue;
					}
					//segment1.p2在segment2上
					if (std::abs(d4) < 5e-10 && segment1.p2.x > segment2.p1.x && segment1.p2.x < segment2.p2.x) {
						Segment new_segment21(segment2.p1, segment1.p2);
						Segment new_segment22(segment2.p2, segment1.p2);
						new_segments.insert(new_segment21);
						new_segments.insert(new_segment22);
						erase_segments.insert(segment2);
						continue;
					}
				}
				done_pairs.emplace(std::make_pair(segment1, segment2));
				done_pairs.emplace(std::make_pair(segment2, segment1));
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
				if (std::abs(d) < 5e-10 && point.x > segment.p1.x && point.x < segment.p2.x) {
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
	done_pairs.clear();
	done_points.clear();
	new_segments.clear();
	erase_segments.clear();

	long p_id_count = 0;
	long s_id_count = 0;
	std::unordered_map<Point2D, long> point_id;
	for (auto& point : points) {
		Point2D p(p_id_count, point.x, point.y);
		this->constraint_points.insert({ p_id_count, p });
		point_id.insert({ p, p_id_count });
		p_id_count += 1;
	}

	for (auto& segment : segments) {
		Point2D p1(point_id[segment.p1], segment.p1.x, segment.p1.y);
		Point2D p2(point_id[segment.p2], segment.p2.x, segment.p2.y);
		Segment s(s_id_count, p1, p2);
		this->constraint_segments.insert({ s_id_count, s });
		s_id_count += 1;
	}
	
	//drawer->plot_points_and_segments(this->constraint_points, this->constraint_segments);
	
}



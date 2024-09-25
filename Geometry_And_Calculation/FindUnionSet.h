#pragma once
#include<vector>
#include<unordered_map>

class FindUnionSet {
public:
	FindUnionSet(int node_num)
		: parents(std::vector<int>(node_num)), set_size(std::vector<int>(node_num, 0)) {
		for (int i = 0; i < parents.size(); i++) {
			parents[i] = i;
		}
	}
	~FindUnionSet(){}
	int find_parents(int node) {
		return node == parents[node] ? node : parents[node] = find_parents(parents[node]);
	}
	bool is_same(int node_1, int node_2) {
		if (find_parents(node_1) == find_parents(node_2))
			return true;
		else
			return false;
	}
	void union_set(int node_1, int node_2) {
		int parents_1 = find_parents(node_1);
		int parents_2 = find_parents(node_2);
		if (parents_1 == parents_2)
			return;
		if (set_size[parents_1] > set_size[parents_2]) {
			parents[parents_2] = parents_1;
			set_size[parents_1] += set_size[parents_2];
			set_size[parents_2] = 0;
		}
		else {
			parents[parents_1] = parents_2;
			set_size[parents_2] += set_size[parents_1];
			set_size[parents_1] = 0;
		}
	}
	std::unordered_map<int, std::vector<int>> get_all_parts() {
		std::unordered_map<int, std::vector<int>> res;
		for (int i = 0; i < set_size.size(); i++) {
			if (set_size[i] != 0) {
				std::vector<int> temp;
				res.insert({ i, temp });
			}
		}
		for (int i = 0; i < set_size.size(); i++) {
			res[find_parents(i)].push_back(i);
		}
		return res;
	}

public:
	std::vector<int> parents;
	std::vector<int> set_size;

};
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string.h>
using namespace std;

class VInfo {
public:
	int node, weight;

	bool operator < (const VInfo& v) const {
		if (weight != v.weight) { return weight > v.weight; }
		return node < v.node;
	}
};

int V, E;
vector<set<VInfo>> VVec(26);
int Dist_cur, Dist_max;
int visit_phy[26], visit_vir[26];


int Path_Exist(int _node) {		

	memset(visit_vir, 0, sizeof(visit_vir));
	queue <int> Que;
	Que.push(_node);

	while (Que.size() != 0)
	{
		int cur_node = Que.front();
		Que.pop();

		for (auto it = VVec.at(cur_node).begin(); it != VVec.at(cur_node).end(); it++) {

			if (it->node == 0) return 1;
			if (!(visit_phy[it->node]) && !(visit_vir[it->node])) {
				visit_vir[it->node] = 1;
				Que.push(it->node);
			}
		}
	}
	return 0;
}



void Search_Largest_Path(int cur_node, int weight) {
	set<VInfo> curset = VVec.at(cur_node);

	if (!cur_node && Dist_cur != 0) {	
		Dist_cur += weight;
		if (Dist_max == 0 || Dist_max < Dist_cur) { Dist_max = Dist_cur; }
		Dist_cur -= weight;	return;
	}

	int edges_remain = 0;
	for (int i = 0; i < 26; i++) {
		if (!visit_phy[i] && !VVec.at(i).empty() || i == 0)
			for (auto it = VVec.at(i).begin(); it != VVec.at(i).end(); it++) {
				if (!visit_phy[it->node] || it->node == 0) { edges_remain += it->weight; break; }
			}
	}
	if (Dist_cur + weight + edges_remain < Dist_max) { return; }


	Dist_cur += weight;
	visit_phy[cur_node] = 1;

	if (!Path_Exist(cur_node)) { Dist_cur -= weight; visit_phy[cur_node] = 0; return; }

	for (auto it = curset.begin(); it != curset.end(); it++) {
		if (!(it->node) && Dist_cur != 0) { Search_Largest_Path(it->node, it->weight); continue; }
		if (visit_phy[it->node]) { continue; }

		Search_Largest_Path(it->node, it->weight);
	}
	Dist_cur -= weight;
	visit_phy[cur_node] = 0;
	return;
}


int main() {

	cin >> V >> E;
	int e;
	char v1, v2;
	VInfo temp;

	for (int i = 0; i < E; i++) {
		cin >> v1 >> v2 >> e;

		temp.node = v2 - 'a';
		temp.weight = e;
		VVec.at(v1 - 'a').insert(temp);

		temp.node = v1 - 'a';
		VVec.at(v2 - 'a').insert(temp);
	}

	Search_Largest_Path(0, 0);
	cout << Dist_max;

	return 0;
}
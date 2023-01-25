#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<pair<int, int>> g[26];
vector<int> great;
vector<int> ng;
bool visit[26]{};
int bound = 0, answer = 0, midsol = 0, edge = 0;

bool near() {
	for (auto iter : g[0]) {
		if (!visit[iter.first]) return true;
	}
	return false;
}

bool bfs(int start) {
	bool v[26];
	copy(visit, visit + 26, v);
	queue<int> q;
	q.push(start);
	v[start] = true;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < g[x].size(); i++) {
			int y = g[x][i].first;
			if (y == 0) return true;
			if (!v[y]) {
				q.push(y);
				v[y] = true;
			}
		}
	}
	return false;
}

void fun(int vertex) {
	if (vertex == 0) {
		if (midsol > answer) answer = midsol;
		return;
	}
	else if (!near()) return;
	else if (midsol + bound + edge <= answer) return;
	else if (!bfs(vertex)) return;

	for (auto iter : g[vertex]) {
		if (visit[iter.first] == true) continue;
		visit[vertex] = true;
		bound -= great[iter.first];
		midsol += iter.second;
		edge = iter.second;
		fun(iter.first);
		visit[iter.first] = false;
		midsol -= iter.second;
		bound += great[iter.first];
	}

	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int N, M;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		char in1, in2;
		int d;
		cin >> in1 >> in2 >> d;
		g[in1 - 'a'].push_back({ in2 - 'a', d });
		g[in2 - 'a'].push_back({ in1 - 'a', d });
	}

	for (int i = 0; i < 26; i++) {
		if (g[i].size() != 0) {
			auto maxe = *max_element(g[i].begin(), g[i].end(),
				[](auto f, auto s) { return f.second < s.second; });
			great.push_back(maxe.second);
		}
		else great.push_back(0);
	}

	int bd = accumulate(great.begin() + 1, great.end(), 0);

	for (int i = 0; i < g[0].size(); i++) {
		memset(visit, false, sizeof(visit));
		midsol = g[0][i].second;
		bound = bd - g[0][i].second;
		fun(g[0][i].first);
	}

	cout << answer;
}
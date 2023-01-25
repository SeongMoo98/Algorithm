#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<algorithm>

using namespace std;

vector<vector<int>> vertex;
int dist[26][26];
int d[26][26];

vector<vector<char>> answers;
bool checked[26] = { 0, };
vector<char> trace;
int res = 0;

//모든 vertex에서의 최단거리
//==> 현재 vertex에서 모든 vertex의 최단거리
void floyd(int v) {
	//v : 현재 vertex
	for (int k = 0; k < 26; k++) //k : 거쳐가는 정점
		for (int j = 0; j < 26; j++) //j : 도착 정점
			d[v][j] = min(d[v][j], d[v][k] + d[k][j]);
}

//distance합이 큰게 앞으로
struct compare {
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.second < p2.second;
	}

};
bool BFS(vector<vector<int>> vertex, int src, int dest)
{
	queue<int> queue;

	bool* visited = new bool[26];
	for (int i = 0; i < 26; i++)
		visited[i] = checked[i];

	visited[src] = true;
	queue.push(src);

	// standard BFS algorithm
	while (!queue.empty()) {
		int u = queue.front();
		queue.pop();
		for (int i = 0; i < vertex[u].size(); i++) {
			if (visited[vertex[u][i]] == false) {
				visited[vertex[u][i]] = true;
				queue.push(vertex[u][i]);

				if (vertex[u][i] == dest)
					return true;
			}
		}
	}

	return false;
}

void DFS(int v, int dis_sum) {
	checked[v] = true;
	res = dis_sum;
	int d = 0;

	for (int i : vertex[v]) {
		d = dist[v][i];
		if (i == 0) {
			res = dis_sum + d;
			continue;
		}
		if (checked[i] == true) continue;
		DFS(i, dis_sum + dist[v][i]);
	}
	checked[v] = false;
	res -= d;
}



void print_ans() {
	if (answers.size() == 0) {
		cout << "None";
		return;
	}
	cout << answers[0].size() << "\n";
	for (char c : answers[0])
		cout << (char)(c + 'a') << " ";
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	priority_queue<pair<int, int>, deque<pair<int, int>>, compare>* pq = new priority_queue<pair<int, int>, deque<pair<int, int>>, compare>;
	int N, M;
	cin >> N >> M;
	vertex.resize(26, vector<int>(0));
	for (int i = 0; i < M; i++) {
		char u, v;
		int weitght;
		cin >> u >> v >> weitght;
		vertex[u - 'a'].push_back(v - 'a');
		vertex[v - 'a'].push_back(u - 'a');

		dist[u - 'a'][v - 'a'] = weitght;
		dist[v - 'a'][u - 'a'] = weitght;
	}

	DFS(0, 0);
	cout << res;
	/*sort(answers.begin(), answers.end(), comp);
	print_ans();*/
	return 0;
}







//
//void DFS_s(int v, int dis_sum, priority_queue<pair<int, int>, deque<pair<int, int>>, compare>* pq) {
//	checked[v] = true;
//	trace.push_back(v);
//
//	for (int i : vertex[v]) {
//		pq->push({ i, dis_sum + dist[v][i] });
//		cout << pq->top().second << " ";
//	}
//	//first - 노드번호, second - weight합
//	pair<int, int> cur = pq->top();
//	pq->pop();
//	while (!pq->empty()) {
//		int i = cur.first;
//		if (i == 0) {
//			res = dis_sum + dist[v][i];
//		}
//
//		if (checked[i] == true || !BFS(vertex, v, 0))
//			continue;
//
//		DFS(i, dis_sum + dist[v][i], pq);
//	}
//	checked[v] = false;
//	trace.pop_back();
//
//	//for (int i : cur.first) {
//	//	//vertex 0에 도달했는데 distance가 42이면 그 vertex를 추가
//	//	if (i == 0) {
//	//		if (dis_sum + dist[v][i] )
//	//			answers.push_back(trace);
//	//		continue;
//	//	}
//
//	//	/**************/
//	//	if (checked[i] == true || dis_sum + dist[v][i] >= 42)
//	//		continue;
//	//	//DFS(i, dis_sum + dist[v][i]);
//	//}
//	//backtrack
//	checked[v] = false;
//	trace.pop_back();
//}
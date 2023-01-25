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
int* max_len = new int;

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

	bool visited[26] = { 0, };
	for (int i = 1; i < 26; i++)
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
	int curr_len = 0;
	int d = 0;

	for (int i : vertex[v]) {
		curr_len = dis_sum + dist[v][i];
		if (i == 0) {
			continue;
		}
		//방문했던 곳이거나 !(돌아가는 길이 있다)
		if (checked[i] == true || !BFS(vertex, i, 0))
			continue;
		DFS(i, dis_sum + dist[v][i]);
	}
	if ((*max_len) < curr_len)
		*max_len = curr_len;
	curr_len = 0;

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
	cout << *max_len;
	/*sort(answers.begin(), answers.end(), comp);
	print_ans();*/
	return 0;
}








#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<algorithm>

using namespace std;

vector<vector<int>> vertex;
int dist[26][26];

bool checked[26] = { 0, };
int max_distance = 0;


int distance_max_from_vertex(int src) {
	queue<int> q;

	bool visited[26] = { 0, };
	int index = 0;
	int subtree_max_distance = 0;
	int temp = 0;
	for (int i = 1; i < 26; i++)
		visited[i] = checked[i];

	visited[src] = true;
	q.push(src);


	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int i = 0; i < vertex[u].size(); i++) {
			if (visited[vertex[u][i]] == false) {
				visited[vertex[u][i]] = true;
				if (dist[u][vertex[u][i]] >= temp) {
					temp = dist[u][vertex[u][i]];
					index = vertex[u][i];
				}
			}
		}
		subtree_max_distance += temp;
		if (index == 0) break;
		q.push(index);
		index = 0;
	}

	return subtree_max_distance;
}

//현재 vertex에서 dest(0 = a )까지 가는 길이 있는지 확인
bool BFS(vector<vector<int>> vertex, int src, int dest)
{
	queue<int> q;

	bool visited[26] = { 0, };
	for (int i = 1; i < 26; i++)
		visited[i] = checked[i];

	visited[src] = true;
	q.push(src);

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int i = 0; i < vertex[u].size(); i++) {
			if (visited[vertex[u][i]] == false) {
				visited[vertex[u][i]] = true;
				q.push(vertex[u][i]);

				if (vertex[u][i] == dest)
					return true;
			}
		}
	}

	return false;
}

void DFS(int v, int dist_sum) {
	checked[v] = true;
	int current_dist = 0;

	for (int i : vertex[v]) {
		current_dist = dist_sum + dist[v][i];

		if (i == 0)
			continue;

		//방문했던 곳이거나 !(돌아가는 길이 있다)
		if (checked[i] == true || !BFS(vertex, i, 0) || (max_distance > distance_max_from_vertex(i) + dist_sum)) continue;
		DFS(i, dist_sum + dist[v][i]);
	}
	if (max_distance < current_dist)
		max_distance = current_dist;
	current_dist = 0;
	checked[v] = false;
}


int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

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
	cout << max_distance;

	return 0;
}


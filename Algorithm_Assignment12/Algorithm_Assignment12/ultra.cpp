#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

vector<vector<int>> vertex;
int dist[26][26];

bool checked[26] = { 0, };
int* max_len = new int;

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

				if (vertex[u][i] == dest) return true;
			}
		}
	}

	return false;
}

void DFS(int v, int dis_sum) {
	checked[v] = true;
	int curr_len = 0;

	for (int i : vertex[v]) {
		curr_len = dis_sum + dist[v][i];
		if (i == 0) 
			continue;

		if (checked[i] == true || !BFS(vertex, i, 0))
			continue;
		DFS(i, dis_sum + dist[v][i]);
	}
	if ((*max_len) < curr_len)
		*max_len = curr_len;
	curr_len = 0;

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

		dist[u - 'a'][v - 'a'] = dist[v - 'a'][u - 'a'] = weitght;
	}


	DFS(0, 0);
	cout << *max_len;

	return 0;
}




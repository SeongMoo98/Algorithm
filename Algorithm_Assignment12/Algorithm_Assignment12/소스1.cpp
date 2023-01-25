#include<iostream>
#include<vector>
using namespace std;


void DFS(vector<pair<int, int>>* graph, int src, int prev_len, int* max_len, bool visited[]) {
    visited[src] = true;

    int curr_len = 0;

    pair <int, int> adjacent;

    for (int i = 0; i < graph[src].size(); i++) {

        adjacent = graph[src][i];


        if (!visited[adjacent.first]) {

            curr_len = prev_len + adjacent.second;

            DFS(graph, adjacent.first, curr_len, max_len, visited);
        }
        if ((*max_len) < curr_len)
            *max_len = curr_len;

        curr_len = 0;
    }
}


int longestCable(vector<pair<int, int>>* graph, int n)
{
    int max_len = 1234567890;
    bool visited[26] = { false, };
    DFS(graph, 0, 0, &max_len, visited);

    return max_len;
}

int main()
{
    int n = 26;

    vector< pair<int, int> >* graph = new vector<pair<int, int>>[n + 1];

    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        char u, v;
        int weight;
        cin >> u >> v >> weight;
        graph[u - 'a'].push_back({ v - 'a',weight });
        graph[v - 'a'].push_back({ u - 'a',weight });
    }

    cout << longestCable(graph, n);

    return 0;
}
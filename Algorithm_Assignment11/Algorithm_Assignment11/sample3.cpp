#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1234567890;
vector<pair<int, int>> linked[26];
bool visited[26];
int length = 42;
int idx = 1, final_idx = 0;
int* ans, * final_ans;
vector<int> dist(26, INF);

void fun(int vertex) {
    if (vertex == 0) {
        if (length == 0) {
            if (idx > final_idx) {
                final_idx = idx;
                copy(ans, ans + idx - 1, final_ans);
            }
        }
        return;
    }
    else if (length <= 0) return;
    else if (dist[vertex] > length) return;

    for (pair<int, int> pii : linked[vertex]) {
        if (visited[pii.first]) 
            continue;

        length -= pii.second;
        visited[pii.first] = true;
        ans[idx++] = pii.first;

        fun(pii.first);

        length += pii.second;
        visited[pii.first] = false;
        idx--;
    }
}

inline void start_a() {
    for (int i = 0; i < linked[0].size() - 1; i++) {
        int next = linked[0][i].first;
        int w = linked[0][i].second;

        length -= w;
        visited[next] = true;
        ans[idx++] = next;

        fun(next);

        length += w;
        visited[next] = false;
        idx--;
    }
}

void find_dist() {
    dist[0] = 0;

    priority_queue<pair<int, int>> pq;
    pq.push({ 0, 0 });
    while (!pq.empty()) {
        int cur = pq.top().first;
        int d = -pq.top().second;
        pq.pop();

        if (dist[cur] < d) continue;
        for (pair<int, int> pii : linked[cur]) {
            int next = pii.first;
            int next_d = pii.second + d;
            if (next_d < dist[next]) {
                dist[next] = next_d;
                pq.push({ next, -next_d });
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (dist[i] > 21) {
            visited[i] = true;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        char c1, c2;
        int v1, v2, w;
        cin >> c1 >> c2 >> w;
        v1 = c1 - 'a';
        v2 = c2 - 'a';
        linked[v1].push_back({ v2, w });
        linked[v2].push_back({ v1, w });
    }

    find_dist();

    for (int i = 0; i < 26; i++) {
        if (!visited[i])
            sort(linked[i].begin(), linked[i].end());
    }

    ans = new int[n + 1];
    final_ans = new int[n + 1];
    ans[0] = 0;
    start_a();

    if (final_idx <= 1)
        cout << "None";
    else {
        cout << final_idx - 1 << "\n";
        for (int i = 0; i < final_idx - 1; i++)
            cout << (char)(final_ans[i] + 'a') << " ";
        cout << "\n";
    }
}
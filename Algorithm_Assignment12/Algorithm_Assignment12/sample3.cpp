#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool exp[26], q_exp[26];
int N, M, d, max_sum = 0, ex_d[26], ex_sum = 0;
char u, v;
vector<pair<int, int>> edge_list[26];
queue<int> q;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

bool bfs(int des) {
    if (des == 0) return 1;

    bool f = 0;
    int cnt = 0;
    q.push(0);

    for (int i = 0; i < 26; i++) q_exp[i] = 0;

    q_exp[0] = 1;

    while (!q.empty()) {
        cnt++;

        for (int i = 0; i < edge_list[q.front()].size(); i++) {
            int temp = edge_list[q.front()][i].second;

            if (des == temp) {
                f = 1;
                break;
            }

            if (exp[temp] == 1) continue;

            if (!q_exp[temp]) {
                q.push(temp);
                q_exp[temp] = 1;
            }
        }

        q.pop();
    }

    return f;
}

void assign_edge() {
    cin >> N >> M;

    for (int i = 0; i < 26; i++) {
        exp[i] = 0;
        ex_d[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        cin >> u >> v >> d;

        edge_list[u - 'a'].push_back({ d, v - 'a' });
        edge_list[v - 'a'].push_back({ d, u - 'a' });

        if (ex_d[u - 'a'] < d) ex_d[u - 'a'] = d;
        if (ex_d[v - 'a'] < d) ex_d[v - 'a'] = d;
    }

    for (int i = 0; i < 26; i++) ex_sum += ex_d[i];
}

void cycle(int s, int e, int sum) {
    if (exp[s]) {
        if (s == e && sum > max_sum) max_sum = sum;
        return;
    }

    if (bfs(s)) {
        exp[s] = 1;
        if (s != 0) ex_sum -= ex_d[s];

        vector<pair<int, int>> el = edge_list[s];
        while (!el.empty()) {
            d = el.back().first;
            v = el.back().second;
            el.pop_back();

            if (d == -1) continue;

            if (ex_sum + sum > max_sum) cycle(v, e, sum + d);
        }

        exp[s] = 0;
        if (s != 0) ex_sum += ex_d[s];
    }
}

int main()
{
    fastio();
    assign_edge();
    cycle(0, 0, 0);
    cout << max_sum;
}
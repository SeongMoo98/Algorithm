#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> vertex;
int dist[26][26];

bool comp(vector<char> a, vector<char> b) {
    if (a.size() != b.size())
        return a.size() > b.size();
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) 
            return a[i] < b[i];
    }
}

void init() {
    int n, m; cin >> n >> m;
    vertex.resize(26, vector<int>(0));
    while (m--) {
        char c1, c2; int d;
        cin >> c1 >> c2 >> d;
        vertex[c1 - 'a'].push_back(c2 - 'a');
        vertex[c2 - 'a'].push_back(c1 - 'a');

        dist[c1 - 'a'][c2 - 'a'] = d;
        dist[c2 - 'a'][c1 - 'a'] = d;
    }

}

vector<vector<char>> answers;
int checked[26] = { 0, };
vector<char> trace;

void dfs(int v, int dis_sum) {
    checked[v] = true;
    trace.push_back(v);
    for (int i : vertex[v]) {
        if (i == 0) {
            if (dis_sum + dist[v][i] == 42)
                answers.push_back(trace);
            continue;
        }
        if (checked[i] == true || dis_sum + dist[v][i] >= 42) continue;
        dfs(i, dis_sum + dist[v][i]);
    }
    checked[v] = false;
    trace.pop_back();
}

void print_ans() {
    if (answers.size() == 0) {
        cout << "None";
        return;
    }
    cout << answers[0].size() << "\n";
    for (char c : answers[0]) {
        cout << (char)(c + 'a') << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    init();
    dfs(0, 0);
    sort(answers.begin(), answers.end(), comp);
    print_ans();
}
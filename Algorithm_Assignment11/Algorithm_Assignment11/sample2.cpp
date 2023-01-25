#include <iostream>
#include<map>

using namespace std;
map<char, int> edges[26];
int d, N, M, cost;
char u, v, dest;
string res = "";

void getPath(string& s1, string& s2) {
    if (s1.length() == s2.length()) 
        res = min(s1, s2);
    res = s1.length() < s2.length() ? s2 : s1;
}

void dfs(string path, int dist) {
    if (dist >= 42)
        return;
    int from = path.back() - 'a';
    
    for (auto& edge : edges[from]) {
        tie(dest, cost) = edge;
        if (path.find(dest) == string::npos)
            dfs(path + dest, dist + cost);
        else if (dest == 'a' && dist + cost == 42)
            getPath(res, path);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;

    if (M < 100) {
        while (cin >> u >> v >> d) {
            edges[v - 'a'][u] = d;
            edges[u - 'a'][v] = d;
        }
        dfs("a", 0);
    }

    if (res.empty()) cout << "None\n";
    else {
        cout << res.length() << '\n';
        for (auto& c : res) cout << c << ' ';
    }
}
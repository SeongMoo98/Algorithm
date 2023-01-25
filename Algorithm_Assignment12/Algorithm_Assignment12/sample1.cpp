#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define max(x,y) x > y ? x : y

int V, E, u, v, d, half_V;
int edge[27], val[27][27], node[27][27], visit[27], Cvisit[27], max_val[27];
int dist = 0, ans = 0, flag = 0, max_sum = 0;
vector <int> block;

int FastBFS(int start) {
    memcpy(Cvisit, visit, sizeof(visit)); Cvisit[start] = 1;
    queue<int> Q; Q.push(start);
    while (!Q.empty()) {
        int cur = Q.front(); Q.pop();
        for (int i = edge[cur] - 1; i >= 0; i--) {
            int next = node[cur][i];
            if (next == 0 && flag) return 1;
            if (!Cvisit[next] && val[cur][next] > 0) { Cvisit[next] = 1; Q.push(next); }
        }
    }
    return 0;
}

void set_vis() {
    memset(visit, 0, sizeof(visit));
    for (int i = 0; i < block.size(); i++) visit[block[i]] = 1;
}

void DFS(int start) {
    if (!FastBFS(start)) return;
    visit[start] = 1; max_sum -= max_val[start];
    int i = edge[start];
    do {
        int next = node[start][i - 1];
        if (next == 0) { ans = max(ans, dist + val[start][next]); }
        if (!visit[next]) {
            if (dist + max_sum < ans - 2) { --i; continue; }
            dist += val[start][next];
            DFS(next);
            dist -= val[start][next];
        } --i;
    } while (i);
    visit[start] = 0; max_sum += max_val[start];
}

int main() {
    scanf("%d %d", &V, &E);
    while (E--) {
        scanf(" %c %c %d", &u, &v, &d);
        u -= 97; v -= 97;
        node[u][edge[u]] = v; node[v][edge[v]] = u;
        val[u][v] = d; val[v][u] = d;
        ++edge[u]; ++edge[v];
    }
    for (int i = 25; i >= 0; i--) { if (edge[i] == 1) block.push_back(i); }
    for (int i = 0; i < 26; i++) {
        int this_max = 0;
        for (int j = 0; j < i + 1; j++) {
            this_max = max(this_max, val[i][j]);
        }
        for (int j = i + 1; j < 26; j++) {
            if (val[i][j] != 0) {
                this_max = max(this_max, val[i][j]);
                int tmp = val[i][j];
                val[i][j] = -1; val[j][i] = -1;
                FastBFS(0);
                val[i][j] = tmp; val[j][i] = tmp;
                int cnt = 0;
                for (int k = 25; k >= 0; k--) cnt += Cvisit[k];
                if (cnt != V) {
                    set_vis(); visit[i] = 1;
                    memcpy(Cvisit, visit, sizeof(visit));
                    FastBFS(0);
                    if (!Cvisit[j]) block.push_back(j);
                }
                set_vis();
            }
        }
        max_val[i] = this_max; max_sum += max_val[i];
    }
    set_vis(); memcpy(Cvisit, visit, sizeof(visit));
    visit[0] = 1; max_sum -= max_val[0]; flag = 1;
    for (int i = edge[0] - 1; i != 0; i--) {
        int next = node[0][i];
        dist += val[0][next];
        DFS(next);
        dist = 0;
    }
    printf("%d\n", ans);
    return 0;
}
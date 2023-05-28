/**
 * 洛谷 P3385 Bellman Ford / SPFA
 * 求负环
*/
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e3 + 10, M = 7e3 + 10, INF = 0x7f7f7f7f;

struct Edge {
    int src;
    int dst;
    int w;
} edges[M];

int dis[N];

void solve() {
    int n, m;
    cin >> n >> m;
    int cnt = 0;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[++ cnt] = {u, v, w};
        if (w >= 0) {
            edges[++ cnt] = {v, u, w};
        }
    }

    memset(dis, 0x7f, sizeof dis);
    dis[1] = 0;

    for (int i = 1; i <= n; i ++) {
        bool updated = false;
        for (int j = 1; j <= cnt; j ++) {
            int src = edges[j].src, dst = edges[j].dst, w = edges[j].w;
            if (dis[src] == INF) {
                continue;
            }
            if (dis[dst] > dis[src] + w) {
                updated = true;
                dis[dst] = dis[src] + w;
            }
        }
        if (i == n) {
            if (updated) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        solve();
    }
    
    return 0;
}
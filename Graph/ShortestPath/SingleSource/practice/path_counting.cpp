/**
 * P1608 有向带权图上的最短路计数
 * Dijkstra 加个 DP 就好，应该按照加入最短路集合
 * 的次序来 DP
*/
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2020;

int dist[N];

int g[N][N];

int order[N];

int cnt;

bool st[N];

int f[N];

int main() {
    int n, m;
    cin >> n >> m;

    memset(g, 0x3f, sizeof g);
    memset(dist, 0x3f, sizeof dist);
    
    for (int i = 1; i <= n; i ++) {
        g[i][i] = 0;
    }

    for (int i = 1; i <= m; i ++) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x][y] = min(g[x][y], z);
    }

    dist[1] = 0;

    for (int i = 1; i <= n; i ++) {
        int t = -1;
        for (int j = 1; j <= n; j ++) {
            if (!st[j] && (t == -1 || dist[j] < dist[t])) {
                t = j;
            }
        }
        if (dist[t] == 0x3f3f3f3f) {
            break;
        }

        st[t] = true;
        order[++ cnt] = t;

        for (int j = 1; j <= n; j ++) {
            if (g[t][j] != 0x3f3f3f3f) {
                dist[j] = min(dist[j], dist[t] + g[t][j]);
            }
        }
    }

    if (dist[n] == 0x3f3f3f3f) {
        cout << "No answer" << endl;
        return 0;
    }

    f[1] = 1;

    for (int i = 1; i <= cnt; i ++) {
        int v = order[i];
        for (int j = i + 1; j <= cnt; j ++) {
            int u = order[j];
            if (g[v][u] == 0x3f3f3f3f) {
                continue;
            }
            if (dist[u] == dist[v] + g[v][u]) {
                f[u] += f[v];
            }
        }
    }

    cout << dist[n] << " " << f[n] << endl;

    return 0;
}
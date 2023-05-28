/**
 * 洛谷 P3371 单源最短路弱化版
*/
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e4 + 10,M = 5e5 + 10, INF = 0x7f7f7f7f;

int e[M], ne[M], w[M], h[N], idx;

bool vis[N];

int d[N];

void add(int x, int y, int z) {
    e[idx] = y;
    ne[idx] = h[x];
    w[idx] = z;
    h[x] = idx ++;
}

int main() {

    int n, m, s;

    cin >> n >> m >> s;

    memset(h, -1, sizeof h);

    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    memset(d, 0x7f, sizeof d);

    d[s] = 0;

    for (int i = 1; i <= n; i ++) {
        int t = -1;

        for (int j = 1; j <= n; j ++) {
            if (!vis[j] && (t == -1 || d[t] > d[j])) {
                t = j;
            }
        }

        if (d[t] == INF) {
            break;
        }

        vis[t] = true;

        for (int k = h[t]; k != -1; k = ne[k]) {
            int u = e[k];
            d[u] = min(d[u], d[t] + w[k]);
        }
    }

    for (int i = 1; i <= n; i ++) {
        if (d[i] == INF) {
            cout << 2147483647 << " ";
        } else {
            cout << d[i] << " ";
        }
    }

    return 0;
}
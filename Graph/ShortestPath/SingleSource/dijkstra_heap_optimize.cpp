/**
 * 洛谷 P4779 单源最短路标准版
*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e5 + 10,M = 2e5 + 10, INF = 0x7f7f7f7f;

int e[M], ne[M], w[M], h[N], idx;

bool vis[N];

int d[N];

using pii = pair<int, int>;

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

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    memset(d, 0x7f, sizeof d);

    d[s] = 0;

    pq.push({d[s], s});

    while (!pq.empty()) {
        pii t = pq.top();
        pq.pop();
        int v = t.second, dis = t.first;
        if (vis[v]) {
            continue;
        }
        vis[v] = true;
        for (int j = h[v]; j != -1; j = ne[j]) {
            int u = e[j];
            if (d[u] > dis + w[j]) {
                pq.push({dis + w[j], u});
            }
            d[u] = min(d[u], dis + w[j]);
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
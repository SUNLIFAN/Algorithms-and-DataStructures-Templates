/**
 * 洛谷 P1087 求 DAG 上的最长路
 * 下面给出的一种做法是将边权取负之后跑一遍 bellman ford 求最短路
*/
/**
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1510, M = 5e4 + 10;

struct Edge {
    int src;
    int dst;
    int w;
} edges[M];

int dist[N];

int main() {
    int n,m;
    cin >> n >> m;

    memset(dist, 0x3f, sizeof dist);

    for (int i = 1; i <= m; i ++) {
        int x, y, z;
        cin >> x >> y >> z;
        edges[i] = {x, y, -z};
    }

    dist[1] = 0;

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            Edge& e = edges[j];
            int src = e.src, dst = e.dst, w = e.w;
            if (dist[src] == 0x3f3f3f3f) {
                continue;
            }
            dist[dst] = min(dist[dst], dist[src] + w);
        }
    }

    if (dist[n] == 0x3f3f3f3f) {
        cout << -1 << endl;
    } else {
        cout << -dist[n] << endl;
    }

    return 0;
}
**/

/**
 * 下面给出的第二种做法，只需要线性时间复杂度
 * 先进行拓扑排序，然后根据拓扑逆序计算到 n 的最长路
*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int N = 2e3 + 10, M = 5e4 + 10;

int e[M], ne[M], w[M], h[N], idx;

int order[N], indeg[N];

int dist[N];

int cnt;

void add(int x, int y, int z) {
    e[idx] = y;
    ne[idx] = h[x];
    w[idx] = z;
    h[x] = idx ++;
}

int main() {

    int n, m;

    cin >> n >> m;

    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i ++) {
        dist[i] = -0x3f3f3f3f;
    }

    for (int i = 1; i <= m; i ++) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
        indeg[y] ++;
    }

    queue<int> q;

    for (int i = 1; i <= n; i ++) {
        if (!indeg[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        order[ ++ cnt] = t;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (-- indeg[j] == 0) {
                q.push(j);
            }
        }
    }

    dist[n] = 0;

    for (int i = cnt; i >= 1; i --) {
        int cur = order[i];
        for (int j = h[cur]; ~j; j = ne[j]) {
            int son = e[j];
            if (dist[son] == -0x3f3f3f3f) {
                continue;
            }
            dist[cur] = max(dist[cur], dist[son] + w[j]);
        }
    }

    if (dist[1] == -0x3f3f3f3f) {
        cout << -1 << endl;
    } else {
        cout << dist[1] << endl;
    }

    return 0;
}
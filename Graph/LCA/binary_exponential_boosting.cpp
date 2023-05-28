/**
 * P3379 洛谷 LCA 模板题
 * 倍增法
*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5e5 + 10, M = N << 1;

int e[M], ne[M], h[N], idx;

int depth[N];

int fa[N][30];

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void dfs(int u, int fat) {
    depth[u] = depth[fat] + 1;
    fa[u][0] = fat;
    for (int i = 1; i <= 20; i ++) {
        fa[u][i] = fa[fa[u][i-1]][i-1];
    }

    for (int i = h[u]; ~i; i = ne[i]) {
        int son = e[i];
        if (son == fat) {
            continue;
        }
        dfs(son, u);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        swap(u, v);
    }

    for (int i = 0, delta = depth[v] - depth[u]; delta > 0; delta >>= 1, i ++) {
        if (delta & 1) {
            v = fa[v][i];
        }
    }

    if (u == v) {
        return u;
    }

    for (int i = 20; i >= 0; i --) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i], v = fa[v][i];
        }
    }

    return fa[u][0];
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n - 1; i ++) {
        int x, y;
        cin >> x >> y;
        add(x, y), add(y, x);
    }

    dfs(s, 0);

    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
    return 0;
}
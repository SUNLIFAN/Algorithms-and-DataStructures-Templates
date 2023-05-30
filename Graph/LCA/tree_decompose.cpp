/**
 * P3379 LCA 模板题 树链剖分写法
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 5e5 + 10;

int e[N << 1], ne[N << 1], h[N], idx;

int son[N], fa[N], siz[N], dep[N];

int top[N];

int root;

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void dfs1(int u, int fat, int d) {
    siz[u] = 1, fa[u] = fat, dep[u] = d;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fat) {
            continue;
        }

        dfs1(v, u, d + 1);

        siz[u] += siz[v];

        if (siz[v] > siz[son[u]]) {
            son[u] = v;
        }
    }
}

void dfs2(int u, int topf) {
    top[u] = topf;

    if (!son[u]) {
        return;
    }

    dfs2(son[u], topf);

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fa[u] || v == son[u]) {
            continue;
        }

        dfs2(v, v);
    }
}

void init() {
    dfs1(root, 0, 1);
    dfs2(root, root);
}

int lca(int u, int v) {
    // 不在同一条链
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        u = fa[top[u]];
    }

    if (dep[u] > dep[v]) {
        swap(u, v);
    }

    return u;
}

int main() {

    int n, m;

    cin >> n >> m >> root;

    memset(h, -1, sizeof h);

    for (int i = 1; i <= n - 1; i ++) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }

    init();

    while (m --) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }

    return 0;
}
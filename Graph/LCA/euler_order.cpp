/**
 * P3379 欧拉序求 LCA 模板
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 5e5 + 10, M = N << 1;

int dfn[N << 1], d[N], dfsc, first[N];

int st[N << 1][30];

int e[M], ne[M], h[N], idx;

int log_[N << 1];

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void dfs(int u, int fa) {
    dfn[++ dfsc] = u;
    first[u] = dfsc;
    d[u] = d[fa] + 1;

    for (int i = h[u]; ~i; i = ne[i]) {
        int son = e[i];
        if (son == fa) {
            continue;
        }

        dfs(son, u);

        dfn[++ dfsc] = u;
    }   
}

int query(int l, int r) {
    int k = log_[r - l + 1];
    int pos1 = st[l][k], pos2 = st[r - (1 << k) + 1][k];

    return d[pos1] < d[pos2] ? pos1 : pos2;
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

    for (int i = 1; i <= dfsc; i ++) {
        log_[i] = log2(i);
    }

    for (int i = 1; i <= dfsc; i ++) {
        st[i][0] = dfn[i];
    }

    for (int j = 1; j <= 20; j ++) {
        for (int i = 1; i + (1 << j) <= dfsc; i ++) {
            int pos1 = st[i][j-1], pos2 = st[i + (1 << (j-1))][j-1];
            st[i][j] = d[pos1] < d[pos2] ? pos1 : pos2;
        }
    }

    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        u = first[u], v = first[v];
        if (u > v) {
            swap(u, v);
        }
        cout << query(u, v) << endl;
    }

    return 0;
}
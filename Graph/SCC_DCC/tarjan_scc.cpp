/**
 * 本题是洛谷上的模板题 P3387 缩点
 * 求完 SCC 之后按照拓扑序计算点权最大值
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e4 + 10, M = 1e5 + 10;

int e[M], ne[M], h[N], v[N], idx, esp;

int dfn[N], low[N], stk[N];

int dfsc, scc_cnt;

int id[N];

int se[M], sne[M], sh[N], sv[N], sidx;

bool in_stk[N];

int f[N];

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void sadd(int x, int y) {
    se[sidx] = y;
    sne[sidx] = sh[x];
    sh[x] = sidx ++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ dfsc;
    stk[++ esp] = u;
    in_stk[u] = true;

    for (int i = h[u]; i != -1; i = ne[i]) {
        int son = e[i];
        // 树边
        if (!dfn[son]) {
            tarjan(son);
            low[u] = min(low[u], low[son]);
        } else if (in_stk[son]) {
            // 非树边
            low[u] = min(low[u], dfn[son]);
        }
    }

    if (dfn[u] == low[u]) {
        int y;
        scc_cnt ++;
        do {
            y = stk[esp --];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sv[scc_cnt] += v[y];
        } while (y != u);
    }
}

int dfs(int u) {
    if (f[u] != -1) {
        return f[u];
    }

    int son_ans = 0;
    for (int i = sh[u]; ~i; i = sne[i]) {
        int son = se[i];
        son_ans = max(son_ans, dfs(son));
    }

    f[u] = sv[u] + son_ans;

    return f[u];
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        cin >> v[i];
    }

    memset(h, -1, sizeof h);
    memset(sh, -1, sizeof sh);
    memset(f, -1, sizeof f);

    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        add(x, y);
    }

    for (int i = 1; i <= n; i ++) {
        if (!id[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int son = e[j];
            if (id[son] != id[i]) {
                sadd(id[i], id[son]);
            }
        }
    }

    int ans = 0;

    for (int i = 1; i <= scc_cnt; i ++) {
        ans = max(ans, dfs(i));
    }

    cout << ans << endl;

    return 0;
}
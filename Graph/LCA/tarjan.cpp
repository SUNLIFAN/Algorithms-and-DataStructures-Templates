/**
 * P3379 Tarjan 求 LCA 模板
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 5e5 + 10, M = N << 1;

int e[M], ne[M], h[N], idx;

int p[N];

int ans[N];

int st[N];

using pii = pair<int, int>;

vector<pii> query[N];

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }

    return p[x];
}

void merge(int u, int v) {
    u = find(u), v = find(v);
    p[v] = u;
}

void tarjan(int u) {
    st[u] ++;

    for (int i = h[u]; ~i; i = ne[i]) {
        int son = e[i];
        if (st[son]) {
            continue;
        }
        tarjan(son);
        merge(u, son);
    }

    for (pii q : query[u]) {
        int id = q.first, v = q.second;
        if (st[v] == 2) {
            ans[id] = find(v);
        }
    }
    st[u] ++;
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i ++) {
        p[i] = i;
    }

    for (int i = 1; i <= n - 1; i ++) {
        int x, y;
        cin >> x >> y;
        add(x, y), add(y, x);
    }

    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        if (u == v) {
            ans[i] = u;
        } else {
            query[u].push_back({i, v});
            query[v].push_back({i, u});
        }
    }

    tarjan(s);

    for (int i = 1; i <= m; i ++) {
        cout << ans[i] << endl;
    }

    return 0;
}
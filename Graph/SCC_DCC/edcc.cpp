/**
 * P8436 边双连通分量模板题
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 5e5 + 10, M = 2e6 + 10;

int e[M << 1], ne[M << 1], h[N], idx = 2;

int low[N], dfn[N], dfsc;

int id[N], cnt;

bool isBridge[M << 1];

int stk[N], esp;

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void tarjan(int u, int inEdge) {
    low[u] = dfn[u] = ++ dfsc;
    stk[++ esp] = u;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                isBridge[i] = isBridge[i ^ 1] = true;
            }
        } else if (i != (inEdge ^ 1)) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        int v;
        cnt ++;
        do {
            v = stk[esp--];
            id[v] = cnt;
        } while (v != u);
    }
}

vector<int> dcc[N];

int main() {
    int n, m;
    cin >> n >> m;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i ++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    for (int i = 1; i <= n; i ++) {
        if (!id[i]) {
            tarjan(i, 0);
        }
    }

    for (int i = 1; i <= n; i ++) {
        dcc[id[i]].push_back(i);
    }

    cout << cnt << endl;

    for (int i = 1; i <= cnt; i ++) {
        cout << dcc[i].size() << " ";
        for (int j = 0; j < dcc[i].size(); j ++) {
            cout << dcc[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}
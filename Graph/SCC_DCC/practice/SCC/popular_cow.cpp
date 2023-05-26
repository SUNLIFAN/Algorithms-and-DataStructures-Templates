/**
 * SCC 习题 P2341 受欢迎的牛
 * 缩点之后考虑出度为 0 的点，如果超过两个，那么不存在受所有牛喜爱的
 * 如果只有一个，那么受欢迎的牛的个数就是这个 SCC 的大小
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e4 + 10, M = 5e4 + 10;

int e[M], ne[M], h[N], idx;

int in_stk[N], siz[N], id[N], deg[N];

int scc_cnt;

int dfn[N], low[N], dfsc;

int esp, stk[N];

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ dfsc;
    stk[++ esp] = u;
    in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i]) {
        int son = e[i];
        if (!dfn[son]) {
            tarjan(son);
            low[u] = min(low[u], low[son]);
        } else if (in_stk[son]) {
            low[u] = min(low[u], dfn[son]);
        }
    }

    if (low[u] == dfn[u]) {
        int y;
        ++ scc_cnt;
        do {
            y = stk[esp --];
            id[y] = scc_cnt;
            in_stk[y] = false;
            siz[scc_cnt] ++;
        } while (y != u);
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    memset(h, -1, sizeof h);

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
            if (id[i] != id[son]) {
                deg[id[i]] ++;
            }
        }
    }

    int sum = 0, zeros = 0;

    for (int i = 1; i <= scc_cnt; i ++) {
        if (deg[i] == 0) {
            zeros ++;
            sum = siz[i];
        }

        if (zeros > 1) {
            sum = 0;
            break;
        }
    }

    cout << sum << endl;

    return 0;
}
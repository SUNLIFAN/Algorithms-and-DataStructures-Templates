#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5 + 10;

int e[N], ne[N], h[N], idx;

int stk[N], esp;

bool in_stk[N];

int dfn[N], low[N], dfsc;

int siz[N];

int id[N];

int scc_cnt;

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
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (low[u] == dfn[u]) {
        int y;
        ++ scc_cnt;
        do {
            y = stk[esp--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            siz[scc_cnt] ++;
        } while (y != u);
    }
}

int main() {
    int n;
    cin >> n;

    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i ++) {
        int t;
        cin >> t;
        add(i, t);
    }

    int ans = 1e9;

    for (int i = 1; i <= n; i ++) {
        if (!id[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= scc_cnt; i ++) {
        if (siz[i] == 1) {
            continue;
        }

        ans = min(ans, siz[i]);
    }

    cout << ans << endl;


    return 0;
}
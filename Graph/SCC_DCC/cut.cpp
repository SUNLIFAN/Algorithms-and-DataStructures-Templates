/**
 * P3388 求割点模板题
*/
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e4 + 10, M = 1e5 + 10;

int low[N], dfn[N], dfsc;

int e[M << 1], ne[M << 1], h[N], idx = 2;

int root;

bool cut[N];

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void tarjan(int u, int inEdge) {
    low[u] = dfn[u] = ++ dfsc;
    int cnt = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) {
                ++ cnt;
                if (u != root || cnt >= 2) {
                    cut[u] = true;
                }
            }
        } else if (i != (inEdge ^ 1)) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        add(x, y), add(y, x);
    }

    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) {
            root = i;
            tarjan(i, 0);
        }
    }

    int count = 0;

    for (int i = 1; i <= n; i ++) {
        if (cut[i]) {
            count ++;
        }
    }

    cout << count << endl;
    
    for (int i = 1; i <= n; i ++) {
        if (cut[i]) {
            cout << i << " ";
        }
    }
    
    return 0;
}
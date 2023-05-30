/**
 * P8435 点双连通分量模板题
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 5e5 + 10, M = 2e6 + 10;

int e[M << 1], ne[M << 1], h[N], idx = 2;

int low[N], dfn[N], dfsc;

bool cut[N];

vector<int> dcc[N];


int stk[N], esp;

int dcc_cnt;

int root;

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void tarjan(int u, int inEdge) {
    dfn[u] = low[u] = ++ dfsc;
    stk[++ esp] = u;

    int cnt = 0;

    int son = 0;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (!dfn[v]) {
            ++ son;
            tarjan(v, i);
            low[u] = min(low[u], low[v]);

            if (dfn[u] <= low[v]) {
                ++ cnt;
                if (u != root || cnt >= 2) {
                    cut[u] = true;
                }

                int z;
                ++ dcc_cnt;
                do {
                    z = stk[esp --];
                    dcc[dcc_cnt].push_back(z);
                } while (z != v);
                dcc[dcc_cnt].push_back(u);
            }
        } else if (i != (inEdge ^ 1)) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (u == root && son == 0) {
        ++ dcc_cnt;
        dcc[dcc_cnt].push_back(u);
    }
}

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
        if (!dfn[i]) {
            // stk 要记得清空
            root = i;
            esp = 0;
            tarjan(i, 0);
        }
    }

    cout << dcc_cnt << endl;

    for (int i = 1; i <= dcc_cnt; i ++) {
        cout << dcc[i].size() << " ";
        for (int j = 0; j < dcc[i].size(); j ++) {
            cout << dcc[i][j] <<  " ";
        }
        cout << endl;
    }

    return 0;
}
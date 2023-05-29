/**
 * P1656 炸铁路
 * 求桥边模板题
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 200, M = 5050;

int dfn[N], low[N], dfsc;

int e[M << 1], ne[M << 1], h[N], idx = 2;

bool isBridge[M << 1];

using pii = pair<int, int>;

bool cmp(pii& a, pii& b) {
    if (a.first != b.first) {
        return a.first < b.first;
    }

    return a.second < b.second;
}

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void tarjan(int u, int inEdge) {
    dfn[u] = low[u] = ++ dfsc;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]) {
                isBridge[i] = isBridge[i ^ 1] = true;
            }
        } else if (i != (inEdge ^ 1)) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    int n, m;
    memset(h, -1, sizeof h);
    cin >> n >> m;

    for (int i = 1; i <= m; i ++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) {
            tarjan(i, 0);
        }
    }

    vector<pii> ans;

    for (int i = 1; i <= n; i ++) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int u = e[j];
            if (u <= i) {
                continue;
            }
            if (isBridge[j]) {
                ans.push_back({i, u});
            }
        } 
    }

    sort(ans.begin(), ans.end(), cmp);

    for (int i = 0; i < ans.size(); i ++) {
        int a = ans[i].first, b = ans[i].second;
        cout << a << " " << b << endl;
    }

    return 0;
}
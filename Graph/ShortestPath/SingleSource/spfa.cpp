/**
 * 洛谷 P3385 Bellman Ford / SPFA
 * 求负环
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 2e3 + 10, M = 7e3 + 10, INF = 0x7f7f7f7f;

int h[N], e[M], ne[M], w[M], idx;

int dis[N], cnt[N];

bool st[N];

void add(int x, int y, int z) {
    e[idx] = y;
    ne[idx] = h[x];
    w[idx] = z;
    h[x] = idx ++;
}

void solve() {
    int n, m;
    cin >> n >> m;

    memset(h, -1, sizeof h);
    idx = 0;

    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        if (w >= 0) {
            add(v, u, w);
        }
    }

    memset(dis, 0x7f, sizeof dis);
    dis[1] = 0;

    queue<int> q;
    q.push(1);
    cnt[1] = 0;
    st[1] = true;

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        st[1] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dis[j] > dis[t] + w[i]) {
                cnt[j] = cnt[t] + 1;
                dis[j] = dis[t] + w[i];
                if (!st[j]) {
                    q.push(j);
                }
                if (cnt[j] >= n) {
                    cout << "YES" << endl;
                    return;
                }
            }
        }
    }

    cout << "NO" << endl;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        solve();
    }
    
    return 0;
}
/**
 * 洛谷 P4017 最大食物链计数
 * 先拓扑排序，然后按照拓扑逆序 DP
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int N = 5e3 + 10, M = 5e5 + 10, MOD = 80112002;

int e[M], ne[M], h[N], idx;

int f[N];

int order[N], deg[N];

int cnt;

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

int main() {
    int n,m;
    cin >> n >> m;

    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i ++) {
        int a, b;
        cin >> a >> b;
        add(b, a);
        deg[a] ++;
    }

    // 拓扑排序

    queue<int> q;

    vector<int> src;

    for (int i = 1; i <= n; i ++) {
        if (!deg[i]) {
            q.push(i);
            src.push_back(i);
        }
    }

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        order[++ cnt] = t;

        for (int i = h[t]; ~i; i = ne[i]) {
            int son = e[i];
            if (-- deg[son] == 0) {
                q.push(son);
            }
        }
    }

    // 按照拓扑逆序 DP

    for (int i = cnt; i >= 1; i --) {
        int cur = order[i];
        if (h[cur] == -1) {
            f[cur] = 1;
            continue;
        }

        for (int j = h[cur]; ~j ; j = ne[j]) {
            int son = e[j];
            f[cur] = (f[cur] + f[son]) % MOD;
        }
    }

    int ans = 0;

    for (int i = 0; i < src.size(); i ++) {
        ans = (ans + f[src[i]]) % MOD;
    }

    cout << ans << endl;

    return 0;
}
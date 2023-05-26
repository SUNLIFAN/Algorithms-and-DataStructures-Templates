/**
 * 洛谷 P2196 挖地雷
 * 按照拓扑逆序 DP
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 30, M = N * N;

int e[M], ne[M], h[N], v[N], idx;

int order[N], deg[N];

int cnt;

int f[N];

int next_ans[N], start;

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

int main() {
    int n;
    cin >> n;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i ++) {
        cin >> v[i];
    }

    for (int i = 1; i <= n - 1; i ++) {
        for (int j = 1; i + j <= n; j ++) {
            int x;
            cin >> x;
            if (!x) {
                continue;
            }
            add(i, i + j);
            deg[i + j] ++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i ++) {
        if (!deg[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        order[++ cnt] = t;
        for (int i = h[t]; ~i ; i = ne[i]) {
            int j = e[i];
            if (-- deg[j] == 0) {
                q.push(j);
            }
        }
    }

    int ans = 0;

    for (int i = cnt; i >= 1; i --) {
        int cur = order[i];
        f[cur] = v[cur];
        for (int j = h[cur]; ~j; j = ne[j]) {
            int son = e[j];
            if (f[son] + v[cur] > f[cur]) {
                next_ans[cur] = son;
                f[cur] = f[son] + v[cur];
            }
        }
        if (f[cur] > ans) {
            ans = f[cur];
            start = cur;
        }
    }

    while (start != 0) {
        cout << start << " ";
        start = next_ans[start];
    }
    cout << endl;

    cout << ans << endl;

    return 0;
}
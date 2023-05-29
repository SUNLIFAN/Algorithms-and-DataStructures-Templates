/**
 * P1144 最短路计数
 * 无权无向图常用 BFS 来求最短路
 * 在求最短路的时候顺带计数就好
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e6 + 10, M = N << 1, MOD = 100003;

int e[M], ne[M], h[N], idx;

int f[N], dist[N];

void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

int main() {

    int n,m;

    cin >> n >> m;

    memset(h, -1, sizeof h);

    memset(dist, -1, sizeof dist);

    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        add(x, y), add(y, x);
    }

    dist[1] = 0;
    f[1] = 1;

    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int t = q.front();
        q.pop();

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] == -1) {
                dist[j] = dist[t] + 1;
                f[j] = (f[j] + f[t]) % MOD;
                q.push(j);
            } else if (dist[j] == dist[t] + 1) {
                f[j] = (f[j] + f[t]) % MOD;
            }
        }
    }

    for (int i = 1; i <= n; i ++) {
        cout << f[i] << endl;
    }

    return 0;
}
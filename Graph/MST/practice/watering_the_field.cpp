#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2020, M = N * N;

int e[M], ne[M], w[M], h[N], idx;

int x[N], y[N];

using i64 = long long;

int dist[N];

bool st[N];

void add(int x, int y, int z) {
    e[idx] = y;
    ne[idx] = h[x];
    w[idx] = z;
    h[x] = idx ++;
}

int ecd(int i, int j) {
    return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

int main() {
    int n, c;
    cin >> n >> c;

    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i ++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = i + 1; j <= n; j ++) {
            if (ecd(i, j) < c) {
                continue;
            }
            add(i, j, ecd(i, j));
            add(j, i, ecd(i, j));
        }
    }

    memset(dist, 0x3f, sizeof dist);

    dist[1] = 0;

    i64 ans = 0;

    bool fail = false;

    for (int i = 1; i <= n; i ++) {
        int t = -1;
        for (int j = 1; j <= n; j ++) {
            if (!st[j] && (t == -1 || dist[j] < dist[t])) {
                t = j;
            }
        }

        if (dist[t] == 0x3f3f3f3f) {
            fail = true;
            break;
        }

        st[t] = true;
        ans = ans + dist[t];

        for (int k = h[t]; ~k; k = ne[k]) {
            int son = e[k];
            dist[son] = min(dist[son], w[k]);
        }
    }

    cout << (fail ? -1 : ans) << endl;

    return 0;
}
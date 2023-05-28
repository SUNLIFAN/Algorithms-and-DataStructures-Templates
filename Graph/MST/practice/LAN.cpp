/**
 * 洛谷 P2820
 * 裸的 MST
 * 去掉的边权和最大等价于留下的边权和最小
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110, M = 2e5 + 10;

int e[M], ne[M], w[M], h[N], idx;

bool st[N];

int dist[N];

void add(int x, int y, int z) {
    e[idx] = y;
    ne[idx] = h[x];
    w[idx] = z;
    h[x] = idx ++;
}

int main() {

    int n, m;

    cin >> n >> m;

    memset(h, -1, sizeof h);

    int sum = 0;

    for (int i = 1; i <= m; i ++) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
        add(y, x, z);
        sum += z;
    }

    memset(dist, 0x3f, sizeof dist);

    dist[1] = 0;

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
        sum -= dist[t];

        for (int k = h[t]; ~k; k = ne[k]) {
            int son = e[k];
            dist[son] = min(dist[son], w[k]);
        }
    }

    cout << sum << endl;

    return 0;
}
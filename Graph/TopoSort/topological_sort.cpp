/**
 * 洛谷 P3644 拓扑排序模板题
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 110, M = N * N;

int e[M], ne[M], h[N], idx;

int deg[N];

int cnt, order[N];

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
        int son;
        while (cin >> son, son) {
            add(i, son);
            deg[son] ++;
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

        for (int i = h[t]; ~i; i = ne[i]) {
            int son = e[i];
            if (-- deg[son] == 0) {
                q.push(son);
            }
        }
    }


    for (int i = 1; i <= cnt; i ++) {
        cout << order[i] << " ";
    }

    return 0;
}
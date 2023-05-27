/**
 * P3366 洛谷模板题 最小生成树
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int N = 5050, M = 2e5 + 10;

struct Edge {
    int src;
    int dst;
    int w;
} edges[M];

int p[N];

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }

    return p[x];
}

void merge(int u, int v) {
    u = find(u), v = find(v);
    p[v] = u;
}

bool cmp(Edge& a, Edge& b) {
    return a.w < b.w;
}

int main() {
    int n, m;

    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        p[i] = i;
    }

    for (int i = 1; i <= m; i ++) {
        int x, y, z;
        cin >> x >> y >> z;
        edges[i] = {x, y, z};
    }

    sort(edges + 1, edges + 1 + m, cmp);

    int sum = 0;
    int cnt = 0;

    for (int i = 1; i <= m; i ++) {
        Edge& e = edges[i];
        int s = e.src, d = e.dst, w = e.w;
        if (find(s) == find(d)) {
            continue;
        }
        sum += w;
        cnt ++;
        merge(s, d);
    }

    if (cnt != n - 1) {
        cout << "orz" << endl;
    } else {
        cout << sum << endl;
    }


    return 0;
}
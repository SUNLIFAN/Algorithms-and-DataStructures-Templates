#include <iostream>
#include <algorithm>

using namespace std;

const int N = 550, M = N * N;

int p[N];

struct Edge {
    int s;
    int d;
    int w;
} edges[M];

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



bool cmp(Edge& e1, Edge& e2) {
    return e1.w < e2.w;
}

int main() {
    int a, b;
    cin >> a >> b;

    int cnt = 0;

    for (int i = 1; i <= b; i ++) {
        p[i] = i;
    }

    for (int i = 1; i <= b; i ++) {
        edges[++ cnt] = {0, i, a}; 
    }

    for (int i = 1; i <= b; i ++) {
        for (int j = 1; j <= b; j ++) {
            int x;
            cin >> x;
            if (x == 0) {
                continue;
            }
            if (i > j) {
                continue;
            }
            edges[++ cnt] = {i, j, x};
        }
    }

    int ans = 0;

    sort(edges + 1, edges + 1 + cnt, cmp);

    for (int i = 1; i <= cnt; i ++) {
        Edge& e = edges[i];
        int s = e.s, d = e.d, w = e.w;
        if (find(s) == find(d)) {
            continue;
        }
        ans += w;
        merge(s, d);
    }

    for (int i = 1; i <= b; i ++) {
        if (p[i] == i) {
            ans += a;
        }
    }

    cout << ans << endl;

    return 0;
}
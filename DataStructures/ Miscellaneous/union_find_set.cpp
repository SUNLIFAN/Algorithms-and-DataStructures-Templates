/**
 * P3367 并查集模板题
*/

#include <iostream>

using namespace std;

const int N = 1e4 + 10;

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

int main() {
    int n, m;

    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        p[i] = i;
    }

    while (m --) {
        int z, x, y;

        cin >> z >> x >> y;

        if (z == 1) {
            merge(x, y);
        } else {
            if (find(x) == find(y)) {
                cout << "Y" << endl;
            } else {
                cout << "N" << endl;
            }
        }
    }

    return 0;
}
/**
 * 洛谷 B3647 Floyd 模板题
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int d[N][N];

int main() {

    int n, m;

    cin >> n >> m;

    memset(d, 0x3f, sizeof d);


    for (int i = 1; i <= n; i ++) {
        d[i][i] = 0;
    }

    for (int i = 1; i <= m; i ++) {
        int u,v,w;
        cin >> u >> v >> w;
        d[u][v] = d[v][u] = w;
    }

    for (int k = 1; k <= n; k ++) {
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= n; j ++) {
                if (d[i][k] != INF && d[k][j] !=INF) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cout << d[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}
/**
 * P3865 ST 表模板题
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

const int N = 1e5 + 10;

int st[N][20], a[N], log_[N];

int query(int l, int r) {
    int k = log_[r - l + 1];

    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {

    int n, m;

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i ++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i ++) {
        st[i][0] = a[i];
        log_[i] = log2(i);
    }

    for (int j = 1; j < 20; j ++) {
        for (int i = 1; i + (1 << j) <= n + 1; i ++) {
            st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }

    while (m --) {
        int l, r;
        scanf("%d%d", &l, &r);

        printf("%d\n", query(l, r));
    }

    return 0;
}
/**
 * P3374 树状数组模板题
*/
#include <iostream>

using namespace std;

const int N = 5e5 + 10;

int pre[N], c[N];

int lowbit(int x) {
    return x & (-x);
}

int preSum(int r) {
    int s = 0;
    for (int i = r; i > 0; i -= lowbit(i)) {
        s += c[i];
    }
    return s;
}

int sum(int l, int r) {
    return preSum(r) - preSum(l-1);
}

void add(int x, int y, int n) {
    for (int i = x; i <= n; i += lowbit(i)) {
        c[i] += y;
    }
}

void build(int n) {
    for (int i = 1; i <= n; i ++) {
        pre[i] += pre[i-1];
        c[i] = pre[i] - pre[i - lowbit(i)];
    }
}

int main() {
    int n, m;

    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        cin >> pre[i];
    }

    build(n);

    for (int i = 1; i <= m; i ++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            add(x, y, n);
        } else {
            int l, r;
            cin >> l >> r;
            cout << sum(l, r) << endl;
        }
    }

    return 0;
}
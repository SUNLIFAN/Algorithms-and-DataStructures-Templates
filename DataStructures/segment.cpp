/**
 * P2357 分块模板题
*/

#include <iostream>
#include <cmath>

using namespace std;

const int N = 2e5 + 10;

using i64 = long long;

i64 sum[N], lazy[N], a[N];

int id[N];

int b;

i64 query(int l, int r) {
    i64 ans = 0;
    for (int i = l; i <= min(r, b * id[l]); i ++) {
        ans = ans + a[i] + lazy[id[i]];
    }

    if (id[l] == id[r]) {
        return ans;
    }

    for (int i = r; i >= (id[r] - 1) * b + 1; i --) {
        ans = ans + a[i] + lazy[id[i]];
    }

    for (int i = id[l] + 1; i <= id[r] - 1; i ++) {
        ans = ans + sum[i];
    }

    return ans;
}

void update(int l, int r, i64 val) {
    for (int i = l; i <= min(r, id[l] * b); i ++) {
        a[i] += val;
        sum[id[i]] += val;
    }

    if (id[l] == id[r]) {
        return;
    }

    for (int i = r; i >= (id[r] - 1) * b + 1; i --) {
        a[i] += val;
        sum[id[i]] += val;
    }

    for (int i = id[l] + 1; i <= id[r] - 1; i ++) {
        sum[i] = sum[i] + val * b;
        lazy[i] += val;
    }
}

int main() {
    int n, f;

    cin >> n >> f;

    b = sqrt(n);

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        id[i] = (i - 1) / b + 1;
        sum[id[i]] += a[i];
    }

    while (f --) {
        int op, l, r, k;
        cin >> op;

        if (op == 1) {
            cin >> l >> r >> k;
            update(l, r, k);
        } else if (op == 2) {
            cin >> k;
            update(1, 1, k);
        } else if (op == 3) {
            cin >> k;
            update(1, 1, -k);
        } else if (op == 4){
            cin >> l >> r;
            cout << query(l, r) << endl;
        } else {
            cout << query(1, 1) << endl;
        }
    }

    return 0;
}
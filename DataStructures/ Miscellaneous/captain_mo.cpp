#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

using i64 = long long;

const int N = 5e4 + 10;

i64 sum, cnt[N];

i64 num[N], deno[N];

i64 c[N];

int B;

struct query {
    int l;
    int r;
    int id;
} querys[N];

bool cmp(query& a, query& b) {
    if (a.l / B != b.l / B) {
        return a.l < b.l;
    }

    return (a.l / B) & 1 ? a.r < b.r : a.r  >b.r;
}

i64 gcd(i64 a, i64 b) {
    return !b ? a : gcd(b, a % b);
}

void add(i64 i) {
    sum += cnt[i];
    cnt[i] ++;
}

void del(i64 i) {
    cnt[i] --;
    sum -= cnt[i];
}

int main() {
    int n, m;
    cin >> n >> m;

    B = sqrt(n);

    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
    }

    for (int i = 1; i <= m; i ++) {
        int l, r;
        cin >> l >> r;
        querys[i] = {l, r, i};
    }

    sort(querys + 1, querys + 1 + m, cmp);

    for (int i = 1, l = 1, r = 0; i <= m; i ++) {
        if (querys[i].l == querys[i].r) {
            num[querys[i].id] = 0, deno[querys[i].id] = 1;
            continue;
        }

        while (l > querys[i].l) add(c[--l]);
        while (r < querys[i].r) add(c[++ r]);
        while (l < querys[i].l) del(c[l ++]);
        while (r > querys[i].r) del(c[r --]);
        num[querys[i].id] = sum;
        deno[querys[i].id] = (i64)(r - l + 1) * (r - l) / 2;
    }

    for (int i = 1; i <= m; i ++) {
        if (num[i] != 0) {
            i64 d = gcd(num[i], deno[i]);
            num[i] /= d, deno[i] /= d;
            cout << num[i] << "/" << deno[i] << endl;
        } else {
            cout << "0/1" << endl;
        }
    }
    
    return 0;
}
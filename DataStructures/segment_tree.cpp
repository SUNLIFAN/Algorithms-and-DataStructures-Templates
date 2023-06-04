/**
 * P3373 线段树模板题
 * 带懒标记
*/
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

using i64 = long long;

i64 s[N << 2], add_lazy[N << 2], mul_lazy[N << 2];

i64 a[N];

int n, m, t;

void pushup(int p) {
    s[p] = (s[p * 2] + s[p * 2 + 1]) % t;
}

void pushdown(int p, int l, int r) {
    mul_lazy[p * 2] = mul_lazy[p * 2] * mul_lazy[p] % t;
    mul_lazy[p * 2 + 1] = mul_lazy[p * 2 + 1] * mul_lazy[p] % t;
    add_lazy[p * 2] = add_lazy[p * 2] * mul_lazy[p] % t;
    add_lazy[p * 2 + 1] = add_lazy[p * 2 + 1] * mul_lazy[p] % t;
    add_lazy[p * 2] = (add_lazy[p * 2] + add_lazy[p]) % t;
    add_lazy[p * 2 + 1] = (add_lazy[p * 2 + 1] + add_lazy[p]) % t;
    int mid = (l + r) >> 1;
    s[p * 2] = (s[p * 2] * mul_lazy[p] % t + add_lazy[p] * (mid - l + 1) % t) % t;
    s[p * 2 + 1] = (s[p * 2 + 1] * mul_lazy[p] % t + add_lazy[p] * (r - mid) % t) % t;
    mul_lazy[p] = 1;
    add_lazy[p] = 0;
}

void modify_mul(int p, int l, int r, int x, int y, int v) {
    if (x <= l && y >= r) {
        mul_lazy[p] = mul_lazy[p] * v % t;
        add_lazy[p] =add_lazy[p] * v % t;
        s[p] *= v % t;
        return;
    }
    
    pushdown(p, l ,r);
    
    int mid = (l + r) >> 1;
    
    if (x <= mid) {
        modify_mul(p * 2, l, mid, x, y, v);
    }
    
    if (y > mid) {
        modify_mul(p * 2 + 1, mid + 1, r, x, y, v);
    }
    
    pushup(p);
}

void modify_add(int p, int l, int r, int x, int y, int v) {
    if (x <= l && y >= r) {
        add_lazy[p] = (add_lazy[p] + v) % t;
        s[p] = (s[p] + v * (r - l + 1) % t) % t;
        return;
    }
    
    pushdown(p, l, r);
    
    int mid = (l + r) >> 1;
    if (x <= mid) {
        modify_add(p * 2, l, mid, x, y, v);
    }
    
    if (y > mid) {
        modify_add(p * 2 + 1, mid + 1, r, x, y, v);
    }
    
    pushup(p);
}

int query(int p, int l, int r, int x, int y) {
    if (x <= l && y >= r) {
        return s[p];
    }
    
    pushdown(p, l, r);
    
    int mid = (l + r) >> 1;
    
    i64 ret = 0;
    
    if (x <= mid) {
        ret = (ret + query(p * 2, l, mid, x, y)) % t;
    }
    
    if (y > mid) {
        ret = (ret + query(p * 2 + 1, mid + 1, r, x, y)) % t;
    }
    
    return ret;
}

void build(int p, int l, int r) {
    add_lazy[p] = 0, mul_lazy[p] = 1;
    if (l == r) {
        s[p] = a[l];
        return;
    }
    
    int mid = (l + r) >> 1;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    pushup(p);
}

int main() {
    
    cin >> n >> m >> t;
    
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    
    build(1, 1, n);
    
    int op, x, y, k;
    
    while (m --) {
        cin >> op >> x >> y;
        
        if (op == 1) {
            cin >> k;
            modify_mul(1, 1, n, x, y, k);
        } else if (op == 2) {
            cin >> k;
            modify_add(1, 1, n, x, y, k);
        } else {
            cout << query(1, 1, n, x, y) << endl;
        }
        
    }
    
    return 0;
}
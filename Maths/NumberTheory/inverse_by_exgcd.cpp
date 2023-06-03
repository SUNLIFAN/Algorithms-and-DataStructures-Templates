/**
 * Acwng 扩展欧几里德算法求解线性同余方程
 * 可以用于求逆元
 * 求逆元可以看成解同余方程 ax = 1 (mod p)
*/

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

using i64 = long long;

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }

    i64 d = exgcd(b, a % b, x, y);

    i64 t  = x;

    x = y;

    y = t - a / b * y;

    return d;
}

int main() {

    int n;

    i64 a, b, m;

    cin >> n;

    while (n --) {
        cin >> a >> b >> m;
        i64 x, y;
        i64 d = exgcd(a, -m, x, y);

        if (b % d != 0) {
            cout << "impossible" << endl;
        } else {
            x = x * b / d % m;
            cout << x << endl;
        }
    }

    return 0;
}
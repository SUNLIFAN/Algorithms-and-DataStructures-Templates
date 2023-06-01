/**
 * Acwing 876 快速幂求乘法逆元
 * 由于模数 P 为质数，如果 a,p 互质，
 * 那么逆元存在，可以用费马小定理
*/
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

using i64 = long long;

inline i64 qpower(i64 a, i64 b, i64 p) {
    i64 res = 1;
    while (b != 0) {
        if (b & 1) {
            res = res * a % p;
        }
        b >>= 1;
        a = a * a % p;
    }

    return res % p;
}

inline i64 inv(i64 a, i64 p) {
    return qpower(a, p-2, p);
}

int main() {
    int n;
    cin >> n;
    while (n --) {
        i64 a, p;
        cin >> a >> p;
        if (a % p == 0) {
            printf("impossible\n");
        } else {
            printf("%lld\n", inv(a, p));
        }
    }
    return 0;
}
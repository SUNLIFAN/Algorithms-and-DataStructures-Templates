/**
 * P3811 求 1 - n 模 P 意义下的逆元
 * 线性求 1- n 逆元模板题
 * 注意：在逆元不存在时，inv[i] 的值是未定义的。
*/
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int N = 3e6 + 10;

using i64 = long long;

i64 inv[N];

int main() {
    i64 n, p;
    cin >> n >> p;
    inv[1] = 1;
    for (int i = 2; i <= n; i ++) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }

    for (int i = 1; i <= n; i ++) {
        printf("%lld\n", inv[i]);
    }

    return 0;
}
/**
 * JSK T1984 提交于 vjudge
 * 求组合数模板
 * 公式法 在模数为质数的时候用
*/
#include <iostream>
#include <algorithm>

using namespace std;

using i64 = long long;

const int N = 2020, MOD = 1e9 + 7;

i64 qpower(i64 a, i64 b, i64 p) {
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

i64 fact[N], invFact[N];

void init() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i <= 2020; i ++) {
        fact[i] = fact[i-1] * i % MOD;
        invFact[i] = qpower(fact[i], MOD-2, MOD);
    }
}

i64 c(int n, int m, int p) {
    return fact[n] * invFact[m] % p * invFact[n-m] % p;
}

int main() {

    init();

    int n, m;

    cin >> n >> m;

    cout << c(n, m, MOD) << endl;
    
    return 0;
}
/**
 * P1226 快速幂模板题
*/

#include <iostream>
#include <algorithm>

using namespace std;

using i64 = long long;

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

int main() {
    i64 a, b, p;
    cin >> a >> b >> p;

    cout << a << "^" << b << " mod " << p << "=" << qpower(a, b, p) << endl;

    return 0;
}
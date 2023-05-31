/**
 * Acwing 877 扩展欧几里德算法模板题
*/

#include <iostream>
#include <algorithm>

using namespace std;

using i64 = long long;

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }

    i64 d = exgcd(b, a % b, x, y);

    i64 t = x;
    x = y;
    y = t - a / b * y;

    return d;
}

int main() {
    int n;
    cin >> n;
    while (n --) {
        i64 a, b, x, y;
        cin >> a >> b;
        exgcd(a, b, x, y);
        cout << x << " " << y << endl;
    }
    return 0;
}
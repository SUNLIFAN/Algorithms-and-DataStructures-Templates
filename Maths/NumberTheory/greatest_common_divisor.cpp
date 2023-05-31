/**
 * 欧几里德算法求最大公约数模板
 * bailian OJ 3248 提交在 vjudge 上
*/
#include <iostream>

using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int x, y;
    while (cin >> x >> y) {
        cout << gcd(x, y) << endl;
    }
    return 0;
}
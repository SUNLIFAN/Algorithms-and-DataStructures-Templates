/**
 * 杨辉三角 预处理组合数
 * P5732
*/

#include <iostream>

using namespace std;

const int N = 22;

int c[N][N];

void init(int n) {
    c[0][0] = 1;
    for (int i = 1; i <= n - 1; i ++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j ++) {
            c[i][j] = c[i-1][j] + c[i-1][j-1];
        }
    }
}

int main() {
    int n;
    cin >> n;
    init(n);

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j <= i; j ++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
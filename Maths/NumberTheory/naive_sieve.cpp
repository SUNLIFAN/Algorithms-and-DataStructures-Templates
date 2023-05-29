/**
 * P5736 朴素筛模板题
 * 对于每个素数，筛掉他们的倍数
*/
#include <cstdio>

using namespace std;

const int N = 1e5 + 10;

bool st[N];

int primes[N], a[N];

int main() {

    int n, cnt = 0;
    
    scanf("%d", &n);

    for (int i = 1; i <= n; i ++) {
        scanf("%d", &a[i]);
    }

    st[1] = true;

    for (int i = 2; i <= 1e5 + 10; i ++) {
        if (!st[i]) {
            primes[++ cnt] = i;
        } else {
            continue;
        }

        for (int j = i + i; j <= 1e5 + 10; j += i) {
            st[j] = true;
        }
    }

    for (int i = 1; i <= n; i ++) {
        if (!st[a[i]]) {
            printf("%d ", a[i]);
        }
    }

    return 0;
}
#include <iostream>

using namespace std;

const int N = 1e8 + 10;

int primes[N];

bool st[N];

int main() {
    int n, q, cnt = 0;
    scanf("%d%d", &n, &q);

    for (int i = 2; i <= n; i ++) {
        if (!st[i]) {
            primes[++ cnt] = i;
        }

        for (int j = 1; j <= cnt && primes[j] <= n / i; j ++) {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }

    while(q --) {
        int k;
        scanf("%d", &k);
        printf("%d\n", primes[k]);
    }
    return 0;
}
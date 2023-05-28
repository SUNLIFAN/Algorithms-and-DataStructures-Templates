/**
 * 洛谷 P2330
 * 繁忙的都市
 * MST 裸题，题意等价于求这个图的最小生成树
 * 简证如下: 
 * 由于要使得边最少，且连通，因此选择的子图一定是一棵树
 * 又由于要使得最大的边的分数最小，假设标准答案中某条边不在最小生成树里
 * 把这条边拿掉，会变成两个连通分量，由于这条边不在最小生成树里，因此这肯定不是一条
 * 桥边，还存在其他边把两个连通分量连在一起，如果这条边不是当前最大分数的边，那么可以把这条边换成
 * 最小生成树中连接这两个连通分量的边。如果这条边是当前的最大分数的边，那么换成最小生成树中的边之后，
 * 由标准答案的性质得，最大分数边应该变大或者不变，因此换进来的这条 MST 中的边的分数
 * 和换出去的边一样，因此这仍然是一个标准答案。如此替换直到最后所有边都在 MST 中。
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 330, M = 2e5 + 10;

int e[M], ne[M], w[M], h[N], idx;

bool st[N];

int dist[N];

void add(int x, int y, int z) {
    e[idx] = y;
    ne[idx] = h[x];
    w[idx] = z;
    h[x] = idx ++;
}

int main() {

    int n, m;

    cin >> n >> m;

    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i ++) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
        add(y, x, z);
    }

    int maxv = 0;

    memset(dist, 0x3f, sizeof dist);

    dist[1] = 0;

    bool fail = false;

    for (int i = 1; i <= n; i ++) {
        int t = -1;
        for (int j = 1; j <= n; j ++) {
            if (!st[j] && (t == -1 || dist[j] < dist[t])) {
                t = j;
            }
        }

        if (dist[t] == 0x3f3f3f3f) {
            fail = true;
            break;
        }

        st[t] = true;
        maxv = max(maxv, dist[t]);

        for (int k = h[t]; ~k; k = ne[k]) {
            int son = e[k];
            dist[son] = min(dist[son], w[k]);
        }
    }

    cout << n - 1 << " " << maxv << endl;

    return 0;
}
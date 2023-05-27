/**
 * 洛谷 P3243
 * 满足拓扑序的前提优先考虑 1, 2, 3, ..., n 等价于
 * 在反图上求拓扑序，队列用大根堆，最后输出拓扑逆序
*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;


int e[N], ne[N], h[N], idx;

int order[N], cnt;

int deg[N];


void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void solve() {
    int n, m;
    cin >> n >> m;
    memset(h, -1, sizeof h);
    idx = 0;
    cnt = 0;
    memset(deg, 0, sizeof deg);
    
    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        add(y, x);
        deg[x] ++;
    }
    
    priority_queue<int> pq;
    
    for (int i = 1; i <= n; i ++) {
        if (!deg[i]) {
            pq.push(i);
        }
    }
    
    while (!pq.empty()) {
        int t = pq.top();
        pq.pop();
        
        order[++ cnt] = t;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (--deg[j] == 0) {
                pq.push(j);
            }
        }
    }
    
    if (cnt != n) {
        cout << "Impossible!" << endl;
    } else {
        for (int i = cnt; i >= 1; i --) {
            cout << order[i] <<  " ";
        }
        
        cout << endl;
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
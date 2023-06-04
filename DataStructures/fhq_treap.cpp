/**
 * P3369 平衡树模板题
 * FHQ Treap 写法
*/
#include <iostream>
#include <algorithm>
#include <cstdlib>
#define lc tr[p].ch[0]
#define rc tr[p].ch[1]
using namespace std;

const int N = 1e5 + 10, INF = 1e9;

struct Node {
    int ch[2];
    int key;
    int pri;
    int size;
} tr[N];

int root, idx;

int newNode(int key) {
    tr[++ idx].key = key;
    tr[idx].pri = rand();
    tr[idx].size = 1;
    return idx;
}

void pushup(int p) {
    tr[p].size = tr[lc].size + tr[rc].size + 1;
}

void splitByKey(int p, int key, int &x, int& y) {
    if (!p) {
        x = y = 0;
        return;
    }
    
    if (tr[p].key <= key) {
        x = p;
        splitByKey(rc, key, rc, y);
    } else {
        y = p;
        splitByKey(lc, key, x, lc);
    }
    
    pushup(p);
}

int merge(int x, int y) {
    if (!x || !y) {
        return x + y;
    }
    if (tr[x].pri > tr[y].pri) {
        tr[x].ch[1] = merge(tr[x].ch[1], y);
        pushup(x);
        return x;
    } else {
        tr[y].ch[0] = merge(x, tr[y].ch[0]);
        pushup(y);
        return y;
    }
}

void insert(int& p, int key) {
    int x = 0, y = 0;
    splitByKey(p, key, x, y);
    p = merge(merge(x, newNode(key)), y);
}

void erase(int& p, int key) {
    if (!p) {
        return;
    }
    int x = 0, y = 0, z = 0;
    splitByKey(p, key, x, z);
    splitByKey(x, key-1, x, y);
    y = merge(tr[y].ch[0], tr[y].ch[1]);
    p = merge(merge(x, y), z);
}

int getKth(int p, int k) {
    if (!p) {
        return INF;
    }
    
    if (k == tr[lc].size + 1) {
        return tr[p].key;
    } else if (k > tr[lc].size + 1) {
        return getKth(rc, k - tr[lc].size - 1);
    } else {
        return getKth(lc, k);
    }
}

int getRank(int &p, int key) {
    int x, y;
    splitByKey(p, key-1, x, y);
    int ret = tr[x].size + 1;
    p = merge(x, y);
    return ret;
}

int pred(int& p, int key) {
    if (!p) {
        return -INF;
    }
    
    int x, y;
    splitByKey(p, key-1, x, y);
    int cur = x;
    if (!cur) {
        return -INF;
    }
    
    while (tr[cur].ch[1]) {
        cur = tr[cur].ch[1];
    }
    
    p = merge(x, y);
    
    return tr[cur].key;
}

int succ(int& p, int key) {
    if (!p) {
        return INF;
    }
    
    int x, y;
    splitByKey(p, key, x, y);
    int cur = y;
    if (!cur) {
        return INF;
    }
    
    while (tr[cur].ch[0]) {
        cur = tr[cur].ch[0];
    }
    
    p = merge(x, y);
    
    return tr[cur].key;
}

int main() {
    int n;

    cin >> n;

    int opt, x;

    for (int i = 1; i <= n; i ++) {
        cin >> opt >> x;
        if (opt == 1) {
            insert(root, x);
        } else if (opt == 2) {
            erase(root, x);
        } else if (opt == 3) {
            cout << getRank(root, x)  << endl;
        } else if (opt == 4) {
            cout << getKth(root, x) << endl;
        } else if (opt == 5) {
            cout << pred(root, x) << endl;
        } else {
            cout << succ(root, x) << endl;
        }
    }

    return 0;
}
/**
 * P3369 平衡树模板题
 * 普通 Treap 写法
*/

#include <iostream>
#include <cstdlib>
#include <algorithm>
#define lc ch[0]
#define rc ch[1]

using namespace std;

const int N = 1e5 + 10, INF = 1e8;

int root, idx;

struct TreapNode {
    int ch[2];
    int siz;
    int cnt;
    int key;
    int pri;
} tr[N];

void pushup(int p) {
    tr[p].siz = tr[tr[p].lc].siz + tr[tr[p].rc].siz + tr[p].cnt;
}

int getNode(int key) {
    ++ idx;
    tr[idx].siz = tr[idx].cnt = 1;
    tr[idx].key = key;
    tr[idx].pri = rand();

    return idx;
}

void rotate(int& p, int d) {
    int t = tr[p].ch[d];
    tr[p].ch[d] = tr[t].ch[!d], tr[t].ch[!d] = p;
    p = t;
    pushup(tr[p].ch[!d]), pushup(p);
}

void build() {
    getNode(-INF), getNode(INF);
    root = 1;
    tr[1].rc = 2;
    pushup(root);
    if (tr[2].pri > tr[1].pri) {
        rotate(root, 1);
    }
}

void insert(int& p, int key) {
    if (!p) {
        p = getNode(key);
    } else if (tr[p].key == key) {
        tr[p].cnt ++;
    } else if (key < tr[p].key) {
        insert(tr[p].lc, key);
        if (tr[tr[p].lc].pri > tr[p].pri) {
            rotate(p, 0);
        }
    } else {
        insert(tr[p].rc, key);
        if (tr[tr[p].rc].pri > tr[p].pri) {
            rotate(p, 1);
        }
    }

    pushup(p);
}


void erase(int& p, int key) {
    if (!p) {
        return;
    }

    if (tr[p].key == key) {
        if (tr[p].cnt > 1) {
            tr[p].cnt --;
        } else if (tr[p].lc || tr[p].rc) {
            if (!tr[p].rc || tr[tr[p].lc].pri > tr[tr[p].rc].pri) {
                rotate(p, 0);
                erase(tr[p].rc, key);
            } else {
                rotate(p, 1);
                erase(tr[p].lc, key);
            }
        } else {
            p = 0;
        }
    } else if (key < tr[p].key) {
        erase(tr[p].lc, key);
    } else {
        erase(tr[p].rc, key);
    }

    pushup(p);
}


int getRank(int p, int key) {
    if (!p) {
        return 0;
    }

    if (tr[p].key == key) {
        return tr[tr[p].lc].siz + 1;
    } else if (key < tr[p].key) {
        return getRank(tr[p].lc, key);
    } else {
        return tr[tr[p].lc].siz + tr[p].cnt + getRank(tr[p].rc, key);
    }
}

int getKth(int p, int rk) {
    if (!p) {
        return INF;
    }

    if (tr[tr[p].lc].siz >= rk) {
        return getKth(tr[p].lc, rk);
    } else if (tr[tr[p].lc].siz + tr[p].cnt >= rk) {
        return tr[p].key;
    } else {
        return getKth(tr[p].rc, rk - tr[tr[p].lc].siz - tr[p].cnt);
    }
}

int pred(int p, int key) {
    if (!p) {
        return -INF;
    }

    if (tr[p].key < key) {
        return max(tr[p].key, pred(tr[p].rc, key));
    } else {
        return pred(tr[p].lc, key);
    }
}

int succ(int p, int key) {
    if (!p) {
        return INF;
    }

    if (tr[p].key > key) {
        return min(tr[p].key, succ(tr[p].lc, key));
    } else {
        return succ(tr[p].rc, key);
    }
}

int main() {
    int n;

    cin >> n;

    build();

    int opt, x;

    for (int i = 1; i <= n; i ++) {
        cin >> opt >> x;
        if (opt == 1) {
            insert(root, x);
        } else if (opt == 2) {
            erase(root, x);
        } else if (opt == 3) {
            cout << getRank(root, x) - 1 << endl;
        } else if (opt == 4) {
            cout << getKth(root, x + 1) << endl;
        } else if (opt == 5) {
            cout << pred(root, x) << endl;
        } else {
            cout << succ(root, x) << endl;
        }
    }

    return 0;
}
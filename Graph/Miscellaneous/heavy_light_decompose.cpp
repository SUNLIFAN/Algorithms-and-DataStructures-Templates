/**
 * P3384 轻重链剖分 模板题
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

using i64 = long long;

int dep[N], fa[N], son[N], e[N << 1], ne[N << 1], h[N], idx;

int id[N], w[N], siz[N], top[N], dfsc, a[N];

i64 lazy[N << 2], tr[N << 2];

int root;

int P;
// 树链剖分初始化代码
void add(int x, int y) {
    e[idx] = y;
    ne[idx] = h[x];
    h[x] = idx ++;
}

void dfs1(int u, int fat, int d) {
    dep[u] = d, fa[u] = fat;
    siz[u] = 1;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        
        if (v == fat) {
            continue;
        }

        dfs1(v, u, d + 1);

        siz[u] += siz[v];

        if (siz[v] > siz[son[u]]) {
            son[u] = v;
        }
    }
}

void dfs2(int u, int topf) {
    top[u] = topf;
    id[u] = ++ dfsc;
    a[dfsc] = w[u];

    if (!son[u]) {
        return;
    }

    dfs2(son[u], topf);

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fa[u] || v == son[u]) {
            continue;
        }

        dfs2(v, v);
    }
}

void init() {
    dfs1(root, 0, 1);
    dfs2(root, root);
}

// 线段树代码
void pushup(int u) {
    tr[u] = (tr[u << 1] + tr[u << 1 | 1]) % P;
}

void pushdown(int u, int l, int r) {
    int mid = l + r >> 1;
    tr[u << 1] = (tr[u << 1] + (mid - l + 1) * lazy[u] % P) % P;
    lazy[u << 1] = (lazy[u << 1] + lazy[u]) % P;
    tr[u << 1 | 1] = (tr[u << 1 | 1] + (r - mid) * lazy[u] % P) % P;
    lazy[u << 1 | 1] = (lazy[u << 1 | 1] + lazy[u]) % P;
    lazy[u] = 0;
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = a[l];
        return;
    }

    int mid = (l + r) >> 1;
    
    build(u << 1, l, mid);
    
    build(u << 1 | 1, mid + 1, r);
    
    pushup(u);
}

i64 query(int u, int l, int r, int x, int y) {
    if (l >= x && r <= y) {
        return tr[u] % P;
    }

    i64 ans = 0;

    pushdown(u, l, r);

    int mid = (l + r) >> 1;
    if (x <= mid) {
        ans = (ans + query(u << 1, l, mid, x, y)) % P;
    }

    if (y > mid) {
        ans = (ans + query(u << 1 | 1, mid + 1, r, x, y)) % P;
    }

    return ans;
}

void update(int u, int l, int r, int x, int y, i64 v) {
    if (l >= x && r <= y) {
        lazy[u] = (lazy[u] + v) % P;
        tr[u] = (tr[u] + (r - l + 1) * v % P) % P;
        return;
    }

    pushdown(u, l, r);

    int mid = l + r >> 1;
    
    if (x <= mid) {
        update(u << 1, l, mid, x, y, v);
    }

    if (y > mid) {
        update(u << 1 | 1, mid + 1, r, x, y, v);
    }

    pushup(u);
}

// 树链剖分处理树上修改和查询代码

i64 queryPath(int u, int v) {
    i64 ans = 0;

    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        ans = (ans + query(1, 1, dfsc, id[top[u]], id[u])) % P;
        u = fa[top[u]];
    }

    if (dep[u] > dep[v]) {
        swap(u, v);
    }

    ans = (ans + query(1, 1, dfsc, id[u], id[v])) % P;

    return ans;
}

i64 querySubTree(int u) {
    return query(1, 1, dfsc, id[u], id[u] + siz[u] - 1);
}

void updatePath(int u, int v, i64 val) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        update(1, 1, dfsc, id[top[u]], id[u], val);
        u = fa[top[u]];
    }

    if (dep[u] > dep[v]) {
        swap(u, v);
    }

    update(1, 1, dfsc, id[u], id[v], val);
}

void updateSubTree(int u, i64 val) {
    update(1, 1, dfsc, id[u], id[u] + siz[u] - 1, val);
}

int main() {
    int n, m;

    cin >> n >> m >> root >> P;

    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i ++) {
        cin >> w[i];
    }

    for (int i = 1; i <= n - 1; i ++) {
        int x, y;
        cin >> x >> y;
        add(x, y), add(y, x);
    }

    init();

    build(1, 1, dfsc);

    while (m --) {
        int x, y, z;
        int op;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            updatePath(x, y, z);
        } else if (op == 2) {
            cin >> x >> y;
            cout << queryPath(x, y) << endl;
        } else if (op == 3) {
            cin >> x >> z;
            updateSubTree(x, z);
        } else {
            cin >> x;
            cout << querySubTree(x) << endl;
        }
    }

    return 0;
}
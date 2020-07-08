#include <bits/stdc++.h>

using namespace std;
const int N = 1001, M = 2 * N + N;
typedef long long ll;

struct ADJ {
    int head[N], nxt[M], to[M], ne;

    void init(int n) {
        memset(head + 1, 0, n * sizeof head[0]);
        ne = 0;
    }

    void add_edge(int u, int v) {
        nxt[++ne] = head[u];
        to[ne] = v;
        head[u] = ne;
    }

    void add_biedge(int u, int v) {
        add_edge(u, v), add_edge(v, u);
    }
} adj;

#define neigh(adj, u, e, v)for(int e=adj.head[u], v; v=adj.to[e], e; e=adj.nxt[e])

int sz[N], dep[N], dfsAt[M], dfsOf[N], dfst;

void ewalk(int u, int p) {
    dfsAt[dfsOf[u] = dfst++] = u;
    sz[u] = 1;
    neigh(adj, u, e, v) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        ewalk(v, u);
        sz[u] += sz[v];
        dfsAt[dfst++] = u;
    }
}

int lg[M];
const int lgM = (int) ceil(log2(M));
int table[M][lgM];

#define ACC(i) dep[dfsAt[i]]

void SPT() {
    lg[0] = -1;
    for (int i = 0; i < dfst; ++i) {
        lg[i + 1] = lg[i] + !(i & (i + 1)); //i is one less than a power of two
        table[i][0] = i;
    }
    for (int j = 1; (1 << j) < dfst; ++j) {
        for (int i = 0; i + (1 << j) < dfst; ++i) {
            int lf = table[i][j - 1];
            int rt = table[i + (1 << (j - 1))][j - 1];
            table[i][j] = ACC(lf) < ACC(rt) ? lf : rt;
        }

    }
}

int RMQ(int a, int b) {
    int l = lg[b - a + 1];

    int lf = table[a][l];
    int rt = table[b - (1 << l) + 1][l];
    return ACC(lf) < ACC(rt) ? lf : rt;
}

int LCA(int u, int v) {
    int a = dfsOf[u], b = dfsOf[v];
    if (a > b) swap(a, b);
    return dfsAt[RMQ(a, b)];
}

int ts, n, m, u, v;

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    scanf("%d", &ts);
    for (int vid = 1; vid <= ts; ++vid) {
        printf("Case %d:\n", vid);
        scanf("%d", &n);
        adj.init(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &m);
            while (m--) {
                scanf("%d", &v);
                adj.add_edge(i + 1, v);
            }
        }
        dep[1] = dfst = 0;
        ewalk(1, -1);
        SPT();
        scanf("%d", &m);
        while (m--) {
            scanf("%d%d", &u, &v);
            printf("%d\n", LCA(u, v));
        }
    }

}

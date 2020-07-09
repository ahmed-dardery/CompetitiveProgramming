#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 2 * 61, M = 4 * N + 2 * N * N;

struct ADJ {
    int head[N], nxt[M], from[M], to[M], n, ne;

    void add_edge(int f, int t) {
        from[ne] = f;
        to[ne] = t;
        nxt[ne] = head[f];
        head[f] = ne++;
    }

    void init(int nNodes) {
        ne = 0;
        n = nNodes;
        memset(head, -1, n * sizeof head[0]);
    }
};

struct SCC {
    ADJ adj;

    int visidx[N], lowlink[N], cmp[N], stck[N], stcksz, cmpid, dfst;

    void operator()() {
        int n = adj.n;
        memset(visidx, -1, n * sizeof visidx[0]);
        memset(lowlink, -1, n * sizeof lowlink[0]);
        memset(cmp, -1, n * sizeof cmp[0]);
        cmpid = dfst = stcksz = 0;
        for (int i = 0; i < n; i++) {
            if (visidx[i] == -1)
                dfs(i);
        }
    }

    void dfs(int u) {
        visidx[u] = lowlink[u] = dfst++;
        stck[stcksz++] = u;

        for (int e = adj.head[u], v; ~e && (v = adj.to[e], 1); e = adj.nxt[e]) {
            if (visidx[v] == -1) {
                dfs(v);
                lowlink[u] = min(lowlink[u], lowlink[v]);
            } else if (cmp[v] == -1)
                lowlink[u] = min(lowlink[u], visidx[v]);
        }
        if (lowlink[u] == visidx[u]) {
            do {
                cmp[stck[--stcksz]] = cmpid;
            } while (stck[stcksz] != u);
            ++cmpid;
        }
    }
};

struct TwoSat {
    SCC scc;

    void init(int n) {
        scc.adj.init(2 * n);
    }

    void force(int a, bool val) {
        add_or(a, val, a, val);
    }

    void add_or(int a, bool aVal, int b, bool bVal) {
        scc.adj.add_edge(2 * a ^ aVal, 2 * b ^ !bVal);
        scc.adj.add_edge(2 * b ^ bVal, 2 * a ^ !aVal);
    }

    void add_xor(int a, bool aVal, int b, bool bVal) {
        add_or(a, aVal, b, bVal);
        add_or(a, !aVal, b, !bVal);
    }

    int value[N], nodes[N];

    bool operator[](int i) {
        return value[2 * i];
    }

    bool operator()() {
        int n = scc.adj.n;

        scc();
        for (int i = 0; i < n; i += 2)
            if (scc.cmp[i] == scc.cmp[i ^ 1]) return 0;

        memset(value, -1, n * sizeof value[0]);
        iota(nodes, nodes + n, 0);
        sort(nodes, nodes + n, [this](int a, int b) { return scc.cmp[a] < scc.cmp[b]; });
        for (int i = 0; i < n; i++) {
            if (~value[nodes[i]]) continue;
            value[nodes[i]] = 1;
            value[nodes[i] ^ 1] = 0;
        }
        return 1;
    }
};

int halal, haram;

TwoSat twoSat;

int getNode(int i, char h) {
    return 2 * i + (h == 'h');
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    while (scanf("%d%d", &halal, &haram), haram || halal) {

        int n = halal * 2;
        twoSat.init(n);

        for (int i = 0; i < haram; ++i) {
            int a, b;
            char ah, bh;
            scanf("%d%c %d%c", &a, &ah, &b, &bh);
            twoSat.add_or(getNode(a, ah), 1, getNode(b, bh), 1);
        }
        for (int i = 0; i < halal; ++i) {
            twoSat.add_xor(getNode(i, 'h'), 1, getNode(i, 'w'), 1);
        }
        twoSat.force(getNode(0, 'w'), 1);

        if (!twoSat()) {
            puts("bad luck");
        } else {
            vector<string> toPrint;
            for (int i = 2; i < n; ++i)
                if (twoSat[i])
                    toPrint.emplace_back(to_string(i / 2) + "wh"[i & 1]);

            for (int i = 0; i < (int) toPrint.size(); ++i) {
                printf("%s%c", toPrint[i].c_str(), " \n"[i + 1 == toPrint.size()]);
            }
        }
    }
}

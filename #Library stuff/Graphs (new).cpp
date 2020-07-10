#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 2e5 + 7, M = 4 * N;

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

unordered_map<int, int> idxOf;
int arr[N];
int n, a, b;

TwoSat twoSat;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    scanf("%d%d%d", &n, &a, &b);

    twoSat.init(n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
        idxOf[arr[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        auto ami = idxOf.find(a - arr[i]), bmi = idxOf.find(b - arr[i]);
        int aidx = ami == idxOf.end() ? -1 : ami->second;
        int bidx = bmi == idxOf.end() ? -1 : bmi->second;
        if (~aidx && ~bidx) {
            twoSat.add_or(i, 0, aidx, 1);
            twoSat.add_or(i, 1, bidx, 0);
        } else if (~aidx) {
            twoSat.force(i, 0);
            twoSat.force(aidx, 0);
        } else if (~bidx) {
            twoSat.force(i, 1);
            twoSat.force(bidx, 1);
        } else {
            puts("NO");
            return 0;
        }
    }

    if (!twoSat()) {
        puts("NO");
        return 0;
    }

    puts("YES");
    for (int i = 0; i < n; ++i) {
        printf("%d ", (int) twoSat[i]);
    }
    puts("");
}

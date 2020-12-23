//modified from kactl
typedef vector<int> vi;
template<bool VALS_EDGES>
struct HLD {
    int N, tim = 0;
    vector<vi> adj;
    vi par, siz, depth, rt, pos;
    SegmentTree tree;
    HLD(const vector<vi> &adj_) : N(adj_.size()), adj(adj_), par(N, -1), siz(N, 1), depth(N),
                                  rt(N), pos(N), tree(N) {
        dfsSz(0);
        dfsHld(0);
    }
    void dfsSz(int v) {
        if (par[v] != -1) adj[v].erase(find(adj[v].begin(), adj[v].end(), par[v]));
        for (int &u : adj[v]) {
            par[u] = v, depth[u] = depth[v] + 1;
            dfsSz(u);
            siz[v] += siz[u];
            if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
        }
    }
    void dfsHld(int v) {
        pos[v] = tim++;
        for (int u : adj[v]) {
            rt[u] = (u == adj[v][0] ? rt[v] : u);
            dfsHld(u);
        }
    }
    template<class B>
    void process(int u, int v, B op) {
        for (; rt[u] != rt[v]; v = par[rt[v]]) {
            if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
            op(pos[rt[v]], pos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u] + VALS_EDGES, pos[v]);
    }
    void modifyPath(int u, int v, int val) {
        process(u, v, [&](int l, int r) { tree.add(l, r, val); });
    }
    int queryPath(int u, int v) {
        int res = 0;
        process(u, v, [&](int l, int r) {
            res = operation(res, tree.query(l, r));
        });
        return res;
    }
    int querySubtree(int v) {
        return tree.query(pos[v] + VALS_EDGES, pos[v] + siz[v] - 1);
    }
};

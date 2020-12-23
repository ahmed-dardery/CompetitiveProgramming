//Binary Lifting
int depth[N], par[N][LG];

void dfs(int u, int p) {
    par[u][0] = p;
    for (auto& v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}
void initLCA(int root, int nNodes) {
    depth[root] = 0;
    dfs(root, -1);

    for (int l = 1; l < LG; ++l)
        for (int i = 0; i < nNodes; ++i)
            if (~par[i][l - 1])
                par[i][l] = par[par[i][l - 1]][l - 1];
            else
                par[i][l] = -1;
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; ++i) {
        if (diff & 1) u = par[u][i];
        diff >>= 1;
    }
    if (u == v) return u;
    for (int i = LG - 1; ~i; --i) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}


//Eular Tour
//calcSzDep(root), buildLCA();
int sz[N], dep[N], in[N], eular[M], dfst;
void calcSzDep(int u, int par = -1) {
    sz[u] = 1;
    eular[in[u] = dfst++] = u;
    for (int v : adj[u]) {
        if (v == par) continue;
        dep[v] = dep[u] + 1;
        calcSzDep(v, u);
        eular[dfst++] = u;
        sz[u] += sz[v];
    }
}
int spt[N][LGN];
void buildLCA() {
    for (int i = 0; i < dfst; ++i)
        spt[i][0] = i;

    for (int j = 1; (1 << j) <= dfst; ++j) {
        for (int i = 0; i + (1 << j) <= dfst; ++i) {
            int a = spt[i][j - 1];
            int b = spt[i + (1 << (j - 1))][j - 1];
            spt[i][j] = dep[eular[a]] < dep[eular[b]] ? a : b;
        }
    }
}
int LCA(int a, int b) {
    a = in[a];
    b = in[b];
    if (a > b) swap(a, b);

    int len = __lg(b - a + 1);
    a = spt[a][len];
    b = spt[b - (1 << len) + 1][len];
    int r = dep[eular[a]] < dep[eular[b]] ? a : b;
    return eular[r];
}
int distance(int u, int v) {
    int l = LCA(u, v);
    return dep[u] + dep[v] - 2 * dep[l];
}

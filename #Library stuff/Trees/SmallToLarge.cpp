//DS.clear(); dfst = 0; dfs_size(root); smallLarge()
int sz[N], in[N], out[N], flat[N], dfst = 0;
void dfs_size(int u, int p = -1) {
    flat[in[u] = dfst++] = u;
    sz[u] = 1;
    for (auto v : adj[u]) {
        if (v != p) {
            dfs_size(v, u);
            sz[u] += sz[v];
        }
    }
    out[u] = dfst - 1;
}
void smallLarge(int u, int p = -1, bool keep = 0) {
    int mx = -1, big = -1;
    for (auto v : adj[u])
        if (v != p && mx < sz[v])
            mx = sz[v], big = v;
    for (auto v : adj[u])
        if (v != p && v != big)
            smallLarge(v, u, 0);

    if (big != -1) {
        smallLarge(big, u, 1);
    }
    addNode(u);
    for (auto v : adj[u]) {
        if (v != p && v != big) {
            for (int t = in[v]; t <= out[v]; ++t) {
                addNode(flat[t]);
            }
        }
    }
    //DS contains all nodes from the subtree of u (including u)
    ans[u] = calcValue(u);

    if (keep == 0) {
        for (int t = in[u]; t <= out[u]; ++t) {
            removeNode(flat[t]);
        }
    }
}

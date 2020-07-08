void szdfs(int u, int p) {
    sz[u] = 1;
    bigChild[u] = -1;
    par[u] = p;
    int mxChild = 0;
    neigh(u, e, v) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        szdfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > mxChild) {
            mxChild = sz[v];
            bigChild[u] = v;
        }
    }
}


int chainHead[N], chainSz[N];

void hld(int u, int chain_head) {
    if (u == chain_head) chainSz[u] = 0;
    ++chainSz[chain_head];
    chainHead[u] = chain_head;

    dfsAt[dfsTime[u] = dfst++] = u;

    if (~bigChild[u]) hld(bigChild[u], chain_head);
    neigh(u, e, v) {
        if (v == par[u] || v == bigChild[u]) continue;
        hld(v, v);
    }
}

void pathUpdate(int u, int v, int newVal) {
    while (chainHead[u] != chainHead[v]) {
        if (depth[chainHead[u]] < depth[chainHead[v]]) swap(u, v);
        update(dfsTime[chainHead[u]], dfsTime[u], newVal);
        u = par[chainHead[u]];
    }
    if (depth[u] < depth[v]) swap(u, v);
    update(dfsTime[v], dfsTime[u], newVal);
}

int pathQuery(int u, int v) {
    node uPath, vPath;
    while (chainHead[u] != chainHead[v]) {
        if (depth[chainHead[u]] < depth[chainHead[v]]) swap(u, v), swap(uPath, vPath);
        node q = query(dfsTime[chainHead[u]], dfsTime[u]);
        swap(q.suf, q.pre);
        uPath = node(uPath, q);
        u = par[chainHead[u]];
    }
    if (depth[u] < depth[v]) swap(u, v), swap(uPath, vPath);
    node q = query(dfsTime[v], dfsTime[u]);
    swap(uPath.suf, uPath.pre);
    return node(node(vPath, q), uPath).mx;
}
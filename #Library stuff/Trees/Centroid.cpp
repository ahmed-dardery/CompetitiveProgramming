int sz[N], del[N], cPar[N], delId;

void calcSz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p || del[v] == delId) continue;
        calcSz(v, u);
        sz[u] += sz[v];
    }
}

int decompose(int u, int p, int s) {
    for (int v : adj[u]) {
        if (v == p || del[v] == delId) continue;
        if (2 * sz[v] > s) return decompose(v, u, s);
    }

    // u is centroid
    // ex, count all pairs with property x where u is on the path
    // use dfs freely (but remember del check)

    del[u] = delId;
    for (int v : adj[u]) {
        if (del[v] == delId) continue;
        calcSz(v, u);
        cPar[decompose(v, u, sz[v])] = u;
    }
    return u;
}

int centroid(int root) {
    delId++;
    calcSz(root, -1);
    root = decompose(root, -1, sz[root]);
    cPar[root] = -1;
    return root;
}

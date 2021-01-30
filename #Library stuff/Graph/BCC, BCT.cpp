int idx[N], low[N], vis[N], isArt[N], isBridge[M], vid, dfst, stck[N], stcksz, cmpcnt;
ADJ compids, bct;
void bccdfs(int u, int pe = -1) {
    idx[u] = low[u] = dfst++;
    vis[u] = vid;
    stck[stcksz++] = u;
    neigh(adj, u, e, v) {
        if (pe == e) continue;
        if (vis[v] != vid) { //gray - white
            bccdfs(v, e ^ 1);
            low[u] = min(low[u], low[v]);
            if (low[v] >= idx[u]) {
                if (low[v] > idx[u])
                    isBridge[e] = isBridge[e ^ 1] = vid;
                if (~pe || idx[v] > idx[u] + 1) //any node, or root with multiple children
                    isArt[u] = vid;
                compids.add_edge(u, cmpcnt);
                do compids.add_edge(stck[--stcksz], cmpcnt); while (stck[stcksz] != v);
                ++cmpcnt;
            }
        } else //gray - gray
            low[u] = min(low[u], idx[v]);
    }
}
void constructBCT() {
    int nNodes = 2*n;
    bct.init(nNodes);
    for (int u = 0; u < n; ++u)
        if (isArt[u] == vid)
            neigh(compids, u, _, v)bct.add_biedge(u, v + n);
}
void bcc() {
    ++vid;
    compids.init(n);
    dfst = cmpcnt = 0;
    for (int u = 0; u < n; ++u) {
        if (vis[u] != vid) {
            stcksz = 0;
            int old = dfst;
            bccdfs(u);
            if (dfst == old + 1)
                compids.add_edge(u, cmpcnt++);
        }
    }

    constructBCT();
}

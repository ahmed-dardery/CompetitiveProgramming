const int NN = 1e5 + 7, OO = 0x3f3f3f3f;
int q[NN], qsz, vis[NN], vid, dis[NN];
int src, snk;
int nNodes /*= something*/;

bool bfs() {
    ++vid;
    qsz = 0;
    q[qsz++] = src;
    memset(dis, OO, nNodes * sizeof dis[0]);
    dis[src] = 0;
    vis[src] = vid;
    for (int k = 0; k < qsz; ++k) {
        int u = q[k];
        for (int e = head[u], v; v = to[e], ~e; e = nxt[e]) {
            if (vis[v] == vid || cap[e] == 0) continue;
            vis[v] = vid;
            dis[v] = dis[u] + 1;
            if (v == snk) return 1;
            q[qsz++] = v;
        }
    }
    return 0;
}

int flowdfs(int u, int mn) {
    if (u == snk)
        return mn;
    if (mn == 0 || vis[u] == vid)
        return 0;

    vis[u] = vid;

    for (int &e = work[u]; ~e; e = nxt[e]) {
        int v = to[e];

        if (dis[v] != dis[u] + 1)
            continue;
        int f = flowdfs(v, min(mn, cap[e]));
        if (f) {
            cap[e] -= f;
            cap[e ^ 1] += f;
            return f;
        }
    }

    return 0;
}

int max_flow() {
    int f = 0;
    while (bfs()) {
        memcpy(work, head, nNodes * sizeof head[0]);
        ++vid;
        while (int chg = flowdfs(src, OO)) {
            f += chg;
            ++vid;
        }
    }
    return f;
}


const int NN = 1e5 + 7;
int nNodes;
int dist[NN], flw[NN], vis[NN], par[NN], vid;

ll bellman(int src) {
    int u = src;
    memset(dist, 0x3f, nNodes * sizeof dist[0]);
    memset(flw, 0, nNodes * sizeof flw[0]);
    flw[u] = INT_MAX;
    dist[u] = 0;
    vis[u] = ++vid;
    queue<int> Q;
    Q.emplace(u);
    int cnt = nNodes;
    while (Q.size() and cnt--) {
        int s = Q.size();
        while (s--) {
            u = Q.front();
            Q.pop();
            vis[u] = 0;
            neig(head, u, e, v, cp)
            {
                if (!cp) continue;
                int dd = dist[u] + cst[e];
                if (dd < dist[v]) {
                    dist[v] = dd;
                    flw[v] = min(flw[u], cp);
                    par[v] = e;
                    if (vis[v] != vid) {
                        vis[v] = vid;
                        Q.emplace(v);
                    }
                }
            }
        }
    }
    if (flw[snk]) {
        for (int i = snk, e; e = par[i], i != src; i = to[e ^ 1]) {
            cap[e] -= flw[snk];
            cap[e ^ 1] += flw[snk];
        }
    }
    return flw[snk];
}

pair<ll, ll> min_cost_max_flow() {
    ll res = 0, f, cost = 0;
    while (++vid, f = bellman(src)) {
        res += f;
        cost += f * dist[snk];
    }
    return {res, cost};
}

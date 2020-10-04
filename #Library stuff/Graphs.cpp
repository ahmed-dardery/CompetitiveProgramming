#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5, M = N * N + 5, OO = 0x3f3f3f3f;
int head[N], nxt[2*M], to[2*M], ne;

void add_edge(int f, int t) {
	nxt[ne] = head[f];
	to[ne] = t;
	head[f] = ne++;
}
void add_biedge(int a, int b) { add_edge(a, b), add_edge(b, a); }
#define neigh(u,e,v) for(int e = head[u], v ; v = to[e], ~e ; e = nxt[e])

int sz[N], par[N], sets;

void init(int n) {
	iota(par, par + n, 0);
	fill(sz, sz + n, 1);
	sets = n;
}

int find(int u) {
	return (par[u] == u ? u : par[u] = find(par[u]));
}

void join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b)	return;
	if (sz[a] < sz[b])	swap(a, b);		//optional
	sz[a] += sz[b];						//remove if no size
	par[b] = a;
	--sets;
}

bool bellman(int src) {
	memset(dis, OO, sizeof dis);
	dis[src] = 0;
	int x = n;
	while (x--) {
		for (int e = 0; e < ne; e++) {
			int u = from[e], v = to[e], c = cst[e];
			if (dis[u] + c < dis[v]) {
				if (!x)	return 0;
				dis[v] = dis[u] + c;
			}
		}
	}
	return 1;
}

const int di[] = { 1,-1,0,0 };
const int dj[] = { 0,0,1,-1 };
bool inbounds(int ni, int nj) {
	return (ni >= 0 && ni < n && nj >= 0 && nj < m);
}

int dis[N];
void dijkstra(int f) {
	memset(dis + 1, OO, n * sizeof dis[0]);
	priority_queue<pii> q;
	dis[f] = 0;
	q.emplace(0, f);
	while (!q.empty()) {
		int u = q.top().second;
		int d = -q.top().first;
		q.pop();
		if (d != dis[u]) continue;
		for (int e = head[u]; ~e; e = nxt[e]) {
			int v = to[e], c = cst[e];
			int nd = dis[u] + c;
			if (nd < dis[v]) {
				dis[v] = nd;
				q.emplace(-nd, v);
			}
		}
	}
}

int dfst, visidx[N], lowlink[N], cmpid[N], cmpn;
int stck[N], stcksz = 0;
void sccbfs(int u) {

	visidx[u] = lowlink[u] = dfst++;
	stck[stcksz++] = u;
	for (int e = head[u], v; v = to[e], ~e; e = nxt[e]) {
		if (visidx[v] == -1) {
			sccbfs(v);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		}
		else if (cmpid[v] == -1) {	//not cross edge
			lowlink[u] = min(lowlink[u], visidx[v]);
		}
	}
	if (lowlink[u] == visidx[u]) {
		while (stcksz--) {
			cmpid[stck[stcksz]] = cmpn;
			if (stck[stcksz] == u) break;
		}
		cmpn++;
	}
}
void scc() {
	memset(visidx, -1, n * sizeof visidx[0]);
	memset(lowlink, -1, n * sizeof lowlink[0]);
	memset(cmpid, -1, n * sizeof cmpid[0]);
	cmpn = dfst = stcksz = 0;
	for (int i = 0; i < n; i++) {
		if (visidx[i] == -1)
			sccbfs(i);
	}
}

int depth[N];
int par[N][LG];

void dfs(int u, int p) {
    for (auto &v : adj[u]) {
        if (v == p) continue;
        par[v][0] = u;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

void initLCA(int root) {
    memset(par, -1, LG * (n + 1) * sizeof(int));
    depth[root] = 0;
    dfs(root, -1);

    for (int i = 0; i < n; ++i)
        for (int l = 1; l < LG; ++l)
            if (~par[i][l - 1])
                par[i][l] = par[par[i][l - 1]][l - 1];
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

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

int stcksz[N], par[N], sets;

void init(int n) {
	iota(par, par + n, 0);
	fill(stcksz, stcksz + n, 1);
	sets = n;
}

int find(int u) {
	return (par[u] == u ? u : par[u] = find(par[u]));
}

void join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b)	return;
	if (stcksz[a] < stcksz[b])	swap(a, b);		//optional
	stcksz[a] += stcksz[b];						//remove if no size
	par[b] = a;
	--sets;
}

bool bellman(int src) {
	memset(best, OO, sizeof best);
	best[src] = 0;
	int x = nNodes;
	while (x--) {
		for (int e = 0; e < ne; e++) {
			int u = from[e], v = to[e], c = cst[e];
			if (best[u] + c < best[v]) {
				if (!x)	return 0;
				best[v] = best[u] + c;
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

int best[N];
void dijkstra(int f) {
	memset(best + 1, OO, nNodes * sizeof best[0]);
	priority_queue<pii> q;
	best[f] = 0;
	q.emplace(0, f);
	while (!q.empty()) {
		int u = q.top().second;
		int d = -q.top().first;
		q.pop();
		if (d != best[u]) continue;
		for (int e = head[u]; ~e; e = nxt[e]) {
			int v = to[e], c = cst[e];
			int nd = best[u] + c;
			if (nd < best[v]) {
				best[v] = nd;
				q.emplace(-nd, v);
			}
		}
	}
}

int dfst, visidx[N], lowlink[N], cmpid[N], cmpn;
int stck[N], stcksz = 0;
void sccdfs(int u) {

	visidx[u] = lowlink[u] = dfst++;
	stck[stcksz++] = u;
	for (int e = head[u], v; v = to[e], ~e; e = nxt[e]) {
		if (visidx[v] == -1) {
			sccdfs(v);
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
void bcc() {
	memset(visidx, -1, nNodes * sizeof visidx[0]);
	memset(lowlink, -1, nNodes * sizeof lowlink[0]);
	memset(cmpid, -1, nNodes * sizeof cmpid[0]);
	cmpn = dfst = stcksz = 0;
	for (int i = 0; i < n; i++) {
		if (visidx[i] == -1)
			sccdfs(i);
	}
}


//bridgify
bool bridge[M];
void bccdfs(int u, int p) {

	visidx[u] = lowlink[u] = dfst++;
	for (int e = head[u], v; v = to[e], ~e; e = nxt[e]) {
		if (visidx[v] == -1) {
			bccdfs(v, u);
			lowlink[u] = min(lowlink[u], lowlink[v]);
			if (lowlink[v] > visidx[u]) {
				bridge[e] = bridge[e ^ 1] = 1;
			}
		}
		else if (v != p) {
			lowlink[u] = min(lowlink[u], visidx[v]);
		}
	}
}








int vis[N], vid, q[N], qsz, best[N];


bool bfs() {
	++vid;
	qsz = 0;
	q[qsz++] = src;
	memset(best, OO, nNodes * sizeof best[0]);
	best[src] = 0;
	vis[src] = vid;
	for (int k = 0; k < qsz; ++k) {
		int u = q[k];
		for (int e = head[u], v; v = to[e], ~e; e = nxt[e]) {
			if (vis[v] == vid || cap[e] == 0) continue;
			vis[v] = vid;
			best[v] = best[u] + 1;
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

		if (best[v] != best[u] + 1 )
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

//or


ll best[N];
int parEdge[N];
bool bellman(int src) {
	memset(best, OO, sizeof best);
	best[src] = 0;
	parEdge[src] = -1;

	int x = nNodes;
	while (x--) {
		for (int e = 0; e < ne; e++) {
			if (!cap[e]) continue;
			int u = to[e ^ 1], v = to[e];
			ll c = cst[e];
			if (best[u] + c < best[v]) {
				if (!x)	assert(0);
				best[v] = best[u] + c;
				parEdge[v] = e;
			}
		}
	}
	return best[snk] != OO;
}
ll augment() {
	int e;
	int u = snk;
	int mn = OO;
	while (~(e = parEdge[u])) {
		mn = min(mn, cap[e]);
		u = to[e ^ 1];
	}
	u = snk;
	ll price = 0;
	while (~(e = parEdge[u])) {
		cap[e] -= mn;
		cap[e ^ 1] += mn;

		price += mn * cst[e];

		u = to[e ^ 1];
	}
	return price;
}

ll flow() {
	memcpy(cap, cap, sizeof cap);
	ll f = 0;
	while (bellman(src)) {
		ll chg = augment();
		f += chg;
	}
	return f;
}
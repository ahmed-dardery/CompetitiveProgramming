#include <bits/stdc++.h>

using namespace std;
int tsts, n;

typedef long long ll;

const int NODES = 100;
const int N = 2 * NODES, M = 4 * N * N, OO = 0x3f3f3f3f3f;
int head[N], work[N], nxt[M], to[M], ne;
ll cap[M];
void add_edge(int f, int t, ll c) {
	nxt[ne] = head[f];
	to[ne] = t;
	cap[ne] = c;
	head[f] = ne++;
}
void add_flowedge(int u, int v, ll c) {
	if (c == 0) return;
	add_edge(u, v, c);
	//cerr << u << " " << v << " " << c << endl;
	add_edge(v, u, 0);
}

int src = 0;
int snk = N - 1;

int vis[N], vid;
int dis[N];
int q[N], qsz;
bool bfs() {
	++vid;
	qsz = 0;
	q[qsz++] = src;
	memset(dis, OO, n * sizeof dis[0]);
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
ll flowdfs(int u, ll mn) {
	if (u == snk)
		return mn;
	if (mn == 0 || vis[u] == vid)
		return 0;

	vis[u] = vid;

	for (int &e = work[u]; ~e; e = nxt[e]) {
		int v = to[e];

		if (dis[v] != dis[u] + 1)
			continue;
		ll f = flowdfs(v, min(mn, cap[e]));
		if (f) {
			cap[e] -= f;
			cap[e ^ 1] += f;
			return f;
		}
	}

	return 0;
}
ll max_flow() {
	ll f = 0;
	while (bfs()) {
		memcpy(work, head, n * sizeof head[0]);
		++vid;
		while (ll chg = flowdfs(src, OO)) {
			f += chg;
			++vid;
		}

	}
	return f;
}

int m, w;
int main() {
	//freopen("input.txt", "rt", stdin);
	//freopen("output.txt", "wt", stdout);
	while (scanf("%d %d", &m, &w), m || w) {
		ne = 0;
		src = 0;
		snk = (m - 1) * 2;
		n = snk + 2;
		memset(head, -1, n * sizeof head[0]);
		for (int i = 0; i < m - 2; i++) {
			int u; ll c;
			scanf("%d %lld", &u, &c);
			--u;
			u *= 2;
			add_flowedge(u, u ^ 1, c);
		}
		add_flowedge(0, 1, OO);
		add_flowedge(snk, snk ^ 1, OO);
		snk++;
		for (int i = 0; i < w; i++) {
			int u, v; ll c;
			scanf("%d %d %lld", &u, &v, &c);
			--u, --v;
			u *= 2, v *= 2;
			add_flowedge(u ^ 1, v, c);
			add_flowedge(v ^ 1, u, c);

		}
		printf("%lld\n", max_flow());
	}
}
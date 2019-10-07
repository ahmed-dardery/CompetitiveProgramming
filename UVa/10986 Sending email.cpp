#include <bits/stdc++.h>
int tsts;

using namespace std;
typedef pair<int, int> pii;

const int N = 5e5 + 7, M = 5e5 + 7;
int head[N], nxt[M], to[M], cst[M], ne;
void add_edge(int f, int t, int c) {
	nxt[ne] = head[f];
	to[ne] = t;
	cst[ne] = c;
	head[f] = ne++;
}
void add_biedge(int u, int v, int c) { add_edge(u, v, c), add_edge(v, u, c); }
int dis[N];
int n, m, st, en;
void init() {
	memset(head, -1, (n + 1) * sizeof head[0]);
	memset(dis, '?', (n + 1) * sizeof dis[0]);
	ne = 0;
}
int Dijkstra() {
	priority_queue<pii> q;
	q.emplace(0, st);
	dis[st] = 0;
	while (q.size()) {
		int u = q.top().second;
		int d = -q.top().first;
		q.pop();
		if (d != dis[u]) continue;
		if (u == en) return dis[u];
		for (int e = head[u], v; v = to[e], ~e; e = nxt[e]) {
			if (dis[u] + cst[e] < dis[v]) {
				dis[v] = dis[u] + cst[e];
				q.emplace(-dis[v], v);
			}
		}
	}
	return -1;
}
int a, b, c;
int main() {
	scanf("%d", &tsts);
	for (int ts = 0; ts < tsts; ts++) {
		scanf("%d%d%d%d", &n, &m, &st, &en);
		init();
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &a, &b, &c);
			add_biedge(a, b, c);
		}
		int ans = Dijkstra();
		printf("Case #%d: ", ts + 1);
		if (ans == -1) printf("unreachable\n");
		else printf("%d\n", ans);
	}
}
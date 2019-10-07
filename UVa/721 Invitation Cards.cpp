#include <bits/stdc++.h>
int tsts;

using namespace std;
typedef long long  ll;
typedef pair<ll, int> pli;

const int N = 1e6 + 7, M = 2e6 + 7, OO = 0x3f3f3f3f;
int head[N], nxt[M], to[M], ne;
ll cst[M];

void add_edge(int f, int t, ll c) {
	nxt[ne] = head[f];
	to[ne] = t;
	cst[ne] = c;
	head[f] = ne++;
}

int n, m;
int a, b; ll c;

ll dis[N];
void Dijkstra(bool odd) {
	memset(dis + 1, OO, n * sizeof dis[0]);
	priority_queue<pli> q;
	dis[1] = 0;
	q.emplace(0, 1);
	while (!q.empty()) {
		int u = q.top().second;
		ll d = -q.top().first;
		q.pop();
		if (d != dis[u]) continue;
		for (int e = head[u]; ~e; e = nxt[e]) {
			if ((e & 1) == odd) continue;
			int v = to[e]; ll c = cst[e];
			ll nd = dis[u] + c;
			if (nd < dis[v]) {
				dis[v] = nd;
				q.emplace(-nd, v);
			}
		}
	}
}


int main() {
	scanf("%d", &tsts);
	while (tsts--) {
		scanf("%d%d", &n, &m);
		memset(head + 1, -1, n * sizeof head[0]);
		ne = 0;

		for (int i = 0; i < m; i++) {
			scanf("%d%d%lld", &a, &b, &c);
			add_edge(a, b, c);
			add_edge(b, a, c);
		}
		ll total = 0;
		Dijkstra(0);
		for (int i = 1; i <= n; i++) {
			total += dis[i];
		}
		Dijkstra(1);
		for (int i = 1; i <= n; i++) {
			total += dis[i];
		}
		printf("%lld\n", total);
	}
}
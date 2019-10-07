#include <bits/stdc++.h>
int tsts;

using namespace std;
typedef long long  ll;
typedef pair<int, int> pii;
const int N = 550, M = 2 * 10007;
int head[N], nxt[M], to[M], degree[M], ne;

void add_edge(int f, int t) {
	nxt[ne] = head[f];
	to[ne] = t;
	degree[f]++;
	head[f] = ne++;
}
void add_biedge(int a, int b) { add_edge(a, b), add_edge(b, a); }

int vis[M], vid;
pii ans[M]; int sz = 0;
void Euler(int u) {
	for (int &k = head[u]; ~k; ) {
		int v = to[k], e = k;
		k = nxt[k];
		if (vis[e] == vid) continue;
		vis[e ^ 1] = vid;
		Euler(v);
		ans[sz++] = { u, v };
	}
}
int m, n;
int a, b;
int main() {
	//freopen("input.txt", "rt", stdin);
	n = 50;
	scanf("%d", &tsts);
	for (int t = 1; t <= tsts; t++) {
		sz = 0;
		vid++;
		scanf("%d", &m);
		memset(head, -1, (n + 1) * sizeof head[0]);
		memset(degree, 0, (n + 1) * sizeof degree[0]);
		ne = 0;

		int odd;
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			add_biedge(a, b);
			odd = a;
		}
		int oddc = 0;
		for (int i = 1; i <= n; ++i) {
			if (degree[i] & 1) odd = i, ++oddc;
		}
		printf("Case #%d\n", t);
		if (oddc != 0)
			puts("some beads may be lost");
		else {
			Euler(odd);

			if (sz != m) puts("some beads may be lost");
			else {

				for (int i = m - 1; ~i; --i) {
					printf("%d %d\n", ans[i].first, ans[i].second);
				}
			}
		}
		puts("");
	}

}
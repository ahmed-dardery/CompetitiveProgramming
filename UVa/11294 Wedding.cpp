#include <bits/stdc++.h>
int tsts;

using namespace std;
typedef long long  ll;
const int N = 120, M = N * N + N;

int head[N], to[M], nxt[M], ne;
void add_edge(int f, int t) {
	nxt[ne] = head[f];
	to[ne] = t;
	head[f] = ne++;
}

int n, m;

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

int nodes[N];
int value[N];
bool twosat() {
	scc();
	memset(value, -1, n * sizeof value[0]);
	for (int i = 0; i < n; i += 2) {
		if (cmpid[i] == cmpid[i ^ 1]) return 0;
	}
	iota(nodes, nodes + n, 0);
	sort(nodes, nodes + n, [](int a, int b) {return cmpid[a] < cmpid[b]; });
	for (int i = 0; i < n; i++) {
		if (~value[nodes[i]]) continue;
		value[nodes[i]] = 1;
		value[nodes[i] ^ 1] = 0;
	}
	return 1;
}

int a, b;
int legal, notlegal;
void add_or(int a, int b) {
	add_edge(a ^ 1, b);
	add_edge(b ^ 1, a);
}
int getnode(char gender, int idx, bool inv) {
	return (idx * 4 + (gender == 'h') * 2) ^ inv;
}
pair<int, char> toprint[N]; int tosz;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	while (scanf("%d%d", &legal, &notlegal), legal) {
		n = legal * 4;
		memset(head, -1, n * sizeof head[0]);
		ne = 0;
		add_or(getnode('w', 0, 1), getnode('w', 0, 1));		//w0' + w0'		//thus w0 must be 0

		for (int i = 0; i < legal; i++) {
			//(wi + hi)(wi' + hi')
			add_or(getnode('w', i, 0), getnode('h', i, 0));
			add_or(getnode('w', i, 1), getnode('h', i, 1));
		}
		for (int i = 0; i < notlegal; i++) {
			int i1, i2;
			char c1, c2;
			scanf("%d%c%d%c", &i1, &c1, &i2, &c2);
			//(a' + b')
			add_or(getnode(c1, i1, 1), getnode(c2, i2, 1));
		}
		if (twosat()) {
			tosz = 0;
			for (int i = 2; i < n; i += 2) {
				int j = (i >> 1);
				if (value[i] == 0)
					toprint[tosz++] = { j / 2,"wh"[j & 1] };
			}
			for (int i = 0; i < tosz; i++) {
				printf("%d%c%c", toprint[i].first, toprint[i].second, " \n"[i == tosz - 1]);
			}
		}
		else {
			puts("bad luck");
		}
	}
}
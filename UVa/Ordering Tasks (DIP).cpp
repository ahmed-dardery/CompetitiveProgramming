#include <bits/stdc++.h>
using namespace std;
const int N = 128, M = 200;

int head[N], to[M], nxt[M], degree[N], ne = 0;
void add_edge(int f, int t) {
	to[ne] = t;
	nxt[ne] = head[f];
	degree[t]++;
	head[f] = ne++;
}
#define neigh(u,e,v) for(int e = head[u], v; v = to[e], ~e; e = nxt[e])
#define inoutfile freopen("input.txt", "rt", stdin);freopen("output.txt", "wt", stdout)

char nodes[N], nl;
int n = 0;
char q[N];
int sz;

int order[200], c;
vector<char> res[10000];
int nres = 0;

void init() {
	n = 0;
	memset(head, -1, sizeof head);
	memset(degree, 0, sizeof degree);
	ne = 0;

	sz = 0;
	c = 0;
	nres = 0;
}
void BFSrecurse(int k) {
	if (k >= sz) {
		res[nres].resize(c);
		copy(order, order + c, res[nres++].begin());
		return;
	}
	int orgsize = sz;
	int u = q[k];
	neigh(u, e, v) {
		if (!--degree[v])
			q[sz++] = v;
	}
	order[c++] = u;

	char orgq[N];
	copy(q + k + 1, q + sz, orgq + k + 1);
	sort(q + k + 1, q + sz);
	do {
		BFSrecurse(k + 1);
	} while (next_permutation(q + k + 1, q + sz));
	copy(orgq + k + 1, orgq + sz, q + k + 1);

	neigh(u, e, v) {
		degree[v]++;
	}
	sz = orgsize;
	c--;
}

void BFS() {
	for (int i = 0; i < n; ++i) {
		int v = nodes[i];
		if (!degree[v]) q[sz++] = v;
	}
	sort(q, q + sz);
	do {
		BFSrecurse(0);
	} while (next_permutation(q, q + sz));
}

int main() {
	in
	while (true) {
		init();
		while (true) {
			if (scanf("%c%c", nodes + n++, &nl) == EOF) return 0;
			if (nl == '\n') break;
		}
		while (true) {
			char a, b;
			scanf("%c %c%c", &a, &b, &nl);
			add_edge(a, b);
			if (nl == '\n') break;
		}
		BFS();
		int x = unique(res, res + nres) - res;
		for (int i = 0; i < x; ++i) {
			for (int j = 0; j < res[i].size(); j++) {
				printf("%c", res[i][j]);
			}
			puts("");
		}
		puts("");
	}
}
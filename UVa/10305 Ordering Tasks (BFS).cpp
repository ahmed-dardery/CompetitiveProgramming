#include <bits/stdc++.h>
using namespace std;

const int N = 10005, M = 1000005;
const long long OO = 1e18;

#define neigh(u,e,v) for (int e = head[u], v; v = to[e], ~e; e = nxt[e])
int ne = 0;
int head[N], nxt[M], to[M], degree[N];
void add_edge(int f, int t) {
	nxt[ne] = head[f];
	to[ne] = t;
	degree[t]++;
	head[f] = ne++;
}
void add_biedge(int a, int b) { add_edge(a, b), add_edge(b, a); }

#define max(a,b) ( ((a) > (b)) ? (a) : (b) )
#define min(a,b) ( ((a) < (b)) ? (a) : (b) )
#define fori(n) for (int i = 0; i < (n); i++)
#define forirev(n) for (int i = (n-1); ~i; i--)
#define forj(n) for (int j = 0; j < (n); j++)
#define forjrev(n) for (int j = (n-1); ~j; j--)
#define fork(n) for (int k = 0; k < (n); k++)
#define FOR(a,b,c) for (int a = (b); a < (c); ++a)
#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
#define unsync cin.sync_with_stdio(false), cin.tie(0)
#define inoutfile freopen("input.txt", "rt", stdin);freopen("output.txt", "wt", stdout)

typedef unsigned long long ulng;
typedef long long lng;
typedef pair<int, int> pii;
typedef pair<lng, lng> pll;
typedef vector<int> vi;
typedef vector<vector<int>> vii;
typedef vector<pii> vpii;

int n, m;

int q[200];

int sz = 0;

int order[200];
int c = 0;

void BFS() {
	fori(n) {
		if (!degree[i]) q[sz++] = i;
	}
	for (int k = 0; k < sz; ++k) {
		int u = q[k];
		neigh(u, e, v) {
			if (!--degree[v])
				q[sz++] = v;
		}
		order[c++] = u;
	}
}
void init(int n) {
	memset(head, -1, n * sizeof head[0]);
	c = 0;
	sz = 0;
}
int main() {
	inoutfile;
	while (true) {
		scanf("%d %d", &n, &m);
		if (n == m && n == 0) break;
		init(n);
		fori(m) {
			int f, t;
			scanf("%d %d", &f, &t);
			add_edge(--f, --t);
		}
		BFS();
		fori(c) {
			printf("%d", order[i] + 1);
			if (i != c - 1) printf(" ");
		}
		puts("");
	}
}
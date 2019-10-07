#include <bits/stdc++.h>

using namespace std;

/*
const int N = 10005, M = 1000005;
const long long OO = 1e18;

#define neigh(u,e,v) for (int e = head[u], v; v = to[e], ~e; e = nxt[e])
int ne = 0;
int head[N], nxt[M], to[M];//, degree[N];
void add_edge(int f, int t) {
	nxt[ne] = head[f];
	to[ne] = t;
	//degree[t]++;
	head[f] = ne++;
}
void add_biedge(int a, int b) { add_edge(a, b), add_edge(b, a); }
*/

#define fori(n) for (int i = 0; i < (n); i++)
#define forj(n) for (int j = 0; j < (n); j++)
#define all(x) (x).begin(), (x).end()
#define unsync cin.sync_with_stdio(false), cin.tie(0)
#define inoutfile freopen("input.txt", "rt", stdin);freopen("output.txt", "wt", stdout)

template <class N> using vec = vector<N>;
typedef long long lng;

int n, w[3001], l[3001];

int mem[1001][3011];

int dp(int i, int c) {
	if (c >= 3010) c = 1e9;
	if (c < 0) return -1;
	if (i == n) return 0;
	
	int &res = mem[i][(c > 3010) ? 3010 : c];
	if (~res) return res;


	int r1 = dp(i + 1, c);
	int r2 = dp(i + 1, min(c - w[i], l[i])) + 1;

	if (r2 > r1) return res = r2; else return res = r1;
}

int main() {
	while (scanf("%d", &n) != EOF && n != 0) {
		memset(mem, -1, sizeof mem);
		for(int i = 0; i < n; ++i) scanf("%d %d", &w[i], &l[i]);
		printf("%d\n",dp(0, 1e9));
	}
}
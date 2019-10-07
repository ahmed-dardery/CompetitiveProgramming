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

typedef long long lng;


const int M = 201, C = 21, K = 21;
#define FAIL -1000

int test;
int m, c;

int price[C][K];
int sz[C];

int mem[C][M];

int dp(int ind, int money) {
	if (money < 0) return FAIL;
	if (!~ind) return m - money;

	int &res = mem[ind][money];
	if (~res) return res;
	res = FAIL;
	fori(sz[ind]) {
		if (money >= price[ind][i])
			res = max(res, dp(ind - 1, money - price[ind][i]));
	}
	return res;
}

int main() {
	
	scanf("%d", &test);
	while (test--) {
		memset(mem, -1, sizeof mem);
		scanf("%d %d", &m, &c);
		fori(c) {
			scanf("%d", &sz[i]);
			forj(sz[i])
				scanf("%d", &price[i][j]);

		}
		int res = dp(c - 1, m);
		if (res == FAIL)
			puts("no solution");
		else
			printf("%d\n", res);

	}
}
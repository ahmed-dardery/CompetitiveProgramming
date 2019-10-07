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

const int N = 5;
int change[N] = { 1,5,10,25,50 };

int n;

lng mem[7501][N + 1];

lng dp(int n, int i = N-1) {
	if (n == 0) return 1;
	if (!~i) return 0;

	lng &ret = mem[n][i];
	if (~ret) return ret;
	ret = 0;

	if (n >= change[i])
		ret += dp(n - change[i], i);
	
	ret += dp(n, i - 1);

	return ret;
}

int main() {
	//inoutfile;
	memset(mem, -1, sizeof mem);
	while (scanf("%d", &n) != EOF) {
		printf("%lld\n", dp(n));
	}
}
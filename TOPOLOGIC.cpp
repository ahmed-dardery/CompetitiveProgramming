#include <bits/stdc++.h>
using namespace std;

#define neigh(u,e,v) for (int e = head[u], v; v = to[e], ~e; e = nxt[e])
const int N = 10005, M = 1000005;
int ne = 0;
int head[N], nxt[M], to[M], degree[N];
void add_edge(int f, int t) {
	nxt[ne] = head[f];
	to[ne] = t;
	++degree[t];
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
typedef vector<pair<lng, lng>> vpll;

int n, m;

int visit[N]; //0: unvisited, -1 underprocessing, 1 visited

void init() {
	memset(head + 1, -1, n * sizeof head[0]);
	ne = 0;
}

int order[N];
int o = 0;

void BFS() {
	priority_queue<int, vector<int>, greater<int>> q;
	fori(n) {
		if (!degree[i+1]) q.push(i+1);
	}
	int u;
	while (!q.empty()) {
		u = q.top();
		q.pop();
		order[o++] = u;
		neigh(u, e, v)
			if (!--degree[v])
				q.push(v);
	}

}
int main()
{
	//inoutfile;
	unsync;
	scanf("%d %d", &n, &m);
	init();
	fori(m){
		int a, b;
		scanf("%d %d", &a, &b);
		add_edge(a, b);
	}
	BFS();
	if (o != n) printf("Sandro fails.\n");
	else{
		for (int i = 0; i < o; ++i)
			printf("%d ", order[i]);
		puts("");
	}
}
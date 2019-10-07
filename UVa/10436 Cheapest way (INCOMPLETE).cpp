#include <bits/stdc++.h>

using namespace std;
typedef long long lng;

const int N = 1e3 + 5, M = N * N + 5, OO = 0x3f3f3f3f;

int head[N], nxt[M], to[M], cst[M];
int ne;

void add_edge(int f, int t, int c) {
	nxt[ne] = head[f];
	to[ne] = t;
	cst[ne] = c;
	head[f] = ne++;
}
void add_biedge(int a, int b,int c) { add_edge(a, b,c), add_edge(b, a,c); }
#define neigh(u,e,v) for(int e = head[u], v ; v = to[e], ~e ; e = nxt[e])

int n,dis[N];
void init() {
	memset(head, -1, sizeof head);
	ne = 0;
}
struct node {
	int dis;
	int u;
	int par;
	bool operator<(const node &n) const {
		return dis > n.dis;
	}
};
int maps, ns, np, nq, c;

char inttostr[301][35], a[301], b[301];
int stCst[35];


int parent[N];
void Dijkstra(int src) {
	memset(parent, -1, sizeof parent);
	memset(dis, OO, sizeof dis);
	priority_queue<node> q;
	q.push({ stCst[src], src ,-1});
	dis[src] = stCst[src];
	while (q.size()) {
		int d = q.top().dis, u = q.top().u;
		q.pop();
		if (dis[u] != d)	continue;
		neigh(u,e,v) {
			int c = cst[e] + stCst[v];
			int dd = d + c;
			if (dis[v] > dd) {
				dis[v] = dd;
				parent[v] = u;
				q.push({ dd, v, u});
			}
		}
	}
}
map<string, int> strtoint;

void print(int i) {
	if (i == -1) return;
	if (i)	print(parent[i]);
	printf("%s%c", inttostr[i],(i==strtoint[b])?'\n':' ');
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif
 
	scanf("%d", &maps);
	for (int m = 1; m <= maps; m++) {
		printf("Map #%d\n", m);
		init();
		strtoint.clear();
		scanf("%d", &ns);
		for (int i = 0; i < ns; i++) {
			scanf("%s %d", inttostr + i, stCst + i);
			strtoint[inttostr[i]] = i;

		}
		scanf("%d", &np);
		for (int i = 0; i < np; i++) {
			scanf("%s %s %d", &a,&b,&c);
			add_biedge(strtoint[a], strtoint[b], c*2);
		}
		scanf("%d", &nq);
		for (int i = 1; i <= nq; i++) {
			printf("Query #%d\n", i);
			scanf("%s %s %d", &a, &b, &c);
			Dijkstra(strtoint[a]);
			print(strtoint[b]);
			printf("Each passenger has to pay : %.2Lf taka\n",dis[strtoint[b]] * 1.1 / c);
		}
		if (m != maps) puts("");
	}
}	
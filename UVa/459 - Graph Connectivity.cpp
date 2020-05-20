#include <bits/stdc++.h>

using namespace std;
typedef long long lng;

const int N = 1 << 8, M = N*N + 5, OO = 0x3f3f3f3f;
int head[N], nxt[M], to[M], ne;
void add_edge(int f, int t) {
	nxt[ne] = head[f];
	to[ne] = t;
	head[f] = ne++;
}
void add_biedge(int a, int b) { add_edge(a, b), add_edge(b, a); }
#define neigh(u,e,v) for(int e = head[u], v ; v = to[e], ~e ; e = nxt[e])


int n;
char a, b, tmp, last;
int vis[N], vid;
void init() {
	memset(head + 'A', -1, last * sizeof(head[0]) - 'A');
	vid++;
}

void BFS(int u) {
	vis[u] = vid;
	neigh(u, e, v) {
		if (vis[v] != vid) BFS(v);
	}
}
int main() {
	scanf("%d ", &n);
	while (n--) {
		
		scanf("%c%c", &last, &tmp); 
		init();

		while (scanf("%c", &a) != EOF && a != '\n') {
			scanf("%c%c", &b, &tmp);
			add_biedge(a, b);
		}
		int count = 0;
		for (char ch = 'A'; ch <= last; ch++)
			if (vis[ch] != vid)
				count++, BFS(ch);

		printf("%d\n", count);
		if (n != 0) puts("");
	}
}
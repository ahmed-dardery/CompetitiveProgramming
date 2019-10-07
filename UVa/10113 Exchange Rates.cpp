#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
struct frac {
	int num;
	int denom;
	frac() {
		num = denom = 1;
	}
	frac(int a, int b) {
		int x = gcd(a, b);
		denom = b / x;
		num = a / x;
	}
	frac operator* (const frac &f) {
		return frac(num*f.num, denom*f.denom);
	}
	
};

const int N = 100, M = 100000;
int head[N], to[M], nxt[M], ne = 0;
frac cost[M];
void add_edge(int f, int t, frac c) {
	to[ne] = t;
	nxt[ne] = head[f];
	cost[ne] = c;
	head[f] = ne++;
}
//void add_biedge(int a, int b) { add_edge(a, b), add_edge(b, a); }
#define neigh(u,e,v) for(int e = head[u], v; v = to[e], ~e; e = nxt[e])

#define inoutfile freopen("input.txt", "rt", stdin);freopen("output.txt", "wt", stdout)
typedef long long lng;

struct {
	int v;
	frac c;
} q[N];
int sz;

int vis[N], vid = 0;
bool BFS(int st, int en) {
	sz = 0;
	q[sz++] = { st,frac(1,1) };
	vis[st] = ++vid;
	for (int k = 0; k < sz; k++) {
		neigh(q[k].v, e, v) {
			if (vis[v] == vid) continue;
			vis[v] = vid;
			q[sz++] = { v,cost[e] * q[k].c };
			if (v == en) return true;
		}
	}
	return false;
}
char query;
char nameA[25], nameB[25];
int A, B;
int main() {
	//inoutfile;
	map<string, int> strtoint;
	int nodeID = 1;
	memset(head, -1, sizeof head);
	while (true){
		scanf(" %c", &query);
		if (query == '!') {
			scanf("%d %s = %d %s", &A, nameA, &B, nameB);
			if (strtoint[nameA]== 0)
				strtoint[nameA] = nodeID++;
			if (strtoint[nameB] == 0)
				strtoint[nameB] = nodeID++;
			
			add_edge(strtoint[nameA], strtoint[nameB], frac(A, B));
			add_edge(strtoint[nameB], strtoint[nameA], frac(B, A));
		}
		else if (query == '?') {
			scanf("%s = %s", nameA, nameB);
			if (BFS(strtoint[nameA], strtoint[nameB])) {
				printf("%d %s = %d %s\n", q[sz - 1].c.num, nameA, q[sz - 1].c.denom, nameB);
			}
			else {
				printf("? %s = ? %s\n", nameA, nameB);
			}
		}
		else break;
	}
}
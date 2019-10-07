#include <bits/stdc++.h>

using namespace std;
int tsts, n;

const int OFF = 50;
const int N = 2 * OFF + 2, M = 2 * N * N, OO = 0x3f3f3f3f;
int head[N], nxt[M], to[M], ne, cap[M], capcpy[M];
double cst[M];
void add_edge(int f, int t, double c, int flow) {
	nxt[ne] = head[f];
	to[ne] = t;
	cap[ne] = flow;
	cst[ne] = c;
	head[f] = ne++;
}
void add_flowedge(int u, int v, double c, int flow) {
	add_edge(u, v, c, flow);
	add_edge(v, u, -c, 0);
}

int src = N - 2;
int snk = N - 1;

double dis[N];
int parEdge[N];
bool bellman(int src, bool big) {
	int sign = 2 * big - 1;
	fill(dis, dis + N, 1e18);
	dis[src] = 0;
	parEdge[src] = -1;

	int x = N;
	while (x--) {
		for (int e = 0; e < ne; e++) {
			if (!capcpy[e]) continue;
			int u = to[e ^ 1], v = to[e];
			double c = sign * cst[e];
			if (dis[u] + c - dis[v] < -1e-5) {
				if (!x)	assert(0);
				dis[v] = dis[u] + c;
				parEdge[v] = e;
			}
		}
	}
	return dis[snk] != 1e18;
}
double augment() {
	int e;
	int u = snk;
	int mn = OO;
	while (~(e = parEdge[u])) {
		mn = min(mn, capcpy[e]);
		u = to[e ^ 1];
	}
	u = snk;
	double price = 0;
	while (~(e = parEdge[u])) {
		capcpy[e] -= mn;
		capcpy[e ^ 1] += mn;

		price += mn * cst[e];

		u = to[e ^ 1];
	}
	return price;
}

double flow(bool big) {
	memcpy(capcpy, cap, sizeof cap);
	double f = 0;
	while (bellman(src, big)) {
		double chg = augment();
		f += chg;
	}
	return f;
}
int P, I;

int x;
int main() {
	tsts = 0;
	while (scanf("%d%d", &P, &I), P || I) {
		tsts++;
		ne = 0;
		memset(head, -1, sizeof head);
		for (int i = 0; i < P; i++) {
			scanf("%d", &x);
			add_flowedge(src, i, 0, x);
		}
		for (int i = 0; i < I; i++) {
			scanf("%d", &x);
			add_flowedge(i + OFF, snk, 0, x);
		}
		for (int i = 0; i < P; i++) {
			for (int j = 0; j < I; j++) {
				double p;
				scanf("%lf", &p);
				if (p != -1)
					add_flowedge(i, j + OFF, p, OO);
			}
		}
		double f1 = flow(1);
		double f2 = flow(0);
		printf("Problem %d: %.2lf to %.2lf\n", tsts, f1, f2);
	}
}
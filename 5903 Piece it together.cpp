#include <bits/stdc++.h>

using namespace std;

const int N = 3 * 500 * 500, M = 4 * N, OO = 0x3f3f3f3f;
int head[N], nxt[2 * M], to[2 * M], ne;

void add_edge(int f, int t) {
	nxt[ne] = head[f];
	to[ne] = t;
	head[f] = ne++;
}
void add_biedge(int a, int b) { add_edge(a, b), add_edge(b, a); }

int n, off;
int blacks[N], blcksz;
int r, c;
int tsts;

int whiteToBlack[N];
int vis[N], vid;
bool findMatch(int u) {
	if (vis[u] == vid) return 0;
	vis[u] = vid;
	for (int e = head[u], v; v = to[e], ~e; e = nxt[e]) {
		if (whiteToBlack[v] == -1) {
			whiteToBlack[v] = u;
			return 1;
		}
		else {
			int x = whiteToBlack[v];
			if (findMatch(x)) {
				whiteToBlack[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
bool maxMatch() {
	memset(whiteToBlack, -1, n * sizeof whiteToBlack[0]);
	for (int i = 0; i < blcksz; i++) {
		++vid;
		if (!findMatch(blacks[i])) return 0;
	}
	for (int i = 0; i < blcksz; i++) {
		++vid;
		if (!findMatch(blacks[i] + off)) return 0;
	}
	return 1;
}

void init() {
	blcksz = ne = 0;
	memset(head, -1, n * sizeof head[0]);
}
int twoD(int i, int j) {
	return i * c + j;
}
char arr[507][507];
int di[] = { 1,-1,0,0 };
int dj[] = { 0,0,1,-1 };
int main() {
	scanf("%d", &tsts);
	while (tsts--) {
		scanf("%d%d", &r, &c);
		n = r * c * 2;
		off = n / 2;
		init();
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				scanf(" %c", &arr[i][j]);
				if (arr[i][j] == 'B')
					blacks[blcksz++] = twoD(i, j);
			}
		}
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (arr[i][j] == 'B') {
					if (i - 1 >= 0 && arr[i - 1][j] == 'W') {
						add_edge(twoD(i, j), twoD(i - 1, j));
					}
					if (i + 1 < r && arr[i + 1][j] == 'W') {
						add_edge(twoD(i, j), twoD(i + 1, j));
					}
					if (j - 1 >= 0 && arr[i][j - 1] == 'W') {
						add_edge(twoD(i, j) + off, twoD(i, j - 1));
					}
					if (j + 1 < c && arr[i][j + 1] == 'W') {
						add_edge(twoD(i, j) + off, twoD(i, j + 1));
					}
				}
			}
		}
		bool succ = maxMatch();
		if (succ) {
			for (int i = 0; i < r; i++) {
				for (int j = 0; j < c; j++) {
					if (arr[i][j] == 'W' && whiteToBlack[twoD(i, j)] == -1) {
						succ = 0;
					}
				}
			}
		}
		puts(succ ? "YES" : "NO");
	}
}
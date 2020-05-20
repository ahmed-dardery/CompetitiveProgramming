#include <bits/stdc++.h>
int tsts;

using namespace std;
typedef pair<int, int> pii;

const int N = 100, M = 5e5 + 7;
int n, m;
bool inbounds(int ni, int nj) {
	return (ni >= 0 && ni < n && nj >= 0 && nj < m);
}

char mp[N][N];
char x;
int tst = 0;

int vis[N][N][2], vid;
short mxd;
bool succ = 1;
void DFS(char i, char j, bool k, short depth = 1) {
	vis[i][j][k] = vid;
	mxd = max(depth, mxd);

	char ni, nj, nk;
	//left
	if (k == 0 && mp[i][j] == '/' || k == 1 && mp[i][j] == '\\') {
		ni = i, nj = j - 1;
		if (inbounds(ni, nj)) {
			nk = (mp[ni][nj] == '/');
			if (vis[ni][nj][nk] != vid)
				DFS(ni, nj, nk, depth + 1);
		}
		else
			succ = 0;
	}
	//right
	if (k == 0 && mp[i][j] == '\\' || k == 1 && mp[i][j] == '/') {
		ni = i, nj = j + 1;
		if (inbounds(ni, nj)) {
			nk = (mp[ni][nj] == '\\');
			if (vis[ni][nj][nk] != vid)
				DFS(ni, nj, nk, depth + 1);
		}
		else
			succ = 0;
	}
	//up
	if (k == 0) {
		ni = i - 1, nj = j;
		if (inbounds(ni, nj)) {
			nk = 1;
			if (vis[ni][nj][nk] != vid)
				DFS(ni, nj, nk, depth + 1);
		}
		else
			succ = 0;
	}
	//down
	if (k == 1) {
		ni = i + 1, nj = j;
		if (inbounds(ni, nj)) {
			nk = 0;
			if (vis[ni][nj][nk] != vid)
				DFS(ni, nj, nk, depth + 1);
		}
		else
			succ = 0;
	}
}
short ans, cycles;
int main() {
	//freopen("input.txt", "rt", stdin);
	while (scanf("%d%d", &m, &n), n && m) {
		++tst;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf(" %c", &x);
				mp[i][j] = x;
			}
		}
		++vid;
		ans = -1;
		cycles = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < 2; k++) {
					if (vis[i][j][k] == vid) continue;
					mxd = 0;
					succ = 1;
					if (DFS(i, j, k), succ) {
						ans = max(ans, mxd);
						++cycles;
					}
				}
			}
		}
		printf("Maze #%d:\n", tst);
		if (cycles == 0) puts("There are no cycles.");
		else printf("%d Cycles; the longest has length %d.\n", cycles, ans);
		puts("");
	}
}
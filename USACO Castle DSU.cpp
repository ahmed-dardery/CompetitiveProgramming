#include <bits/stdc++.h>
using namespace std;

#define neigh(u,e,v) for (int e = head[u], v; v = to[e], ~e; e = nxt[e])
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
int grid[55][55];

int sz[3025];
int leaf[3025];
int sets;

const char dirs[] = "WNES";
const int di[] = { 0,-1,0,1 };
const int dj[] = { -1,0,1,0 };

int maxRoom = 1, max2Room = 1, maxi, maxj;
char maxdir;

void init(int n) {
	iota(leaf, leaf + n, 0);
	fill(sz, sz + n, 1);
	sets = n;
}

int find(int x) {
	return (leaf[x] == x) ? x : leaf[x] = find(leaf[x]);
}
void join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return;
	if (sz[a] < sz[b]) swap(a, b); //a is guranteed to be bigger
	leaf[b] = a;
	sz[a] += sz[b];
	maxRoom = max(maxRoom, sz[a]);
	sets--;
}

int oneD(int i, int j) {
	return i * m + j;
}
int main()
{
	//inoutfile;
	unsync;
	scanf("%d %d", &m, &n);
	fori(n) forj(m)
		scanf("%d", &grid[i][j]);
	
	init(n*m);
	fori(n) forj(m){
		for(int k = 0; k < 2; ++k) {
			if (!(grid[i][j] & (1 << k)))
				join(oneD(i, j), oneD(i + di[k], j + dj[k]));
		}
	}
	forj(m) forirev(n) {
		for (int k = 1; k < 3; ++k) {
			int ni = i + di[k], nj = j + dj[k];
			int a, b;
			if (ni < 0 || nj >= m || (a = find(oneD(ni, nj))) == (b = find(oneD(i, j)))) continue;
			int newRoom = sz[a] + sz[b];
			if (newRoom > max2Room) {
				max2Room = newRoom;
				maxi = i + 1, maxj = j + 1;
				maxdir = dirs[k];
			}
		}
	}
	printf("%d\n%d\n%d\n%d %d %c\n", sets, maxRoom, max2Room, maxi, maxj, maxdir);

}
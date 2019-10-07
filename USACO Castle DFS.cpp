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
int roomID[55][55];
int roomSize[3025];
int ID = 0;
const char dirs[] = { 'W','N','E','S' };
const int di[] = { 0,-1,0,1 };
const int dj[] = { -1,0,1,0 };

int maxRoom = 0;

int DFS(int i, int j) {
	if (~roomID[i][j]) return 0;
	roomID[i][j] = ID;
	int res = 1;
	for (int k = 0; k < 4; ++k) {
		if (!(grid[i][j] & (1 << k))){
			res += DFS(i + di[k], j + dj[k]);
		}
	}
	roomSize[ID] = res;
	maxRoom = max(maxRoom, res);
	return res;
}
int main()
{
	//inoutfile;
	unsync;
	scanf("%d %d", &m, &n);
	fori(n) forj(m)
		scanf("%d", &grid[i][j]);
	
	memset(roomID, -1, sizeof roomID);

	fori(n) forj(m) {
		if (DFS(i, j)) ++ID;
	}
	int max2Rooms = 0;
	char maxdir;
	int maxi, maxj;
	forj(m) forirev(n) {
		for (int k = 1; k < 3; ++k) {
			if (grid[i][j] & (1 << k)) {
				int ni = i + di[k], nj = j + dj[k];
				if (ni < 0 || nj >= m) continue;
				int r1 = roomID[i][j];
				int r2 = roomID[ni][nj];
				int newRoom = roomSize[r1] + roomSize[r2];
				if (r1 != r2 && newRoom > max2Rooms){
					max2Rooms = newRoom;
					maxi = i+1, maxj = j+1;
					maxdir = dirs[k];
				}
			}
		}
	}
	printf("%d\n%d\n%d\n%d %d %c\n", ID, maxRoom, max2Rooms, maxi, maxj, maxdir);

}
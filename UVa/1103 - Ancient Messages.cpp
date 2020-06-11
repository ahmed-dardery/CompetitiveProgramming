#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define DEBUG(p) cerr << #p << ": " << p << endl
const int N = 300, OO = 0x3f3f3f3f;

int n, m;

bool grid[N][N];
int vis[N][N], vid;
int cmpId[N][N];

const int di[] = {1, -1, 0, 0};
const int dj[] = {0, 0, 1, -1};

void floodfill(int i, int j, int type, int id) {
    vis[i][j] = vid;
    cmpId[i][j] = id;
    for (int k = 0; k < 4; ++k) {
        int ni = i + di[k], nj = j + dj[k];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
        if (grid[ni][nj] != type) continue;
        if (vis[ni][nj] == vid) continue;
        floodfill(ni, nj, type, id);
    }
}

int nearestCmp;

int floodsearch(int i, int j) {
    vis[i][j] = vid;
    for (int k = 0; k < 4; ++k) {
        int ni = i + di[k], nj = j + dj[k];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
        if (grid[ni][nj] != 0) {
            nearestCmp = cmpId[ni][nj];
            continue;
        }
        if (vis[ni][nj] == vid) continue;
        floodsearch(ni, nj);
    }
    return nearestCmp;
}

int whiteCnt[N * N];

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    while (scanf("%d%d", &n, &m), n || m) {
        memset(whiteCnt, 0, n * m * sizeof whiteCnt[0]);
        ++vid;
        printf("Case %d: ", vid);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                char c;
                scanf(" %c", &c);
                if (c <= '9') c -= '0';
                else c += 10 - 'a';
                for (int k = 0; k < 4; ++k)
                    grid[1 + i][1 + j * 4 + k] = (c >> (3 - k)) & 1;
            }
        }
        m *= 4;

        n += 2, m += 2;

        for (int i = 0; i < n; ++i)
            grid[i][0] = grid[i][m - 1] = 0;
        for (int j = 0; j < m; ++j)
            grid[0][j] = grid[n - 1][j] = 0;


        floodfill(0, 0, 0, -1);

        int curId = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (vis[i][j] == vid || grid[i][j] == 0) continue;
                floodfill(i, j, 1, curId++);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (vis[i][j] == vid || grid[i][j] == 1) continue;
                ++whiteCnt[floodsearch(i, j)];
            }
        }
        const char *sym = "WAKJSD";
        vector<int> found(curId, 0);
        for (int q = 0; q < curId; ++q) {
            found[q] = sym[whiteCnt[q]];
        }
        sort(found.begin(), found.end());
        for (int i = 0; i < curId; ++i) {
            printf("%c", found[i]);
        }
        puts("");
    }

}

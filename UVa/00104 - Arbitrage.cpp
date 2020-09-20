#include <bits/stdc++.h>

#define endl '\n'

using namespace std;
typedef long long ll;
const int N = 25, M = 2 * N;
int n;

//<len, i, j>
double mat[N][N][N];
int mnK[N][N][N];


void printPathUtil(int l, int a, int b) {
    int &k = mnK[l][a][b];
    if (k == -1) return;
    //printPathUtil(l - 1, a, k);
    cout << k + 1 << " ";
    printPathUtil(l - 1, k, b);
}

void printPath(int l, int a, int b) {
    cout << a + 1 << " ";
    printPathUtil(l, a, b);
    cout << b + 1 << "\n";
}


void solve() {
    for (int len = 2; len <= n; ++len) {
        memset(mat[len], 0, sizeof mat[len]);
        memset(mnK[len], -1, sizeof mnK[len]);

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
//                    int x = rand() % (len - 1) + 1;
//                    double nv = mat[x][i][k] * mat[len - x][k][j];

                    double nv = mat[1][i][k] * mat[len - 1][k][j];
                    if (nv > mat[len][i][j]) {
                        mat[len][i][j] = nv;
                        mnK[len][i][j] = k;

                    }
                    if (mat[len][i][i] >= 1.01) {
                        printPath(len, i, i);
                        return;
                    }
                }
            }
        }
    }
    cout << "no arbitrage sequence exists\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef CLION
    freopen("in", "rt", stdin);
#endif

    while (cin >> n) {
        memset(mat[0], 0, sizeof mat[0]);
        memset(mat[1], 0, sizeof mat[1]);
        memset(mnK[0], -1, sizeof mnK[0]);
        memset(mnK[1], -1, sizeof mnK[1]);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    mat[1][i][i] = 1.0;
                    continue;
                }
                cin >> mat[1][i][j];
            }
        }
        solve();
    }
}

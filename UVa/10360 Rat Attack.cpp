#include <bits/stdc++.h>
#include <random>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e5 + 7, M = 1025 + 7;
const double OO = 2e18;
int n, m;

ll pre[M][M];
int arr[M][M];

void precalc() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            pre[i][j] = pre[i][j - 1] + pre[i - 1][j] - pre[i - 1][j - 1] + arr[i][j];
}

ll sum(int si, int sj, int ei, int ej) {
    return pre[ei][ej] - pre[si - 1][ej] - pre[ei][sj - 1] + pre[si - 1][sj - 1];
}

int d;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    //cout << fixed << setprecision(2);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    int t;
    int cnt;
    cin >> t;
    while (t--) {
        memset(arr, 0, sizeof arr);
        cin >> d;
        cin >> cnt;
        n = m = 1026;
        for (int i = 0; i < cnt; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            ++a,++b;
            arr[a][b] = c;
        }
        precalc();
        ll ans = 0;
        int bi=-1, bj=-1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int si = i - d, sj = j - d, ei = i + d, ej = j + d;
                si = max(si, 1), sj = max(sj, 1), ei = min(n, ei), ej = min(m, ej);
                ll curr = sum(si, sj, ei, ej);
                if (curr > ans){
                    ans = curr;
                    bi = i;
                    bj = j;
                }
            }
        }
        cout << --bi << " " << --bj << " " << ans << "\n";
    }
    return 0;
}

#include <bits/stdc++.h>

using namespace std;
#define endl '\n'

typedef long long ll;
const int N = 1e2 + 5;

ll x, y, z, s;

ll cnt[N][N][N];

ll sqr(ll v) {
    return v * v;
}

ll getSub(ll i, ll j, ll k) {
    ll V[2][3] = {
            {i - 1, j - 1, k - 1},
            {x - i, y - j, z - k}
    };
    ll NN[3] = {x, y, z};
    ll NC[3] = {y * z, x * z, x * y};
    ll NA = x * y * z;

    ll ans = NA * NA;
    for (int dim = 0; dim < 3; ++dim)
        for (int dir = 0; dir < 2; ++dir)
            ans -= sqr(V[dir][dim] * NC[dim]);

    for (int dim1 = 0; dim1 < 3; ++dim1)
        for (int dir1 = 0; dir1 < 2; ++dir1)
            for (int dim2 = dim1 + 1; dim2 < 3; ++dim2)
                for (int dir2 = 0; dir2 < 2; ++dir2)
                    ans += sqr((NA / NN[dim1] / NN[dim2]) * V[dir1][dim1] * V[dir2][dim2]);

    for (int dir1 = 0; dir1 < 2; ++dir1)
        for (int dir2 = 0; dir2 < 2; ++dir2)
            for (int dir3 = 0; dir3 < 2; ++dir3)
                ans -= sqr(V[dir1][0] * V[dir2][1] * V[dir3][2]);

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cout << fixed << setprecision(9);
#ifndef ONLINE_JUDGE
    freopen("input.in", "rt", stdin);
#endif
    int t;
    cin >> t;
    for (int vid = 1; vid <= t; ++vid) {

        cin >> x >> y >> z >> s;
        double total = 0;
        for (ll i = 1; i <= x; ++i) {
            for (ll j = 1; j <= y; ++j) {
                for (ll k = 1; k <= z; ++k) {
                    cnt[i][j][k] = getSub(i, j, k);
                    double pp = cnt[i][j][k] / double(x * x * y * y * z * z);
                    /*
                        p[i][j][k] = 0;
                        for (int u = 0; u < s; ++u) {
                            p[i][j][k] = pp + p[i][j][k] * (1 - 2 * pp);
                        }
                    */
                    total += 0.5 * (1 - pow(1 - 2 * pp, s));
                }
            }
        }
        cout << "Case " << vid << ": " << total << endl;
    }

}

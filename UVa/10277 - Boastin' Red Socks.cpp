#include <bits/stdc++.h>

using namespace std;
#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;
const int N = 50000;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cout << fixed << setprecision(9);
#ifndef ONLINE_JUDGE
    freopen("input.in", "rt", stdin);
#endif
    ll p, q;
    while (cin >> p >> q, q) {
        if (p == 0) {
            cout << "0 2\n";
            continue;
        }
        ll g = __gcd(p, q);
        p /= g, q /= g;
        ll bestR = 1e9, bestB = 1e9;
        for (ll r = 2; r <= N; ++r) {
            ll temp = (2 * r - 1);
            ll c = q * r * (1 - r);
            if (c % p != 0) continue;
            c = c / p + r * (r - 1);
            ll dis = temp * temp - 4 * c;
            if (dis < 0) continue;
            ll sq = sqrt(dis);
            if (sq * sq != dis) continue;
            ll b = -temp + sq;
            if (b % 2 != 0 || b < 0) continue;
            b /= 2;
            if (r + b <bestR+bestB)
                bestR = r, bestB = b;
            break;
        }
        if (bestR + bestB > N) cout << "impossible\n";
        else{
            cout << bestR << " " << bestB << endl;
        }
    }


}

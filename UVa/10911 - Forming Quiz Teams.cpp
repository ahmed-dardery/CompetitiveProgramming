#include <bits/stdc++.h>
#include <random>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e5 + 7;
const double OO = 2e18;
int n;

pii points[N];

double dist(pii a, pii b) {
    ll x = a.first - b.first;
    ll y = a.second - b.second;
    return sqrt(x * x + y * y);
}


double mem[N];
double solve(int msk) {
    if (msk == (1 << n) - 1) return 0;

    int pos = __builtin_ctz(~msk); //find number of trailing ones : find index of first zero
    double &ret = mem[msk];
    if (ret < OO) return ret;

    msk |= 1 << pos;

    for (int i = pos + 1; i < n; ++i) {
        if (msk & (1 << i)) continue;
        ret = min(solve(msk | 1 << i) + dist(points[pos], points[i]), ret);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cout << fixed << setprecision(2);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    int test = 0;
    while (cin >> n, n != 0) {
        ++test;
        n *= 2;
        for (int i = 0; i < n; ++i) {
            string s; cin >> s;
            cin >> points[i].first >> points[i].second;
        }
        fill(mem, mem + (1 << n), OO);
        cout << "Case " << test << ": " << solve(0) << '\n';
    }
}

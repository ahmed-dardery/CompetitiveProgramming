#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;

const int N = 2e5 + 7;

ll n, L, w;

pair<double, double> ranges[N];

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cout << fixed << setprecision(9);
#ifndef ONLINE_JUDGE
    freopen("input.in", "rt", stdin);
#endif
    while (cin >> n >> L >> w) {
        for (int i = 0; i < n; ++i) {
            ll off, r;
            cin >> off >> r;
            double x = 0;
            if (r > w / 2.0)
                x = sqrt(r * r - w * w / 4.0);
            ranges[i] = {off - x, off + x};
        }
        sort(ranges, ranges + n);
        double st, en;
        st = en = 0;
        int cnt = 0;
        double eps = 1e-9;
        for (int i = 0; i < n; ++i) {
            if (en - L >= -eps/2) break;
            if (ranges[i].first - st <= eps) {
                en = max(en, ranges[i].second);
            } else if (ranges[i].first - en > eps) {
                break;
            } else {
                st = en;
                ++cnt;

                en = max(en, ranges[i].second);
            }
        }
        ++cnt;

        if (en < L) {
            cout << -1 << endl;
        }else {
            cout << cnt << endl;
        }
    }
}

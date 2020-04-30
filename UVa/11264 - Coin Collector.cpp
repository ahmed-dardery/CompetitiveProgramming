#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 7;

int n, t;
ll coins[N];

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cout << fixed << setprecision(9);
#ifndef ONLINE_JUDGE
    freopen("input.in", "rt", stdin);
#endif
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> coins[i];
        }
        coins[n] = 1e18;
        ll total = 0;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (total + coins[i] < coins[i + 1]) {
                total += coins[i];
                ++cnt;
            }
        }
        cout << cnt << endl;
    }
}

#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 7;

int n, m;

int d[N], v[N];

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cout << fixed << setprecision(9);
#ifndef ONLINE_JUDGE
    freopen("input.in", "rt", stdin);
    freopen("output.out", "wt", stdout);
#endif
    while (cin >> n >> m, n || m) {
        for (int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        
        multiset<int> v;    //multiset because we need repetitions
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            v.insert(x);
        }
        
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            auto it = v.lower_bound(d[i]);     //smallest number >= d[i]
            
            if (it == v.end()) {        //no such number : no solution
                ans = -1;
                break;
            } else {
                ans += *it;
                v.erase(it);
            }
        }

        if (ans == -1) {
            cout << "Loowater is doomed!\n";
        } else {
            cout << ans << endl;
        }
    }
}

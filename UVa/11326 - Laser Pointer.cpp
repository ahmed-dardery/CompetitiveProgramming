#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
using namespace __gnu_pbds;
#define endl '\n'

typedef long long ll;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 2e4 + 5;

typedef pair<ll, ll> point;
#define X first
#define Y second


int main() {
    cout << fixed << setprecision(3);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif

    int t;
    cin >> t;

    while (t--) {
        double L, W, theta;
        cin >> L >> W >> theta;
        theta = theta * M_PI / 180;
        double d1 = L / cos(theta);
        double x = tan(theta) * L;
        x = fmod(x, 2 * W);
        if (x > W)
            x = 2 * W - x;
        double d2 = hypot(x, L);
        cout << d1 / d2 << endl;
    }
}

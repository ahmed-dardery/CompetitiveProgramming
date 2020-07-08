    #include <bits/stdc++.h>

    #define endl '\n'

    using namespace std;
    typedef long long ll;
    const int N = 1e5 + 7, M = 2 * N;

    int n;
    int arr[N];

    int main() {
        ios_base::sync_with_stdio(0), cin.tie(0);
    #ifdef CLION
        freopen("input.in", "rt", stdin);
        freopen("output.out", "wt", stdout);
    #endif

        int t;
        scanf("%d", &t);
        while (t--) {
            scanf("%d", &n);
            for (int i = 0; i < n; ++i) {
                scanf("%d", arr + i);
            }
            sort(arr, arr + n);
            ll cst = 0;
            vector<pair<int, int>> cross;
            while (n >= 4) {
                if (2 * arr[1] <= arr[n - 2] + arr[0]) {
                    cross.emplace_back(arr[0], arr[1]);
                    cross.emplace_back(arr[0], 0);
                    cross.emplace_back(arr[n - 2], arr[n - 1]);
                    cross.emplace_back(arr[1], 0);
                } else {
                    cross.emplace_back(arr[0], arr[n - 2]);
                    cross.emplace_back(arr[0], 0);
                    cross.emplace_back(arr[0], arr[n - 1]);
                    cross.emplace_back(arr[0], 0);
                }
                n -= 2;
            }
            if (n == 3) {
                cross.emplace_back(arr[0], arr[1]);
                cross.emplace_back(arr[0], 0);
                cross.emplace_back(arr[0], arr[2]);
            } else if (n == 2) {
                cross.emplace_back(arr[0], arr[1]);
            } else if (n == 1) {
                cross.emplace_back(arr[0], 0);
            }
            cst = accumulate(cross.begin(), cross.end(), 0ll,
                             [](ll v, pair<int, int> x) { return v + max(x.first, x.second); });
            printf("%lld\n", cst);
            for (auto v : cross) {
                if (v.second)
                    printf("%d %d\n", v.first, v.second);
                else
                    printf("%d\n", v.first);

            }
            if (t)
                puts("");
        }
    }

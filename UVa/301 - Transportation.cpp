#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e5 + 7;

int c, s, n;
struct order {
    int from, to, cnt;
} arr[N];
int i, cap, station;
int off[N];
int bestProfit = 0;
int profit = 0;

void solve() {
    if (i == n) {
        bestProfit = max(bestProfit, profit);
        return;
    }
    auto &cur = arr[i];

    int oldcap = cap;
    int oldstation = station;

    for (int i = station + 1; i <= cur.from; ++i)
        cap += off[i];
    station = cur.from;

    if (cap >= cur.cnt) {
        ++i;
        cap -= cur.cnt;
        off[cur.to] += cur.cnt;
        profit += cur.cnt * (cur.to - cur.from);
        solve();
        profit -= cur.cnt * (cur.to - cur.from);
        off[cur.to] -= cur.cnt;
        cap += cur.cnt;
        --i;
    }
    ++i;
    solve();
    --i;
    cap = oldcap;
    station = oldstation;
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    while (scanf("%d%d%d", &c, &s, &n), n || c || s) {
        for (int j = 0; j < n; ++j) {
            scanf("%d%d%d", &arr[j].from, &arr[j].to, &arr[j].cnt);
        }
        sort(arr,arr+n,[](order lhs, order rhs){return lhs.from < rhs.from;});
        bestProfit = 0;
        cap = c;
        solve();
        printf("%d\n", bestProfit);
    }
}
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1e5 + 7;

struct machine {
    ll day, profit, buy, sell;

    bool operator<(const machine &lhs) const {
        return day < lhs.day;
    }
} mach[N];

int n;

typedef pair<ll, ll> pll;
#define F first
#define S second

ll sub(const pll &L, ll x) {
    return L.F * x + L.S;
}

map<ll, ll> lines;

pll intersect(const pll &a, const pll &b) {
    return {b.S - a.S, a.F - b.F};
}

bool lessFrac(pll a, pll b) {
    return 1.0 * a.F * b.S < 1.0 * b.F * a.S;
}

bool keepLine(map<ll, ll>::iterator it) {
    if (it == lines.begin() || it == --lines.end()) return 1;
    auto prv = it, nxt = it;
    --prv, ++nxt;

    return lessFrac(intersect(*prv, *it), intersect(*it, *nxt));
}

ll solve() {
    lines.clear();
    lines.insert({0, 0});
    ll dp = 0;
    for (int i = 0; i < n; ++i) {
        ll x = mach[i].day;
        while (lines.size() > 1) {
            auto sc = lines.begin(), fs = sc++;
            if (sub(*fs, x) > sub(*sc, x)) break;
            else lines.erase(fs);
        }

        dp = sub(*lines.begin(), x);

        machine &MI = mach[i];

        if (dp < MI.buy) continue;
        ll m = MI.profit;
        ll c = dp - MI.buy - MI.profit * MI.day - MI.profit + MI.sell;

        auto it = lines.insert({m, c}).F;
        it->S = max(c, it->S);

        if (!keepLine(it)) lines.erase(it);
        else {
            while (it != --lines.end()) {
                auto cpy = it;
                ++cpy;
                if (!keepLine(cpy)) lines.erase(cpy);
                else break;
            }
            while (it != lines.begin()) {
                auto cpy = it;
                --cpy;
                if (!keepLine(cpy)) lines.erase(cpy);
                else break;
            }
        }
    }
    return dp;
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    int CASE = 0;
    ll init, days;

    while (scanf("%d%lld%lld", &n, &init, &days), n || init || days) {
        for (int i = 0; i < n; ++i) {
            machine &m = mach[i];
            scanf("%lld%lld%lld%lld", &m.day, &m.buy, &m.sell, &m.profit);
        }
        mach[n++] = {0, 0, 0, init};
        mach[n++] = {days + 1, 0, 0, 0};
        sort(mach, mach + n);
        printf("Case %d: %lld\n", ++CASE, solve());
    }
}

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 500;

typedef pair<ll, ll> point;
typedef pair<point, point> segment;

struct line {
    ll a, b, c;

    //a x + b y + c = 0
    line(ll x1, ll y1, ll x2, ll y2) {
        a = y2 - y1;
        b = -(x2 - x1);
        c = x2 * y1 - y2 * x1;
        ll g = abs(__gcd(a, __gcd(b, c)));
        if (a < 0 || (a == 0 && b < 0)) g *= -1;
        a /= g, b /= g, c /= g;
    }

    line(segment &x) : line(x.first.first, x.first.second, x.second.first, x.second.second) {}

    bool operator<(const line &rhs) const {
        typedef pair<ll, pair<ll, ll>> combo;
        return combo{a, {b, c}} < combo{rhs.a, {rhs.b, rhs.c}};
    }

    bool operator==(const line &rhs) const {
        typedef pair<ll, pair<ll, ll>> combo;
        return combo{a, {b, c}} == combo{rhs.a, {rhs.b, rhs.c}};
    }
};

const double eps = 1e-9;

bool pointOnSegment(const pair<double, double> &r, const segment &l) {
    bool afterStart = r >= pair<double, double>{l.first.first, l.first.second};
    bool beforeEnd = r <= pair<double, double>{l.second.first, l.second.second};
    return afterStart && beforeEnd;
}

bool intersect(const segment &lhs, const segment &rhs) {
    segment s1 = min(lhs, rhs);
    segment s2 = max(lhs, rhs);
    line l1(s1), l2(s2);
    if (l1 == l2) //same line
        return s2.first <= s1.second;
    else if (l1.a * l2.b == l1.b * l2.a) //parallel line
        return false;

    double x = (double) (l1.b * l2.c - l2.b * l1.c) / (double) (l1.a * l2.b - l2.a * l1.b);
    double y = (-l1.c - l1.a * x) / l1.b;
    pair<double, double> p = {x, y};

    return pointOnSegment(p, s1) && pointOnSegment(p, s2);
}

int n;
segment arr[N];
int vis[N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "rt", stdin);
#endif
    int t;
    cin >> t;
    for (int vid = 1; vid <= t; ++vid) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            point st, en;
            cin >> st.first >> st.second >> en.first >> en.second;
            if (en < st) swap(st, en);
            arr[i] = {st, en};
        }
        int seg = 0;
        for (int i = 0; i < n; ++i) {
            bool breakall = 0;
            for (int j = 0; j < n; ++j) {
                if (j == i)continue;
                if (intersect(arr[i], arr[j])) {
                    breakall = 1;
                    break;
                }
            }
            if (!breakall) seg++;
        }
        cout << seg << endl;
    }
}

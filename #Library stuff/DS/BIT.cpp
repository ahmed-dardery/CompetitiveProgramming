#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct BIT {
    vector<ll> m;

    BIT(int sz) : m(1 << int(__lg(sz) + 1)) {}

    void add(int i, ll v) {
        for (i++; i <= m.size(); i += (i & -i))
            m[i - 1] += v;

    }

    ll get(int i) {
        ll res = 0;
        for (i++; i; i -= (i & -i))
            res += m[i - 1];
        return res;
    }

    int find(ll val) {
        int st = 0;
        for (int s = m.size() >> 1; s; s >>= 1)
            if (val > m[st + s - 1])
                val -= m[(st += s) - 1];
        return st;
    }
};

struct BITRNG {
    vector<ll> m, c;

    BITRNG(int n) : m(n), c(n) {}

    void add(int i, ll dm, ll dc) {
        for (i++; i <= m.size(); i += (i & -i))
            m[i - 1] += dm, c[i - 1] += dc;

    }

    ll get(int i) {
        ll res = 0;
        int i2 = i;
        for (i++; i; i -= (i & -i))
            res += m[i - 1] * i2 + c[i - 1];
        return res;
    }

    void addRange(int st, int en, ll val) {
        add(st, val, -val * (st - 1));
        add(en + 1, -val, val * en);
    }
};

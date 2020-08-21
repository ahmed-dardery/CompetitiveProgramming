#include <bits/stdc++.h>

#define endl '\n'

using namespace std;
typedef long long ll;
const int N = 1e5 + 7, M = 2 * N;

int floydCycleSize(int start, int (*f)(int)) {
    int u = start, cnt = 0;
    do {
        u = f(u);
        cnt++;
    } while (u != start);
    return cnt;
}

int floydCycleStart(int x, int (*f)(int)) {
    int h = x, t = x;
    do {
        h = f(f(h));
        t = f(t);
    } while (h != t);
    h = x;
    while (h != t) {
        h = f(h);
        t = f(t);
    }
    return h;
}

pair<int, int> brent(int x, int (*f)(int)) {
    int lm, h, t, p;
    h = x;
    p = 1;
    do {
        t = h;
        for (lm = 1; lm <= p; ++lm) {
            h = f(h);
            if (h == t) break;
        }
        p <<= 1;
    } while (h != t);
    
    t = h = x;
    for (int i = 0; i < lm; ++i) {
        h = f(h);
    }
    while (h != t) {
        h = f(h);
        t = f(t);
    }
    return {h, lm};
}

int n = 101, c = 1;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef CLION
    freopen("in", "rt", stdin);
#endif
    auto f = [](int x) { return (x * x + c) % n; };
    int start, sz;
    tie(start, sz) = brent(2, f);
//    int start = floydCycleStart(2, f);
//    int sz = floydCycleSize(start, f);
    cout << start << " " << sz << endl << endl;
    int iter = 30;
    for (int x = 2; iter--; x = f(x)) {
        cout << x << " ";
    }
}

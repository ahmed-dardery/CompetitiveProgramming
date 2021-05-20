//#define MULTIPLE_TESTS 0
#include "bits/stdc++.h"
#include <ext/numeric>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template<typename T> using policy_set = tree<T, null_type, less < T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
struct mul {
    int m;
    mul(int m) : m(m) {}
    int operator()(int a, int b) { return 1ll * a * b % m; }
};
int identity_element(mul) { return 1; }
#define fastpower(a, b, m) power(a,b,mul(m))
#define endl '\n'
#define F first
#define S second
#define all(v) (v).begin(), (v).end()
#define SZ(v) int((v).size())
const int N = 82, M = 2 * N, MOD = 1e9 + 7, OO = 0x3f3f3f3f;

string pat;

int dp[N][N];
int factor(int st, int sz) {
    if (sz == 1) return 1;
    int &ret = dp[st][sz];
    if (~ret) return ret;
    ret = 1e9;
    for (int i = 1; i < sz; ++i)
        ret = min(ret, factor(st, i) + factor(st + i, sz - i));
    vi f(sz);
    auto getNewLen = [&](int len, char c) {
        while (len && pat[st + len] != c)
            len = f[len - 1];
        return len + (pat[st + len] == c);
    };
    f[0] = 0;
    for (int i = 1; i < sz; ++i)
        f[i] = getNewLen(f[i - 1], pat[st + i]);
    int patLen = sz - f[sz - 1];
    if (sz % patLen == 0)
        ret = min(ret, factor(st, patLen));
    return ret;
}

void MAIN(int tc = 0) {
    while (1) {
        cin >> pat;
        if (pat == "*") break;
        memset(dp, -1, sizeof dp);
        cout << factor(0, SZ(pat)) << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef CLION
    freopen("in", "rt", stdin);
#endif
#ifdef MULTIPLE_TESTS
    int nTests;
#if MULTIPLE_TESTS == 0
    scanf("%d", &nTests);
#else
    cin >> nTests;
#endif
    for (int tc = 1; tc <= nTests; ++tc) {
        MAIN(tc);
    }
#else
    MAIN();
#endif

}

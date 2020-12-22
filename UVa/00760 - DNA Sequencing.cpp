//#define MULTIPLE_TESTS
#include <bits/stdc++.h>
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
#define sz(v) int(v.size())
#define all(v) (v).begin(), (v).end()
const int N = 2e5 + 7, M = 2 * N, MOD = 1e9 + 7, OO = 0x3f3f3f3f;

//remove added 1 from n if cyclic
//change loop condition to j < n if c is needed.
struct SuffixArray {
    vi sa, lcp;
    vector <vi> c;
    SuffixArray(const string &s, int lim = 128) {
        int n = sz(s) + 1;
        vi x(all(s) + 1), y(sz(s) + 1), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            for (int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            for (int i = 0; i < n; ++i) ws[x[i]]++;
            for (int i = 1; i < lim; ++i) ws[i] += ws[i - 1];
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];

            swap(x, y), p = 1, x[sa[0]] = 0;

            for (int i = 1; i < n; ++i) {
                int a = sa[i - 1], b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
            c.emplace_back(x);
        }
        for (int i = 1; i < n; ++i) rank[sa[i]] = i;
        for (int k = 0, i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k];
        k++ );
    }
    int compareSubString(int i, int j, int sz) {
        int k = __lg(sz);
        if (c[k][i] != c[k][j])
            return c[k][i] - c[k][j];
        else
            return c[k][i + sz - (1 << k)] - c[k][j + sz - (1 << k)];
    }
};

int n, m, arr[N];
string str, str1, str2;

void MAIN() {
    bool first = 1;
    while(cin >> str1 >> str2) {
        if(first) first = 0;
        else cout << endl;
        str = str1 + '#' + str2;
        SuffixArray s(str);
        int best = 0;
        for (int i = 1; i < sz(s.sa); ++i) {
            if ((s.sa[i - 1] - sz(str1)) * (s.sa[i] - sz(str1)) < 0)
                best = max(best, s.lcp[i]);
        }
        if(best == 0){
            cout << "No common sequence.\n";
        }else {
            int lst = -1;
            for (int i = 1; i < sz(s.sa); ++i) {
                if ((s.sa[i - 1] - sz(str1)) * (s.sa[i] - sz(str1)) < 0 && s.lcp[i] == best) {
                    int j = min(s.sa[i - 1], s.sa[i]);
                    if(lst == -1 || s.compareSubString(lst, j, best) != 0)
                    cout << str1.substr(j, best) << endl;
                    lst = j;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef CLION
    freopen("in", "rt", stdin);
#endif
#ifdef MULTIPLE_TESTS
    int nTests;
    scanf("%d", &nTests);
    for (int tc = 1; tc <= nTests; ++tc) {
        MAIN(tc);
    }
#else
    MAIN();
#endif

}

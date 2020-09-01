//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>

#define endl '\n'

using namespace std;
typedef long long ll;
const int N = 1e5+7, M = N, A = 128;


struct PlainTree {
    int _str[N + 1], *str = _str + 1;
    int fail[N], nxt[N][A], len[N], pos[N], nNodes;
    int lazy[N], freq[N];

    int cur;

    int addNode(int l, int p) {
        memset(nxt[nNodes], -1, sizeof nxt[nNodes]);
        len[nNodes] = l;
        pos[nNodes] = p;
        lazy[nNodes] = 1;
        freq[nNodes] = 0;
        return nNodes++;
    }

    int getFailure(int u, int idx) {
        while (str[idx] != str[idx - len[u] - 1]) {
            u = fail[u];
        }
        return u;
    }

    void init() {
        nNodes = 0;
        addNode(-1, -1);
        addNode(0, 0);
        fail[0] = fail[1] = 0;
        cur = 0;
        str[-1] = -1;
    }

    void addChar(int idx, int c) {
        str[idx] = c;
        int u = getFailure(cur, idx);
        int &ch = nxt[u][c];
        if (~ch) {
            lazy[ch]++;
            cur = ch;
            return;
        }
        int v = addNode(len[u] + 2, idx - len[u] - 1);
        cur = ch = v;
        if (len[v] == 1)
            fail[v] = 1;
        else
            fail[v] = nxt[getFailure(fail[u], idx)][c];

    }

    void propagate() {
        for (int i = nNodes - 1; ~i; --i) {
            freq[i] += lazy[i];
            lazy[fail[i]] += lazy[i];
            lazy[i] = 0;
        }
    }

    void build(const char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            addChar(i, s[i]);
        }
        propagate();
    }
};

PlainTree tree;

string s;
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    cin >> s;
    tree.build(s.c_str());
    for (int i = 1; i < tree.nNodes; ++i) {
        cout << s.substr(tree.pos[i], tree.len[i]) << " " << tree.freq[i] << endl;
    }
}

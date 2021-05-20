#include "bits/stdc++.h"

#define endl '\n'

using namespace std;
typedef long long ll;
const int N = 1e5 + 7, M = 2 * N;

const string pad[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

template<char ST, int SZ>
struct trie {
    int nxt[N][SZ];
    vector<int> at[N];
    int nNodes;
    int addNode() {
        memset(nxt[nNodes], -1, sizeof nxt[nNodes]);
        at[nNodes].clear();
        return nNodes++;
    }
    void init() {
        nNodes = 0;
        addNode();
    }
    void insert(const string &s, int idx) {
        int cur = 0;
        for (char c : s) {
            c = tolower(c);
            int &chld = nxt[cur][c - ST];
            if (chld == -1)
                chld = addNode();
            cur = chld;
        }
        at[cur].push_back(idx);
    }
    bool inTrie(const string &s) {
        int cur = 0;
        for (char c : s) {
            c = tolower(c);
            int &chld = nxt[cur][c - ST];
            if (chld == -1)
                return 0;
            cur = chld;
        }
        return at[cur].size();
    }
    vector<int> fetch;
    void dfs(int u) {
        for (int idx : at[u])
            fetch.push_back(idx);
        for (int i = 0; i < SZ; ++i) {
            if (~nxt[u][i]) dfs(nxt[u][i]);
        }
    }
    string call;
    void get(int cur, int i) {
        if (i == call.size()) {
            dfs(cur);
            return;
        }
        if (call[i] <= '1') return;
        for (char c : pad[call[i] - '2']) {
            int &chld = nxt[cur][c - ST];
            if (chld == -1) continue;
            get(chld, i + 1);
        }
    }
    vector<int> solve(const string &str) {
        call = str;
        fetch.clear();
        get(0, 0);
        sort(fetch.begin(), fetch.end());
        return fetch;
    }

};
string vals[N];
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef CLION
    freopen("in", "rt", stdin);
#endif
    string fname, lname, code;
    trie<'a', 26> names;
    trie<'0', 10> codes;
    names.init();
    codes.init();
    int n = 0;
    while (cin >> fname) {
        if (isdigit(fname[0])) {
            if (fname.size() == 1) {
                puts("0");
                continue;
            }
            if (codes.inTrie(fname)) {
                puts(fname.c_str());
                continue;
            }
            vector<int> ret = names.solve(fname);
            if (ret.empty()) puts("0");
            for (int i = 0; i < ret.size(); ++i) {
                printf("%s%c", vals[ret[i]].c_str(), " \n"[i + 1 == ret.size()]);
            }
        } else {
            cin >> lname >> code;
            lname.insert(lname.begin(), fname.front());
            names.insert(lname, n);
            vals[n] = code;
            codes.insert(code, 1);
            ++n;
        }
    }
}

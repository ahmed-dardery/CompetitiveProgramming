#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 1;

char pat[N], str[N];
int F[N];

//I need to know what is the maximum number of characters that can be matched if c is included
int getNewLen(int len, char c) {
	while (len && c != pat[len])
		len = F[len - 1];

	return len + (c == pat[len]);
}
//00012345
//abcabcab
void computeF() {
	F[0] = 0;
	for (int i = 1; pat[i]; i++)
		F[i] = getNewLen(F[i - 1], pat[i]);

}

//returns vector of starting positions where pattern was found
vector<int> KMP() {
	computeF();
	int len = 0;
	vector<int> res;
	for (int i = 0; str[i]; ++i) {
		len = getNewLen(len, str[i]);
		if (!pat[len]) res.push_back(i - len + 1);
	}
	return res;
}



//remove added 1 from n if cyclic
//change loop condition to j < n if c is needed.
struct SuffixArray {
    vi sa, lcp;
    //vector<vi> c;
    SuffixArray(const string &s, int lim = 128) {
        int n = sz(s) + 1; 
        int a, b;
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
                a = sa[i - 1];
                b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
            //c.emplace_back(x);
        }
        for (int i = 1; i < n; ++i) rank[sa[i]] = i;
        for (int k = 0, i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k];
        k++ );
    }
};

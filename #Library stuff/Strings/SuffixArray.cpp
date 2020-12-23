struct SuffixArray {
    vi sa, lcp;
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
        }
        for (int i = 1; i < n; ++i) rank[sa[i]] = i;
        for (int k = 0, i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k];
        k++ );
    }
};


struct SuffixArray {
    vi sa, lcp;
    vector <vi> spt;
    vi iloc;
    SuffixArray(const string &s, int lim = 128) {
        int n = sz(s) + 1;
        vi x(all(s) + 1), y(sz(s) + 1), ws(max(n, lim)), rank(n);
        iloc = sa = lcp = y, iota(all(sa), 0);
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
        }
        for (int i = 1; i < n; ++i) rank[sa[i]] = i;
        for (int k = 0, i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k];
        k++ );

        spt.resize(n);
        for (int i = 0; i < n; ++i) {
            iloc[sa[i]] = i;
            spt[i].emplace_back(lcp[i]);
        }
        for (int j = 1; (1 << j) <= n; ++j)
            for (int i = 0; i + (1 << j) <= n; ++i)
                spt[i].emplace_back(min(spt[i][j - 1], spt[i + (1 << (j - 1))][j - 1]));
    }
    int lcpRange(int i, int j) {
        if (i == j) return sz(sa) - i - 1;
        i = iloc[i], j = iloc[j];
        if(j < i) swap(i, j);
        ++i;
        int l = __lg(j - i + 1);
        return min(spt[i][l], spt[j - (1 << l) + 1][l]);
    }
};

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



string s;
int p[N], c[N], c_tmp[N], ans[N];

void countSort(int arr[], const int comp[], int n) {
    memset(c_tmp, 0, n * sizeof c_tmp[0]);
    for (int i = 0; i < n; ++i)
        ++c_tmp[comp[i]];
    for (int i = 1; i < n; ++i)
        c_tmp[i] += c_tmp[i - 1];
    for (int i = n - 1; i >= 0; --i)
        ans[--c_tmp[comp[arr[i]]]] = arr[i];
    memcpy(arr, ans, n * sizeof arr[0]);
}

void suffix() {
    int n = s.size() + 1;
    iota(p, p + n, 0);
    sort(p, p + n, [](int a, int b) {
        return s[a] < s[b];
    });

    c[p[0]] = 0;
    for (int i = 1; i < n; ++i)
        c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; ++i)
            p[i] = (p[i] - k + n) % n;

        countSort(p, c, n);

        c_tmp[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            int a_st = p[i], a_en = (a_st + k) % n;
            int b_st = p[i - 1], b_en = (b_st + k) % n;
            c_tmp[a_st] = c_tmp[b_st] + (c[a_st] != c[b_st] || c[a_en] != c[b_en]);
        }

        memcpy(c, c_tmp, n * sizeof c[0]);
    }
}

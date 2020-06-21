#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

//given two random numbers 1<=a,b<=n, probability that min(a,b) <= i <= max(a,b)
inline ld prob(ll i, ll n) {
    //return (n * n - ((i - 1) * (i - 1) + (n - i) * (n - i))) / (1.0L * n * n);
    return (2 * i * (n - i + 1) - 1.0L) / (n * n);
}

ld ret[2][2];
ld tmp[2][2];
ld param[2][2];

inline void mul(ld mat1[2][2], ld mat2[2][2]) {
    memset(tmp, 0, sizeof tmp);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            tmp[i][j] = 0;
            for (int k = 0; k < 2; ++k)
                tmp[i][j] += mat1[i][k] * mat2[k][j];
        }
    memcpy(mat1, tmp, sizeof tmp);
}

void pow(ld mat[2][2], int p) {
    ret[0][0] = 1, ret[0][1] = 0, ret[1][0] = 0, ret[1][1] = 1;
    while (p) {
        if (p & 1) mul(ret, mat);
        mul(mat, mat);
        p >>= 1;
    }
}

ld total = 0;
int n, m, q, z;

void solveRange() {
    int mul;
    int halfN = (n + 1) / 2;
    int halfM = (m + 1) / 2;
    int halfQ = (q + 1) / 2;
    for (int i = 1; i <= halfN; ++i) {
        ld pi = prob(i, n);
        for (int j = 1; j <= halfM; ++j) {
            ld pij = pi * prob(j, m);
            for (int k = 1; k <= halfQ; ++k) {
                mul = 1 + !((n & 1) && (i == halfN));
                mul *= 1 + !((m & 1) && (j == halfM));
                mul *= 1 + !((q & 1) && (k == halfQ));
                ld p = pij * prob(k, q);
                param[0][0] = param[1][1] = 1 - p;
                param[0][1] = param[1][0] = p;
                pow(param, z);
                total += mul * ret[0][1];
            }
        }
    }
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    int tests;
    scanf("%d", &tests);

    for (int CASE = 1; CASE <= tests; ++CASE) {

        scanf("%d%d%d%d", &n, &m, &q, &z);
        total = 0;
        if (z != 0)
            solveRange();

        printf("Case %d: %.6lf\n", CASE, double(total));

    }
}

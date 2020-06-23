#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

//given two random numbers 1<=a,b<=n, probability that min(a,b) <= i <= max(a,b)
inline double prob(ll i, ll n) {
    //return (n * n - ((i - 1) * (i - 1) + (n - i) * (n - i))) / (1.0L * n * n);
    return (2 * i * (n - i + 1) - 1.0) / (n * n);
}

double power(double x, int p) {
    double ans = 1;
    while (p) {
        if (p & 1) ans *= x;
        x *= x;
        p >>= 1;
    }
    return ans;
}

double total = 0;
int n, m, q, z;

void solveRange() {
    int mul;
    int halfN = (n + 1) / 2;
    int halfM = (m + 1) / 2;
    int halfQ = (q + 1) / 2;
    for (int i = 1; i <= halfN; ++i) {
        double pi = prob(i, n);
        for (int j = 1; j <= halfM; ++j) {
            double pij = pi * prob(j, m);
            for (int k = 1; k <= halfQ; ++k) {
                mul = 1 + !((n & 1) && (i == halfN));
                mul *= 1 + !((m & 1) && (j == halfM));
                mul *= 1 + !((q & 1) && (k == halfQ));
                double p = pij * prob(k, q);
                double ans = 0.5 * (1 - power(1 - 2 * p, z));
                total += mul * ans;
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

        printf("Case %d: %.6lf\n", CASE, total);

    }
}

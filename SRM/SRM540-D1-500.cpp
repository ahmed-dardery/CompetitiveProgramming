#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 52;

template<typename T>
struct pre3D {
    T arr[N][N][N];
    int n, m, r;

    void build(int nn, int mm, int rr) {
        n = nn, m = mm, r = rr;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                for (int k = 1; k <= r; ++k) {
                    auto one = arr[i - 1][j][k] + arr[i][j - 1][k] + arr[i][j][k - 1];
                    auto two = arr[i - 1][j - 1][k] + arr[i - 1][j][k - 1] + arr[i][j - 1][k - 1];
                    auto three = arr[i - 1][j - 1][k - 1];
                    arr[i][j][k] += one - two + three;
                }
    }

    T query(int si, int sj, int sk, int ei, int ej, int ek) {
        if (ei < si || ej < sj || ek < sk) return 0;
        --si, --sj, --sk;
        si = max(0, si), sj = max(0, sj), sk = max(0, sk);
        ei = min(n, ei), ej = min(m, ej), ek = min(r, ek);

        auto zero = arr[ei][ej][ek];
        auto one = arr[si][ej][ek] + arr[ei][sj][ek] + arr[ei][ej][sk];
        auto two = arr[si][sj][ek] + arr[si][ej][sk] + arr[ei][sj][sk];
        auto three = arr[si][sj][sk];

        return zero - one + two - three;
    }
};

pre3D<double> prob1;
pre3D<double> prob2;

class RandomColoring {
public:
#define off(i, j, k, d) i-d, j-d, k-d, i+d, j+d, k+d

    int n, m, r;

    int count(int si, int sj, int sk, int ei, int ej, int ek) {
        if (ei < si || ej < sj || ek < sk) return 0;
        --si, --sj, --sk;
        si = max(0, si), sj = max(0, sj), sk = max(0, sk);
        ei = min(n, ei), ej = min(m, ej), ek = min(r, ek);
        return (ei - si) * (ej - sj) * (ek - sk);
    }

    double getProbability(int cnt, int maxR, int maxG, int maxB, int startR, int startG, int startB, int d1, int d2) {
        n = maxR, m = maxG, r = maxB;
        --d1;
        ++startR, ++startG, ++startB;

        memset(prob1.arr, 0, sizeof prob1.arr);
        prob1.arr[startR][startG][startB] = 1.0;

        for (int step = 1; step < cnt; ++step) {
            for (int i = 1; i <= maxR; ++i)
                for (int j = 1; j <= maxG; ++j)
                    for (int k = 1; k <= maxB; ++k) {
                        cout << i << j << k << " " << prob1.arr[i][j][k] << endl;
                        int cnt = (count(off(i, j, k, d2)) - count(off(i, j, k, d1)));
                        if (!cnt)
                            prob1.arr[i][j][k] = 0;
                        else prob1.arr[i][j][k] /= cnt;

                    }
            prob1.build(maxR, maxG, maxB);

            for (int i = 1; i <= maxR; ++i)
                for (int j = 1; j <= maxG; ++j)
                    for (int k = 1; k <= maxB; ++k) {
                        auto outer = prob1.query(off(i, j, k, d2));
                        auto inner = prob1.query(off(i, j, k, d1));
                        prob2.arr[i][j][k] = outer - inner;
                    }
            swap(prob1, prob2);
        }
        prob1.build(maxR, maxG, maxB);

        auto outer = prob1.query(off(startR, startG, startB, d2));
        auto inner = prob1.query(off(startR, startG, startB, d1));
        return 1.0 - (outer - inner);
    }

#undef off
};
//
//int main() {
//    ios_base::sync_with_stdio(0), cin.tie(0);
//#ifdef CLION
//    freopen("input.in", "rt", stdin);
//#endif
//    int n, maxR, maxG, maxB, startR, startG, startB, d1, d2;
//    cin >> n >> maxR >> maxG >> maxB >> startR >> startG >> startB >> d1 >> d2;
//    RandomColoring x;
//    cout << x.getProbability(n, maxR, maxG, maxB, startR, startG, startB, d1, d2) << endl;
//
//}

#include <complex>
#include <valarray>

using namespace std;

typedef complex<long double> comp;
long double PI = acosl(-1.0L);

const int MX_LOGN = 17, MX_N = 1 << MX_LOGN;
comp wk[MX_N / 2][MX_LOGN + 1];
int LOG2[MX_N + 1];

void precompute() {
    for (int log2n = 0; log2n <= MX_LOGN; log2n++) {
        int N = 1 << log2n;
        LOG2[N] = log2n;
        for (int k = 0; k < N / 2; k++)
            wk[k][log2n] = polar(1.0L, 2.0L * PI * k / N);
        
    }
}

void FFT(valarray<comp> &x, int neg = -1) {
    static int _ = (precompute(), 0);
    int N = x.size();
    if (N == 1) return;
    int lg = __builtin_ctz(N);
    for (int i = 1, j = 0; i < N - 1; i++) {
        for (int cur = (1 << (lg - 1)); !(cur & (j ^= cur)); cur >>= 1);
        if (i < j) swap(x[i], x[j]);
    }
    for (int hsz = 1, logN = 1; hsz < N; hsz <<= 1, logN++) {
        for (int s = 0; s < N; s += hsz << 1) {
            auto X = &x[s];
            for (int k = 0; k < hsz; k++) {
                auto even = X[k], odd = X[k + hsz];
                auto y0 = wk[k][logN];
                if (neg < 0) y0 = comp(y0.real(), -y0.imag());
                X[k] = even + y0 * odd;
                X[k + hsz] = even - y0 * odd;
            }
        }
    }
}

void IFFT(valarray<comp> &X) {
    FFT(X, 1);
    X /= comp(X.size());
}

typedef valarray<complex<long double>> valcomp;

valarray<long long> mulPoly(const valarray<int> &a, const valarray<int> &b) {
    int szRes = a.size() + b.size() - 1;
    int N = (1 << (int) ceil(log2(szRes)));
    valcomp ab(N);
    int mn = min(a.size(), b.size()), mx = max(a.size(), b.size());
    for (int i = 0; i < mn; ++i)
        ab[i] = complex<long double>(a[i], b[i]);
    for (int i = mn; i < a.size(); ++i)
        ab[i] = complex<long double>(a[i], 0);
    for (int i = mn; i < b.size(); ++i)
        ab[i] = complex<long double>(0, b[i]);

    FFT(ab);
    valcomp abREV = ab;
    abREV *= abREV;
    valcomp abREVCONJ = abREV;
    for (auto &x : abREVCONJ) x = conj(x);

    valcomp res(N);
    for (int i = 0; i < N; ++i) {
        int j = (N - i) & (N - 1);
        res[i] = (abREV[j] - abREVCONJ[i]) / complex<long double>(0, 4 * N);
    }

    FFT(res);
    valarray<long long> ret(N);
    for (int i = 0; i < N; ++i)
        ret[i] = (long long) llround(res[i].real());

    return ret;
}

#include <complex>
#include <valarray>

using namespace std;

typedef complex<long double> comp;
long double PI = acosl(-1.0L);
#define polar(x) polar(1.0L,x);

const int MX_LOGN = 17, MX_N = 1 << MX_LOGN;
comp wk[MX_N / 2][MX_LOGN + 1];
int LOG2[MX_N + 1];
void precompute() {
	for (int log2n = 0; log2n <= MX_LOGN; log2n++) {
		int N = 1 << log2n;
		LOG2[N] = log2n;
		for (int k = 0; k < N / 2; k++) {
			wk[k][log2n] = polar(2.0L * PI * k / N);
		}
	}
}
valarray<comp> FFT(const valarray<comp>& a, int neg = -1) {
	static int dummy = (precompute(), 0);

	int N = a.size();
	if (N == 1) return a;
	valarray<comp> even = a[slice(0, N / 2, 2)];
	valarray<comp> odd = a[slice(1, N / 2, 2)];
	even = FFT(even, neg);
	odd = FFT(odd, neg);
	valarray<comp> ret(N);
	for (int k = 0; k < N / 2; k++) {
		comp w = wk[k][LOG2[N]];
		w = { w.real(),w.imag()*neg };

		ret[k] = even[k] + w * odd[k];
		ret[N / 2 + k] = even[k] - w * odd[k];
	}
	return ret;
}
valarray<comp> IFFT(const valarray<comp>& a) {
	return FFT(a, 1) / comp(a.size());
}
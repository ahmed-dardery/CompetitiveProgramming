#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MX_LOGN = 15, MX_N = 1 << MX_LOGN;
const ll K = 1000002, MOD = K * MX_N + 1, W1 = 23139863998;


ll fastmul(ll x, ll p, ll m = MOD) {
	if (x + p < (ll)2e9)
		return x * p % MOD;
	ll res = 0;
	while (p) {
		if (p & 1) res = (res + x) % m;
		x = (x + x) % m;
		p >>= 1;
	}
	return res;
}

ll fastpow(ll x, ll p, ll m = MOD) {
	ll res = 1;
	while (p) {
		if (p & 1) res = fastmul(res, x);
		x = fastmul(x, x);
		p >>= 1;
	}
	return res;
}

ll wk[MX_N][MX_LOGN + 1][2];
int LOG2[MX_N + 1];
void precompute() {
	for (int log2n = 0; log2n <= MX_LOGN; log2n++) {
		int N = 1 << log2n;
		LOG2[N] = log2n;

		wk[0][log2n][0] = wk[0][log2n][1] = 1;
		wk[1][log2n][0] = fastpow(W1, MX_N / N);
		wk[1][log2n][1] = fastpow(wk[1][log2n][0], MOD - 2);

		for (int k = 2; k < N; k++) {
			wk[k][log2n][0] = fastmul(wk[k - 1][log2n][0], wk[1][log2n][0]);
			wk[k][log2n][1] = fastmul(wk[k - 1][log2n][1], wk[1][log2n][1]);
		}
	}
}
valarray<ll> NTT(const valarray<ll>& a, bool rev = 0) {
	static int dummy = (precompute(), 0);
	int N = a.size();
	int log2n = LOG2[N];
	if (N == 1) return a;
	valarray<ll> even = a[slice(0, N / 2, 2)];
	valarray<ll> odd = a[slice(1, N / 2, 2)];
	even = NTT(even, rev);
	odd = NTT(odd, rev);
	valarray<ll> ret(N);
	for (int k = 0; k < N / 2; k++) {
		ret[k] = (even[k] + fastmul(wk[k][log2n][rev], odd[k])) % MOD;
		ret[k + N / 2] = (even[k] + fastmul(wk[k + N / 2][log2n][rev], odd[k])) % MOD;
	}

	return ret;
}
valarray<ll> INTT(const valarray<ll>& a) {
	ll nneg = fastpow(a.size(), MOD - 2);
	valarray<ll> ret = NTT(a, 1);
	for (int i = 0; i < ret.size(); i++) {
		ret[i] = fastmul(ret[i], nneg);
	}
	return ret;
}
int n;
int tsts;

int main() {
	scanf("%d", &tsts);
	while (tsts--) {
		scanf("%d", &n);
		++n;
		int sz = 1 << int(ceil(log2(2 * n - 1)));
		valarray<ll> a(sz), b(sz);

		for (int i = 0; i < n; i++)
			scanf("%lld", &a[i]);

		for (int i = 0; i < n; i++)
			scanf("%lld", &b[i]);

		a = NTT(a);
		b = NTT(b);
		valarray<ll> c(sz);
		for (int i = 0; i < c.size(); i++) {
			c[i] = fastmul(a[i], b[i]);
		}
		c = INTT(c);
		for (int i = 0; i < 2*n-1; i++) {
			printf("%lld%c", c[i], " \n"[i == 2*n-2]);
		}
		
	}
}
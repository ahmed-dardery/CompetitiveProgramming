/*
TASK:
LANG: C++
*/
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <list>
#include <bitset>
#include <cstring>
#include <climits>
#include <deque>
#include <utility>
#include <complex>
#include <numeric>
#include <functional>
#include <stack>
#include <iomanip>
#include <ctime>
#include <valarray>
//#include "vc.h"
#ifdef _MSC_VER
#include <hash_set>
#include <hash_map>
using namespace stdext;
#else
#if __GNUC__ > 2
#include <ext/hash_set>
#include <ext/hash_map>
using namespace __gnu_cxx;
#else
#include <hash_set>
#include <hash_map>
#endif
#endif

template<class key>
struct hashtemp {

	enum {
		bucket_size = 4, min_buckets = 8
	};
	virtual size_t operator()(const key &p) const = 0;

};

using namespace std;
#ifndef M_PI
const long double M_PI = acos((long double)-1);
#endif
#define rep(i,n) for(int  i=0;i<(int)(n);++i)
long double ZERO = 0;
const long double INF = 1 / ZERO, EPSILON = 1e-12;
#define all(c) (c).begin(),(c).end()
#define rep2(i,a,b) for(int i=(a);i<=((int)b);++i)
#define foreach(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();++it)

#define sz(v) ((int)((v).size()))
#define let(x,y) __typeof(y) x(y)

#define rrep(i,n) for(int  i=((int)n)-1;i>=0;--i)
#define rall(c) (c).rbegin(),(c).rend()
#define rrep2(i,a,b) for(int i=(a);i>=((int)b);--i)
#define rforeach(it,c) for(__typeof((c).rbegin()) it=(c).rbegin();it!=(c).rend();++it)
#define rep2d(i, j, v) rep(i, sz(v)) rep(j, sz(v[i]))
#define foreach2d(i, j, v) foreach(i,v) foreach(j,*i)
typedef long long ll;
ll egcd(ll r0, ll r1, ll &x0, ll &y0) {
#define update(r0,r1) t=r0-r*r1,r0=r1,r1=t
	ll x1 = y0 = 0, y1 = x0 = 1, r, t;
	while (r1) {
		r = r0 / r1;
		update(r0, r1);
		update(x0, x1);
		update(y0, y1);
	}
	return r0;
}

bool solveLDE(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
	g = egcd(a, b, x, y);
	ll m = c / g;
	x *= m, y *= m;
	return !(c % g);
}





typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PI;

template<class T>
pair<T, T> EGCD(T A, T B) {
	if (B == 0) return make_pair(1, 0);
	pair<T, T> tmp = EGCD(B, A%B);
	return make_pair(tmp.second, tmp.first - tmp.second * (A / B));
}

template<class T>
T GCD(T A, T B) {
	while (B != 0) {
		T tmp = A % B;
		A = B;
		B = tmp;
	}
	return A;
}








LL CRT(const vector<PI>& E) {
	LL a = E[0].first;
	LL b = E[0].second;
	for (int i = 1; i < E.size(); ++i) {
		LL c = E[i].first;
		LL d = E[i].second;

		LL g = GCD(b, d);
		if ((c - a) % g != 0)
			return -1;
		LL in = EGCD(b / g, d / g).first;
		LL m = ((((c - a) / g) * in) % (d / g) + (d / g)) % (d / g);

		a += b * m;
		b = b * (d / g);
		a %= b;
		a += b;
		a %= b;
	}

	if (a == 0)
		return b;
	return a;
}


int main() {
	std::ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("1.in", "rt", stdin);
	freopen("1.out", "wt", stdout);
#endif
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<ll> r(n), m(n);
		vector<PI> E(n);
		ll M, R;
		rep(i, n)
			cin >> m[i] >> r[i], r[i] = (i & 1) ? m[i] - r[i] : r[i], E[i] = make_pair(r[i], m[i]);
		if ((R = CRT(E)) != -1)
			cout << R << endl;
		else
			cout << "Impossible\n";



	}
	return 0;
}
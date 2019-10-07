#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
using namespace __gnu_cxx;
typedef long long ll;
struct mat {
	int r, c;
	vector<vector<ll>> M;
	mat(int rr, int cc) : r(rr), c(cc) {
		M.resize(r, vector<ll>(c));
	}
	vector<ll>& operator[](int i) {
		return M[i];
	}
	const vector<ll>& operator[](int i) const {
		return M[i];
	}
};


struct mul {
	int r, c;
	ll m;
	mul(int rr, int cc, ll mm) : r(rr), c(cc), m(mm) {}

	mat operator()(const mat& m1, const mat& m2) const {
		mat ret(m1.r, m2.c);
		assert(m1.c == m2.r);
		for (int i = 0; i < m1.r; i++) {
			for (int j = 0; j < m2.c; j++) {
				for (int k = 0; k < m1.c; k++) {
					ret[i][j] += m1[i][k] * m2[k][j];
					ret[i][j] %= m;	
				}
			}
		}
		return ret;
	}
};
mat identity_element(const mul& m) {
	mat M(m.r, m.c);
	for (int i = 0; i < m.r; i++) {
		M[i][i] = 1;
	}
	return M;
}

int main() {
	mat mat1(3, 3);

	mat1[0] = { 1,0,0 };
	mat1[1] = { 0,0,1 };
	mat1[2] = { 1,1,1 };
	
	mat vec(3, 1);
	vec[0][0] = 2;
	vec[1][0] = 0;
	vec[1][0] = 0;

	ll n; ll b;
	int tsts = 0;
	while (scanf("%lld%lld", &n, &b), n || b) {
		tsts++;
		mul mu(3, 3, b);
		printf("Case %d: %lld %lld %lld\n", tsts ,n, b ,mul(3, 1, b)(power(mat1, n, mu), vec)[1][0] + 1);
	}
}
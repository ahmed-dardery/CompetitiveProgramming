/*
	Number Theory Basics
*/
#include <bits/stdc++.h>
#include <vector>
using namespace std;

typedef long long ll;

//Doesn't sort
vector<int> divisors(int n) {
	vector<int> v;
	int i;
	for (i = 1; i <= n / i; ++i) {
		if (n % i == 0 && i*i != n) {
			v.push_back(i);
			v.push_back(n / i);
		}
		if (i*i == n) v.push_back(i);
	}
	return v;
}

bool isPrime(int n) {
	for (int i = 2; i <= n / i; i += 1 + (i & 1) )
		if (n%i == 0) return 0;

	return n > 1;
}

//Prime count under N can be estimated by N / lnN
int prime[N];
void sieve() {
	memset(prime, 1, sizeof prime);
	prime[0] = prime[1] = 0;
	for (int i = 2; i <= N / i; i += 1 + (i & 1)) {
		if (prime[i])
			for (int j = i * i; j <= N; j += i)
				prime[j] = 0;
	}
}

vector<pair<int, int>> factorize(int n) {
	vector<pair<int, int>> v;
	for (int i = 2; i <= n / i; ++i) {
		int e = 0;
		while (n%i == 0) {
			n /= i;
			e++;
		}
		if (e) v.push_back({ i,e });
	}
	if (n > 1) v.push_back({ n,1 });
	return v;
}


ll GCD(ll a, ll b) {
	while (b) {
		ll t = a % b;
		a = b;
		b = t;
	}
	return a;
}

ll LCM(ll a, ll b) { return a / GCD(a, b) * b; }

ll MODN(ll a, ll b) {
	return (a%b + (b < 0 ? -b : b)) % b;
}

//Solves aX + bY = GCD(a,b)
//returns GCD for convenience.
#define update(t0,t) tmp = t, t = t0 - (a / b) * t, t0 = tmp
ll eGCD(ll a, ll b, ll &x0, ll &y0) {

	ll tmp, y = x0 = 1, x = y0 = 0;
	while (b)
		update(x0, x), update(y0, y), update(a, b);

	return a;
}
//Solves (aX + bY = c) as long as c == m * GCD(a,b)
//returns solvable, x, y are out paramters so the equation is solved with x (or y) as the minimum possible integer.
//general form: (X = x + k*b/g), (Y = y - k*a/g)

//that means either y = y * c + ((x * (c - 1)) / b) * a;
//				or  x = x * c + ((y * (c - 1)) / a) * b;
bool LDE(ll a, ll b, ll &x, ll &y, ll c, ll &g) {
    g = eGCD(a, b, x, y);
    if (c % g) return false;

    a /= g, b /= g, c /= g;		//we can reduce all of them by dividing by the GCD

	//smallest positive x
    x = x * c % b;
    if (b > 0) x = (x + b) % b;
    else if (x < 0) {
        ll k = (x + b - 1) / b;
        x -= k * b;
    }
    y = (c - a * x) / b;

    return true;
}
//Merges (X % m1 = r1) and (X % m2 = r2) into (X % m = r)
//returns solvable
bool combine(ll &m1, ll &r1, ll m2, ll r2) {

	ll x, y, g;
	if (!LDE(m1, m2, x, y, r2 - r1, g)) return false;
	//assert(MODN(x * m1 + r1, m1 * (m2 / g)) == MODN(- y * m2 + r2, m1 * (m2 / g)));
	r1 = x * m1 + r1;
	m1 = m1 * (m2 / g);
	r1 = MODN(r1, m1);
	return true;
}

//Chinese Remainder theorm (X % m[i] = r[i])
bool CRT(const ll m[], const ll r[], int n, ll &m0, ll &r0) {
	m0 = m[0], r0 = r[0];
	for (int i = 1; i < n; i++)
		if (!combine(m0, r0, m[i], r[i])) return false;

	return true;
}

//Alternative modInverse(x,p) = x^(phi(p)-1) if p and x are coprime
//Or modInverse(x,p) = x^(p-2) p is prime;
ll modInverse(ll &x, ll mod) {
	ll res,y;
	if (!LDE(x, mod, res, y, 1)) return -1;
	return res;
}

ll power(ll x, ll p, ll m) {
	//fermat's little theorem
	//p = p % (m - 1);
	ll res = 1;
	while (p) {
		if (p & 1) res = (res * x) % m;
		x = (x*x) % m;
		p >>= 1;
	}
	return res;
}

ll countFactorialFactors(ll n, ll p) {
	ll count = 0;
	while (n)
		count += (n /= p);

	return count;
}

ll combmem[100][100];
ll Combination(int n, int k) {
	if (n == k) return 1;
	if (k == 0) return 1;
	ll & ret = combmem[n][k];
	if (ret != 0) return ret;
	else return ret = Combination(n - 1, k - 1) + Combination(n - 1, k);
}
//phi(p) = p-1 <- p is prime
ll phi(ll x) {
	ll res = x;
	for (ll i = 2; i <= x / i; i += 1 + (i & 1)) {
		if (x % i) continue;
		while (x % i == 0)
			x /= i;
	
		res -= res / i;
	}
	if (x != 1) res -= res / x;
	return res;
}

//powers of ten mod 1e9 + 7
const int N = 2e5;
const ll MOD = 1e9 + 7;
ll TENS[2 * N];
ll* tens = TENS + N;
const ll tenth = 700000005;
void init_tens() {
	tens[-1] = 700000005;
	for (int i = 0; i < 1e5; i++) {
		tens[i] = (tens[i - 1] * 10) % MOD;
	}
	for (int i = -1; i > -1e5; i--) {
		tens[i] = (tens[i + 1] * tens[-1]) % MOD;
	}
}

void gauss() {

	for (int i = 0; i < n; i++) {
		// Search for maximum in this column
		double maxEl = abs(A[i][i]);
		int maxRow = i;
		for (int k = i + 1; k < n; k++) {
			if (abs(A[k][i]) > maxEl) {
				maxEl = abs(A[k][i]);
				maxRow = k;
			}
		}

		// Swap maximum row with current row (column by column)
		for (int k = i; k < n + 1; k++) {
			double tmp = A[maxRow][k];
			A[maxRow][k] = A[i][k];
			A[i][k] = tmp;
		}

		// Make all rows below this one 0 in current column
		for (int k = i + 1; k < n; k++) {
			double c = -A[k][i] / A[i][i];
			for (int j = i; j < n + 1; j++) {
				if (i == j) {
					A[k][j] = 0;
				}
				else {
					A[k][j] += c * A[i][j];
				}
			}
		}
	}

	// Solve equation Ax=b for an upper triangular matrix A
	vector<double> x(n);
	for (int i = n - 1; i >= 0; i--) {
		x[i] = A[i][n] / A[i][i];
		for (int k = i - 1; k >= 0; k--) {
			A[k][n] -= A[k][i] * x[i];
		}
	}
}

// Returns count of numbers in [A B] that 
// are divisible by M. 
int countDivisibles(int A, int B, int M) 
{ 
    // Add 1 explicitly as A is divisible by M 
    if (A % M == 0) 
        return (B / M) - (A / M) + 1; 
  
    // A is not divisible by M 
    return (B / M) - (A / M); 
} 

//counts numbers between s and e (inclusive) where n % x == m
ll count_mod_x(ll x, ll s, ll e, ll m) {
	return (e - s + x - ((m - s) % x + x) % x) / x;
}

ll count_new(ll x, ll e, ll m) {
    return e / x + (m > 0 && m <= e-e/x*x);
}
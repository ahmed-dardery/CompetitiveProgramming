#include <bits/stdc++.h>

using namespace std;
typedef long long lng;

#define MODN(a,b) (((a)%(b)+(b))%(b))

//Solves aX + bY = GCD(a,b)
//returns GCD for convenience.
#define update(t0,t) tmp = t, t = t0 - (a / b) * t, t0 = tmp
lng eGCD(lng a, lng b, lng &x0, lng &y0) {

	lng tmp, y = x0 = 1, x = y0 = 0;
	while (b)
		update(x0, x), update(y0, y), update(a, b);

	return a;
}
//Solves (aX + bY = c) as long as c == m * GCD(a,b)
//returns solvable
//general form: (X = x - k*b/g), (Y = y + k*a/g)
bool LDE(lng a, lng b, lng &x, lng &y, lng c, lng &g) {
	g = eGCD(a, b, x, y);
	if (c % g) return false;

	a /= g, b /= g, c /= g;
	x = MODN(x * c, b);
	y = y * c + ((x * (c - 1)) / b) * a;
	return true;
}
//Merges (X % m1 = r1) and (X % m2 = r2) into (X % m = r)
//returns solvable
bool combine(lng &m1, lng &r1, lng m2, lng r2) {
	lng x, _, g;
	if (!LDE(m1, m2, x, _, r2 - r1, g)) return false;
	r1 = x * m1 + r1;
	m1 = m1 * (m2 / g);
	r1 = MODN(r1, m1);
	return true;
}

//Chinese Remainder theorm (X % m[i] = r[i])
bool CRT(const lng m[], const lng r[], int n, lng &m0, lng &r0) {
	m0 = m[0], r0 = r[0];
	for (int i = 1; i < n; i++)
		if (!combine(m0, r0, m[i], r[i])) return false;

	return true;
}

const lng N = 5005, OO = 0x7fffffffffffffff;


lng setID[N], sz[N], nodeID[N];

lng pos[N], nxt[N];
lng n;

void init() {
	memset(nodeID, -1, 5 * n * sizeof nodeID[0]);
	memset(setID, -1, 5 * n * sizeof setID[0]);
	memset(sz, 0, 5 * n * sizeof sz[0]);
}

int main() {
	
	while (scanf("%lld", &n) != EOF && n != 0) {
		init();

		for (lng i = 0; i < 2 * n; i++) {
			lng *p = nxt + (i % n) * 5 + (i / n) * 2;
			*(p++) = i * 2;
			*p = i * 2 + 1;
		}
		for (lng i = 4 * n; i < 5 * n; i++) {
			lng *p = nxt + (i % n) * 5 + 4;
			*p = i;
		}
		lng set = 0;
		for (lng i = 0; i < 5 * n; ++i) {
			lng x;
			scanf("%lld", &x);
			pos[x] = i;

			lng curr = i;
			lng c = 0;

			while (setID[curr] == -1) {
				nodeID[curr] = c++;
				setID[curr] = set;
				curr = nxt[curr];
				sz[set]++;
			}
			set++;
		}
		lng m[5], r[5];
		lng mn = OO;
		lng player;
		for (lng i = 0; i < n; ++i) {
			lng prem[] = { 1,2,3,4,5 };
			do {
				bool succ = true;
				for (lng d = 0; d < 5; d++) {
					lng node1 = pos[prem[d]];
					lng node2 = i * 5 + d;
					if (setID[node1] == setID[node2]) {
						r[d] = nodeID[node1] - nodeID[node2];
						m[d] = sz[setID[node1]];
					}
					else {
						succ = 0;
						break;
					}
				}
				if (!succ) continue;

				lng m0, r0;
				if (CRT(m, r, 5, m0, r0)) {
					if (r0 == 0)
						r0 = m0;

					if (r0 < mn) {
						mn = r0;
						player = i + 1;
					}
				}

			} while (next_permutation(prem, prem + 5));
		}
		if (mn == OO) puts("Neverending game.");
		else printf("Player %lld wins game number %lld.\n", player, mn);

	}

}
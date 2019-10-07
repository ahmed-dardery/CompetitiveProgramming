
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;

//Entries per test case
#ifdef ONLINE_JUDGE
const int N = 1500;
#else
const int N = 10;
#endif
ull entries[N];

//Number of polynomial terms
const int C = 7;

//[level][power][x]
ull coeff[C][C][C];

//[level][power] the first row
ull first_coeff[C][C] = {
	{ 1, 1, 1, 1,  1,  1,  1 },
	{ 0, 1, 3, 7,  15, 31,  63 },
	{ 0, 0, 2, 12, 50, 180, 602 },
	{ 0, 0, 0, 6,  60, 390, 2100 },
	{ 0, 0, 0, 0,  24, 360, 3360 },
	{ 0, 0, 0, 0,  0,  120, 2520 },
	{ 0, 0, 0, 0,  0,  0,   720 } };

//[level][x]
ull values[C][C];

void fill_coeff() {
	//in the zeroth level, for constant a0, the coefficient is x^a = 1
	for (int x = 0; x < C; ++x) {
		coeff[0][0][x] = 1;
	}
	//in the zeroth level, for constants a1 through a6, the coefficent is x^a
	//thus we set the coefficent of a_n to a_(n-1) * x
	//notice that the x is 0-based
	for (int a = 1; a < C; ++a) {
		for (int x = 0; x < C; ++x) {
			coeff[0][a][x] = coeff[0][a - 1][x] * (x + 1);
		}
	}
	//for subsequent levels, we can generate the coefficents by subtracting the levels
	for (int lvl = 1; lvl < C; ++lvl) {
		for (int a = 0; a < C; ++a) {
			for (int x = 0; x < C - lvl; ++x) {
				coeff[lvl][a][x] = coeff[lvl - 1][a][x + 1] - coeff[lvl - 1][a][x];
			}
		}
	}

	//we only truly care about the first row:
	for (int lvl = 0; lvl < C; ++lvl) {
		for (int a = 0; a < C; ++a) {
			first_coeff[lvl][a] = coeff[lvl][a][0];
		}
	}
	//as it turns out, this is the triangular array OEIS A028246
	
	//notice this function doesn't get called, it's precalculated
}

int generate_levels() {
	bool allsame;
	for (int i = 0; i < C; ++i) {
		values[0][i] = entries[i];
		allsame &= (values[0][i] == values[0][0]);
	}
	if (allsame) return 0;


	for (int k = 1; k < C; ++k) {
		allsame = 1;
		for (int i = 0; i < C - k; ++i) {
			values[k][i] = values[k - 1][i + 1] - values[k - 1][i];
			allsame &= (values[k][i] == values[k][0]);
		}
		if (allsame) return k;
	}
}

ull sol[C];
bool find_solution(int k) {
	fill(sol + k + 1, sol + C, 0);
	for (int i = k; i >= 0; --i) {
		if (values[i][0] % first_coeff[i][i] != 0) return 0;
		sol[i] = values[i][0] / first_coeff[i][i];
		if (sol[i] > 1000) return 0;
		for (int j = k - 1; j >= 0; --j) {
			values[j][0] -= first_coeff[j][i] * sol[i];
		}
	}
	return 1;
}

bool verify_solution() {
	for (int i = 0; i < N; ++i) {
		ull myans = 0;
		ull x = 1;
		for (int j = 0; j < C; ++j) {
			myans += sol[j] * x;
			x *= (i + 1);
		}
		if (myans != entries[i]) return 0;
	}
	return 1;
}

int tsts;
int main() {
	//fill_coeff();
	scanf("%d", &tsts);
	while (tsts--) {
		for (int i = 0; i < N; ++i) {
			scanf("%llu", &entries[i]);
		}
		int k = generate_levels();
		if (find_solution(k) && verify_solution()) {
			for (int i = 0; i < C; ++i) {
				printf("%llu%c", sol[i], (i == C - 1 ? '\n' : ' '));
			}
		}
		else {
			puts("This is a smart sequence!");
		}

	}

}
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#ifndef M_PI
const long double M_PI = acos((long double)-1);
#endif

using namespace std;

typedef long long ll;

typedef complex<double> point;
#define polar(r,t) ((r)*exp(point(0,(t))))
#define polardeg(r,a) polar((r),(t) * M_PI/360)

const int N = 2e6 + 5, M = 1e2 + 5, OO = 0x7f7f7f7f7f7f7f7f;

typedef long long ll;
typedef pair<point, point> segment;




template<class T>
T GCD(T a, T b) {
	while (b) {
		T t = a % b;
		a = b;
		b = t;
	}
	return a;
}

#ifdef _DEBUG
#define __gcd(a,b) gcd(a,b)
#endif
struct line {
	ll a, b, c;

	line(ll x1, ll y1, ll x2, ll y2) {
		a = y2 - y1;
		b = x1 - x2;
		c = -a * x1 - b * y1;
		auto g = abs(__gcd(a, __gcd(b, c)));
		if (a < 0 || a == 0 && b < 0) g *= -1;
		a /= g;
		b /= g;
		c /= g;
	}

	bool operator < (const line &q) const {
		if (a != q.a) return a < q.a;
		else if (b != q.b) return b < q.b;
		else return c < q.c;
	}
};

double polygonArea(vector<pair<double, double>> points) {
#define X first
#define Y second
	double sum = 0;
	for (int i = 0; i < points.size() - 1; i++) {
		sum += points[i].X*points[i + 1].Y - points[i + 1].X*points[i].Y;
	}
	return sum / 2;
}


/*
def ccw(a, b, c):
	dx1 = b[0] - a[0];
	dx2 = c[0] - a[0];
	dy1 = b[1] - a[1];
	dy2 = c[1] - a[1];
	if dx1*dy2 > dy1*dx2;
		return 1;
	if dx1*dy2 < dy1*dx2;
		return -1;
	return 0;
*/
bool ccw(point& a, point& b, point& c) {
	auto dx1 = b.real - a.real;
	auto dx2 = c.real - a.real;
	auto dy1 = b.imag - a.imag;
	auto dy2 = c.imag - a.imag;
	if (dx1*dy2 == dy1 * dx2) //do double comparison if neccessary
		return 0;
	else if (dx1*dy2 > dy1*dx2)
		return 1;
	else
		return 0;
}


struct cmpY {
	bool operator()(const point&a, const point&b) const {
		if (a.Y != b.Y)
			return a.Y < b.Y;
		else
			return a.X < b.X;
	}
};
const double INF = 1e18;
double linesweep() {
	sort(events, events + nEvents);
	double d = INF;
	multiset<point, cmpY> active;
	int left = 0;
	for (int right = 0; right < n; right++) {
		while (left < right && events[right].X - events[left].X > d)
			active.erase(active.find(events[left++]));

		auto itS = active.lower_bound({ -INF, events[right].Y - d });
		auto itE = active.upper_bound({ -INF, events[right].Y + d });
		for (; itS != itE; ++itS)
			d = min(d, dist(*itS, events[right]));

		active.insert(events[right]);
	}
	return d;
}

typedef long long ll;

bool valid(ll);
bool valid(double);

double BS_double() {
	double st = 0, en = 1e9;
	double size = en - st;
	for (size /= 2; size > 1e-7; size /= 2) {
		if (!valid(st + size))
			st += size;
	}
}
//FFFFFFFFFTTTTTTTTTT
ll BS_first() {
	ll st = 0, en = 1e18;
	ll mid;
	while (st < en) {
		mid = st + (en - st) / 2;
		if (!valid(mid))
			st = mid + 1;
		else
			en = mid;
	}
}
//TTTTTTTTTTFFFFFFFFFFF
ll BS_last() {
	ll st = 0, en = 1e18;
	ll mid;
	while (st < en) {
		mid = st + (en - st + 1) / 2;
		if (valid(mid))
			st = mid;
		else
			en = mid - 1;
	}
}
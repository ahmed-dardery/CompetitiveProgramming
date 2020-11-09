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
	ll st = 0, en = 1e18 + 1;
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
	ll st = -1, en = 1e18;
	ll mid;
	while (st < en) {
		mid = st + (en - st + 1) / 2;
		if (valid(mid))
			st = mid;
		else
			en = mid - 1;
	}
}


//FFFFFFFFFFFTTTTTTTTTTTTT

//Use when the ok function for BS does N iterations, but you have M queries
//PBS(0, m-1, 0, n-1)
void PBS(int st, int en, int lf, int rt) {
    if (rt < lf) return;
    if (st == en) {
        for (int i = lf; i <= rt; ++i) {
            answer[sorted[i]] = st;
        }
        return;
    }

    int md = (st + en) / 2;

    while(curT > md){
        --curT;
        rollback(); //equivalent of one backward iteration in the ok function
    }
    while(curT > md){
        perform();  //equivalent of one forward iteration in the ok function
        ++curT;
    }

    int pivot = partition(sorted + lf, sorted + rt + 1, [](int v) {
        return ok(v, md);
    }) - statSort;

    PBS(st, md, lf, pivot - 1);
    PBS(md + 1, en, pivot, rt);
}

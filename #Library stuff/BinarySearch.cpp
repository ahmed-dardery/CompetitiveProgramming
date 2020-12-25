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

//Use when the ok(md) does md iterations
//iota(sorted, sorted+m, 0)
//PBS(0, n-1, 0, m-1) //m queries
int sorted[N], answer[N], curT = 0;
void PBS(int st, int en, int lf, int rt) {
    if (rt < lf) return;
    if (st == en) {
        for (int i = lf; i <= rt; ++i) {
            answer[sorted[i]] = st;
        }
        return;
    }

    int md = (st + en) / 2;

    while (curT > md) {
        rollback(--curT); //equivalent of one backward iteration in the ok function
    }
    while (curT < md) {
        perform(curT++);  //equivalent of one forward iteration in the ok function
    }

    int pivot = partition(sorted + lf, sorted + rt + 1, [](int qi) {
        return ok(qi);  //assume you've done your md loop
    }) - sorted;

    PBS(st, md, lf, pivot - 1);
    PBS(md + 1, en, pivot, rt);
}



    //TTTTTTTFFFFFFF
    //st = just before range
    //en = just after range
    //st, en becomes the separation wall.
    int st = -1, en = n;
    while(en - st > 1){
        int md = st+(en-st)/2;
        if(ok(md))
            st = md;
        else
            en = md;
    }

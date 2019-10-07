#include <bits/stdc++.h>
using namespace std;

class FairWorkload {
public:
	int getMostWork(vector<int> folders, int workers) {
		int n = folders.size();
		vector<int> vals(n);
		vals[0] = folders[0];
		for (int i = 1; i < n; ++i)
			vals[i] = vals[i - 1] + folders[i];

		int st = 1, en = 16 * 1000;
		int mid;
		while (st < en) {
			mid = st + (en - st) / 2;
			if (!valid(mid,vals,workers))
				st = mid + 1;
			else
				en = mid;
		}
		return st;
	}
private:
	bool valid(int &x, vector<int> vals, int &k) {
		int begin = 0;
		for (int i = 0; i < k; ++i) {
			auto it = upper_bound(vals.begin(), vals.end(), x + begin);
			if (it == vals.end()) return true;
			begin = *(it - 1);
		}
		return false;
	}
};
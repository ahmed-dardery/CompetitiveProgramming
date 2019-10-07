#include <bits/stdc++.h>
using namespace std;

#define inoutfile freopen("input.txt", "rt", stdin);freopen("output.txt", "wt", stdout)

const int N = 1001;
int n, a[N];

int mem[N];

int dp(int i = n - 1) {
	int &ret = mem[i];
	if (~ret) return ret;
	ret = 1;
	for (int k = i - 1; ~k; --k) {
		if (a[k] < a[i])
			ret = max(ret, dp(k)+1);
	}
	return ret;
}
/*
void print(int i) {
	
	int ret = dp(i);
	for (int k = i - 1; ~k; --k) {
		if (a[k] < a[i] && ret == dp(k) + 1) {
			print(k);
			break;
		}
	}
	printf("%d ", a[i]);
}
*/
vector<int> curr;
void printAll(int i) {

	int ret = dp(i);
	bool first = true;
	curr.push_back(a[i]);
	for (int k = i - 1; ~k; --k) {
		if (a[k] < a[i] && ret == dp(k) + 1) {
			first = false;
			printAll(k);
		}
	}
	if (first){
		for (int i = (int)curr.size() - 1; i >= 0; --i)
			printf("%d ", curr[i]);
		puts("");
	}
	curr.pop_back();
}
int main() {
	memset(mem, -1, sizeof mem);
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	
	int mx = 0;
	int maxi = -1;
	for (int i = 0; i < n; ++i) {
		int res = dp(i);
		if (res > mx) {
			mx = res;
			maxi = i;
		}
	}
	printf("%d\n",mx);
	for (int i = 0; i < n; ++i) {
		int res = dp(i);
		if (dp(i) == mx) {
			printAll(i);
		}
	}
}
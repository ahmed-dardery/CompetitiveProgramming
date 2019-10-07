#include <bits/stdc++.h>

using namespace std;

#define getn int n; cin >> n
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define forifill(n,x) for (int i = 0; i < n; i++) cin >> x[i]
#define foriprint(n,x) for (int i = 0; i < n; i++) cout << x[i]
#define all(x) x.begin(),x.end()
#define inoutfile freopen("d:\\testcase.txt", "r", stdin);freopen("d:\\output.txt", "w", stdout)

bool sorting(pair<int, int> a, pair<int, int> b) {
	if (a.second != b.second)
		return a.second < b.second;
	else
		return a.first > b.first;
}

int main() {
	//inoutfile;
	vector<pair<int, int>> freq(128);
	fori(128) freq[i] = { i, 0 };
	bool firsty = true;
	string x;
	
	while (getline(cin, x)) {
		if (!firsty) cout << endl; else firsty = false;

		fori(x.length()){
			++freq[x[i]].second;
		}

		sort(all(freq), sorting);

		fori(128) {
			if (freq[i].second != 0) cout << freq[i].first << " " << freq[i].second << endl;
			freq[i] = { i, 0 };
		}
	}
}
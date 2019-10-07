#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <utility>

#include <iomanip>

using namespace std;

#define fori(n) for (int i = 0; i < n; i++)
#define foriR(n) for (int i = n-1; i >= 0; i--)
#define forj(n) for (int j = 0; j < n; j++)
#define forifill(n,x) for (int i = 0; i < n; i++) cin >> x[i]
#define foriprint(n,x) for (int i = 0; i < n; i++) cout << x[i]
#define all(v) (v).begin(),(v).end()
#define allr(v) (v).rbegin(),(v).rend()
#define sz(v) ((int)(v).size())


int main(){

	//freopen("d:\\testcase.txt", "r", stdin);
	//freopen("d:\\output.txt", "w", stdout);

	cout << setprecision(4);
	cout << fixed;

	int n;
	cin >> n;
	cin.ignore();
	cin.ignore();
	while (n--){
		map<string, int> database;
		string x;
		int count = 0;
		while (getline(cin, x) && x != ""){
			++database[x];
			++count;
		}
		for (pair<string, int> tree : database){
			cout << tree.first << " " << tree.second * 100 / (float)count << endl;
		}
		if (n!=0) cout << endl;
	}
}
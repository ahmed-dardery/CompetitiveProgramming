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

	freopen("d:\\testcase.txt", "r", stdin);
	freopen("d:\\output.txt", "w", stdout);


	map<string,int> dict;
	int n, p;
	cin >> n >> p;
	while (n--){
		string x;
		int y;
		cin >> x >> y;
		dict[x] = y;
	}
	long long sum = 0;
	while (p--){
		string word;
		cin >> word;
		while (word != ".") {
			sum += dict[word];
			cin >> word;
		}
		
		cout << sum << endl;
		sum = 0;
	}
}


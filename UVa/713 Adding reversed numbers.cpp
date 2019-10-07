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
typedef vector<int> veci;

int main(){
	//freopen("d:\\testcase.txt", "r", stdin);
	//freopen("d:\\output.txt", "w", stdout);

	int n;
	cin >> n;
	while (n--){
		string n1,n2;
		cin >> n1 >> n2;
		int trailing1 = -1;
		while (++trailing1<n1.length()){
			if (*(n1.end() - trailing1 - 1) != '0') break;
		}
		int trailing2 = -1;
		while (++trailing2 < n2.length()){
			if (*(n2.end() - trailing2 - 1) != '0') break;
		}
		n1.resize(n1.length() - trailing1);
		n2.resize(n2.length() - trailing2);
		reverse(all(n1));
		reverse(all(n2));
		if (n1.length() < n2.length()) swap(n1, n2);
		int remainder = 0;
		fori(n1.length()){
			int n2digit;
			if (i>n2.length() - 1) n2digit = 0;
			else n2digit = (n2[n2.length() - 1 - i] - '0');
			int res = remainder + (n1[n1.length() - 1 - i] - '0') + n2digit;
			remainder = res / 10;
			res = res % 10;
			n1[n1.length() - 1 - i] = res + '0';
		}
		trailing1 = -1;
		while (++trailing1 < n1.length()){
			if (*(n1.end() - trailing1 - 1) != '0') break;
		}
		n1.resize(n1.length() - trailing1);
		reverse(all(n1));
		if (remainder != 0) n1.push_back(remainder + '0');

		cout << n1 << "\n";
	}
}
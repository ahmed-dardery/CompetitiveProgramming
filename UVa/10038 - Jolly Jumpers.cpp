//UVa 10703
//  10083

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>
#include <utility>

using namespace std;

#define getn int n; cin >> n
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define forifill(n,x) for (int i = 0; i < n; i++) cin >> x[i]
#define foriprint(n,x) for (int i = 0; i < n; i++) cout << x[i]
#define range(x) x.begin(),x.end()

int main(){
	//freopen("d:\\testcase.txt", "r", stdin);
	//freopen("d:\\output.txt", "w", stdout);

	int n;
	while (cin >> n){
		n--;
		int last;
		cin >> last;
		vector<bool> vals(n,false);
		bool jolly = true;
		fori(n){
			int x;
			cin >> x;
			int diff = abs(last - x) - 1;
			last = x;
			if (diff<0 || diff >= n || vals[diff]) {
				jolly = false;
			}
			else
			vals[diff] = true;
		}
		if (jolly)
			cout << "Jolly\n";
		else
			cout << "Not jolly\n";
	}
}
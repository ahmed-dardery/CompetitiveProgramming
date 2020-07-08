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
	while (cin >> n, n){
		int myfirst;
		cin >> myfirst;
		while (myfirst){
			stack<int> station;
			vector<int> target(n);
			target[0] = myfirst;
			for (int i = 1; i < n; i++) cin >> target[i];

			int front = 1;
			bool success = true;
			fori(n){
				if (front <= target[i]){
					while (front!=target[i]){
						station.push(front);
						front++;
					}
					front++;
				}
				else if (!station.empty() && (station.top() == target[i])){
					station.pop();
				}
				else
				{
					success = false;
					break;
				}
			}
			cout << (success ? "Yes\n" : "No\n");
			cin >> myfirst;
		}
		cout << "\n";
	}
}
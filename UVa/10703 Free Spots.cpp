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

	int w, h, n;
	while (cin >> w >> h >> n, w || h || n){
		vector<vector<bool>> area(w, vector<bool>(h, false));
		while (n--){
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			for (int i = x1; i <= x2; i++){
				for (int j = y1; j <= y2; j++){
					area[i-1][j-1] = true;
				}
			}
		}
		int clean = 0;
		for (int i = 0; i < w; i++){
			for (int j = 0; j < h; j++){
				clean += !area[i][j];
			}
		}
		if (clean == 0)
			cout << "There is no empty spots.\n";
		else if (clean == 1)
			cout << "There is one empty spot.\n";
		else
			cout << "There are " << clean << " empty spots.\n";
	}
}
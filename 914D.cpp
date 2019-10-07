#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>

using namespace std;
#define fori(x) for (int i = 0; i < x; i++)
#define foriR(x) for (int i = x-1; i >=0; i--)
#define sort(a) std::sort(a.begin(),a.end())

typedef long long lng;

int main()
{
	int n;
	scanf("%d", &n);
	vector<int> myarray(n);
	fori(n) cin >> myarray[i];
	scanf("%d", &n);
	fori(n)
	{
		int q;
		scanf("%d", &q);
		if (q == 1){
			int l, r, x;
			scanf("%d %d %d", &l, &r, &x);
			int changes = 0;
			for (int j = l-1; j < r; j++){
				if (myarray[j] % x != 0) {
					changes++;
					if (changes>1) break;
				}
			}
			if (changes <= 1) cout << "YES\n"; else cout << "NO\n";
		}
		else
		{
			int u, y;
			scanf("%d %d", &u, &y);
			myarray[u - 1] = y;
		}
	}
}

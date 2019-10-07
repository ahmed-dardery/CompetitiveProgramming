#include <iostream>
#include <vector>
#include <stack>
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
	map<char, char> closing;
	closing['('] = ')';
	closing['['] = ']';

	int n;
	cin >> n;
	cin.ignore();
	while (n--){
		stack<char> brackets;
		string x;
		getline(cin, x);
		bool result = true;
		fori(x.length()){
			if (x[i] == '(' || x[i] == '['){
				brackets.push(x[i]);
			}
			else if (!brackets.empty() && closing[brackets.top()] == x[i]){
				brackets.pop();
			}
			else{
				result = false;
				break;
			}
		}
		if (brackets.empty() && result) cout << "Yes\n"; else cout << "No\n";
	}
}
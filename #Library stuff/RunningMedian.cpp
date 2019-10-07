#include <bits/stdc++.h>
using namespace std;


//running median
priority_queue<int> low; priority_queue<int, vector<int>, greater<int>> high;
int getMedian() {
	if (low.empty() && high.empty()) return 0;
	if (low.size() == high.size()) return high.top();	//change this depending on median
	else if (low.size() > high.size()) return low.top();
	else return high.top();
}
void push(int v) {
	int med = getMedian();

	if (v < med)
		low.push(v);
	else
		high.push(v);

	if (low.size() > high.size() + 1) {
		high.push(low.top());
		low.pop();
	}
	else if (high.size() > low.size() + 1) {
		low.push(high.top());
		high.pop();
	}
}

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace __gnu_pbds;
using namespace pb_ds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

t.find_by_order(k) //returns kth item (0-based)
t.order_of_key(v) //returns number of elements strictly less than v
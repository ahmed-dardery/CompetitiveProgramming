#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int a[20], m, n;

vector<int> taken, bestTaken;
int len, bestLen;

void CD(int idx) {
    if (idx == n) { /*base case*/
        if (len > bestLen) {
            bestLen = len;
            bestTaken = taken;
        }
        return;
    }
    if (len + a[idx] <= m) {
        taken.push_back(a[idx]);    //change
        len += a[idx];              //change
        CD(idx + 1);                //recurse
        len -= a[idx];              //backtrack
        taken.pop_back();           //backtrack
    }

    CD(idx + 1);    //recurse
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    while (cin >> m >> n) {
        for (int i = 0; i < n; ++i)
            cin >> a[i];

        bestLen = 0;
        CD(0);

        for (auto v : bestTaken)
            cout << v << " ";

        cout << "sum:" << bestLen << "\n";
    }

}

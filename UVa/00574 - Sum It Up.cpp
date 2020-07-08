#include <bits/stdc++.h>

using namespace std;

int required;
const int N = 1e5 + 7;
int freq[N], n;

vector<int> curr;
int sum;
bool didntPrint = 1;

void solve(int v) {

    if (v == 0) {
        if (sum == required) {
            didntPrint = 0;
            for (int i = 0; i < (int) curr.size(); ++i) {
                cout << curr[i] << "+\n"[i + 1 == curr.size()];
            }
        }
        return;
    }

    if (sum + v <= required && freq[v] > 0) {

        curr.push_back(v);
        sum += v;
        --freq[v];

        solve(v);

        ++freq[v];
        sum -= v;
        curr.pop_back();

    }

    solve(v - 1);
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    while (cin >> required >> n, n) {
        for (int i = 0; i <= 1000; ++i) {
            freq[i] = 0;
        }
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            ++freq[x];
        }
        cout << "Sums of " << required << ":\n";
        didntPrint = 1;
        solve(1000);
        if (didntPrint)
            cout << "NONE\n";

    }

}
#include <bits/stdc++.h>

#define endl '\n'

using namespace std;
typedef long long ll;
const int N = 1e5 + 7, M = 2 * N;

int n, m;
int arr[N];
vector<int> chambers[N];

int main() {
    cout << fixed << setprecision(5);
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef CLION
    freopen("input.in", "rt", stdin);
    freopen("output.out", "wt", stdout);
#endif

    int CASE = 0;
    while (cin >> n >> m) {
        cout << "Set #" << ++CASE << endl;
        for (int i = 0; i < n; ++i) {
            chambers[i].clear();
        }
        ll total = 0;
        for (int i = 0; i < m; ++i) {
            cin >> arr[i];
            total += arr[i];
        }
        double avg = 1.0 * total / n;

        for (int i = m; i < 2 * n; ++i)
            arr[i] = 0;

        sort(arr, arr + 2 * n);
        double s = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] != 0)
                chambers[i].push_back(arr[i]);
            if (arr[2 * n - 1 - i] != 0)
                chambers[i].push_back(arr[2 * n - 1 - i]);
            s += abs(arr[i] + arr[2 * n - 1 - i] - avg);
        }
        for (int i = 0; i < n; ++i) {
            vector<int> &cur = chambers[i];
            cout << setw(2) << i << ":";

            for (int j = 0; j < (int) cur.size(); ++j) {
                cout << " " << cur[j];
            }
            cout << endl;
        }
        cout << "IMBALANCE = " << s << endl << endl;
    }
}

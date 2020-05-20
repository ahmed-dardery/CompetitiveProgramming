#include <bits/stdc++.h>

using namespace std;
int good, bad;
int value, lastFiveMonths;

int bestValue;
int valMonth[12];

/* 4 3 1 8 3 1 0 0 0 0 0 0*/
void solve(int m) {
    if (m >= 6)lastFiveMonths -= valMonth[m - 6];

    if (m >= 5) {

        if (lastFiveMonths >= 0) {
            if (m >= 6)lastFiveMonths += valMonth[m - 6];
            return;
        }
    }
    if (m == 12) {
        bestValue = max(bestValue, value);
        if (m >= 6)lastFiveMonths += valMonth[m - 6];
        return;
    }

    value += good;
    valMonth[m] = good;
    lastFiveMonths += good;
    solve(m + 1);
    lastFiveMonths -= good;
    valMonth[m] = 0;
    value -= good;

    value -= bad;
    valMonth[m] = -bad;
    lastFiveMonths -= bad;
    solve(m + 1);
    lastFiveMonths += bad;
    valMonth[m] = 0;
    value += bad;

    if (m >= 6) lastFiveMonths += valMonth[m - 6];
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    while (cin >> good >> bad) {
        bestValue = -1e9;
        solve(0);
        if (bestValue < 0)
            cout << "Deficit\n";
        else
            cout << bestValue << endl;
    }
}
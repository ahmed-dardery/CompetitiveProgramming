#include <bits/stdc++.h>

using namespace std;
int n, allowedChanges;
string s;
char options[] = "ACGT";
int changes;
vector<string> total;
void solve(int i) {
    if (i == n) {
        total.push_back(s);
        return;
    }

    char backup = s[i];
    for (int k = 0; k < 4; ++k) {
        if (options[k] != backup)
            ++changes;

        s[i] = options[k];

        if (changes <= allowedChanges)solve(i + 1);

        if (options[k] != backup)
            --changes;
    }
    s[i] = backup;
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    int tests;
    cin >> tests;
    while (tests--) {
        total.clear();
        cin >> n >> allowedChanges >> s;
        solve(0);
        //no need to sort because of backtracking order
        cout << total.size() << endl;
        for(auto& v : total){
            cout << v << "\n";
        }
    }
}
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

string words[100];
int n, m;
string pat;

string curPass;

void passwords(int idx) {
    if (idx == pat.length()) { /*base case*/
        cout << curPass << "\n";
        return;
    }
    if (pat[idx] == '#')
        for (int i = 0; i < n; ++i) {
            curPass += words[i];
            passwords(idx + 1);
            curPass.resize(curPass.length() - words[i].length());
        }
    else {
        for (char c = '0'; c <= '9'; ++c) {
            curPass += c;
            passwords(idx + 1);
            curPass.pop_back();
        }
    }
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    while (cin >> n) {
        cout << "--\n";
        
        for (int i = 0; i < n; ++i)
            cin >> words[i];
        cin >> m;
        for (int i = 0; i < m; ++i) {
            cin >> pat;
            passwords(0);
        }
    }

}6

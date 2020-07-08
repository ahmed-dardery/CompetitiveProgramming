#include<bits/stdc++.h>

using namespace std;

const int M = 1000000, N = M;


int teamOf[M];
queue<int> team[N];
int inQ[N], vid;

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif

    int n;
    int test = 0;
    while (cin >> n, n) {
        cout << "Scenario #" << ++test << "\n";
        for (int i = 0; i < n; ++i) {
            int m, v;
            cin >> m;
            while (m--) {
                cin >> v;
                teamOf[v] = i;
            }
            while (!team[i].empty()) team[i].pop();
        }
        ++vid;
        queue<int> q;
        while (true) {
            char s[100];
            cin >> s;
            if (s[0] == 'E') {
                int x;
                cin >> x;
                if (inQ[teamOf[x]] != vid)
                    q.push(teamOf[x]), inQ[teamOf[x]] = vid;
                team[teamOf[x]].push(x);
            } else if (s[0] == 'D') {
                int t = q.front();
                int v = team[t].front();
                cout << v << "\n";
                team[t].pop();
                if (team[t].empty()) q.pop(), inQ[t] = 0;
            } else
                break;
        }
        cout << "\n";
    }
}

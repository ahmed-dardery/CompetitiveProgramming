#include <bits/stdc++.h>

using namespace std;
int n, m;
const int N = 15;
int row[N], col[N];

int mem[N][N];

int MCM(int st, int en) {
    if (st == en) {
        return 0;
    }
    int &ret = mem[st][en];
    if (~ret) return ret;
    ret = 1e9;
    for (int k = st; k < en; ++k) {
        ret = min(ret, MCM(st, k) + MCM(k + 1, en) + row[st] * col[k] * col[en]);
    }
    return ret;
}

void printPath(int st, int en) {
    if (st == en) {
        cout << "A" << st+1;
    }
    int ret = MCM(st, en);
    for (int k = st; k < en; ++k) {
        if (ret == MCM(st, k) + MCM(k + 1, en) + row[st] * col[k] * col[en]) {
            if(st != k) cout << "(";
            printPath(st, k);
            if(st != k) cout << ")";
            cout << " x ";
            if(k+1 != en) cout << "(";
            printPath(k + 1, en);
            if(k+1 != en) cout << ")";
            return;
        }
    }
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    int caseID = 0;
    while(cin >> n, n) {
        cout << "Case " << ++caseID << ": ";
        for (int i = 0; i < n; ++i) {
            cin >> row[i] >> col[i];
        }
        memset(mem, -1, sizeof mem);
        cout << "(";
        printPath(0, n - 1);
        cout << ")\n";
    }

}

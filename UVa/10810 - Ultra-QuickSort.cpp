#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

long long CountInvMerge(long long *a, int n) ;
long long CountInv(long long *a, int n);

int main() {
    int n;
    while (true) {
        cin >> n;
        if (n == 0) break;

        auto *a = new long long[n];
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        cout << CountInv(a, n) << endl;
        
        delete[] a;
    }
    return 0;
}

long long CountInvMerge(long long *a, int n) {
    if (n <=1) return 0;
    auto *aux = new long long[n];
    int idx = 0;
    long long inversions = 0;
    int m = n/2;

    int i = 0, j = m;
    while (i < m && j <n) {
        if (a[i] <= a[j])
            aux[idx++] = a[i++];
        else {
            inversions += m - i;
            aux[idx++] = a[j++];
        }
    }

    while (i < m)
        aux[idx++] = a[i++];
    while (j < n)
        aux[idx++] = a[j++];

    for (int k = 0; k < idx; ++k) {
        a[k] = aux[k];
    }
    delete[] aux;
    return inversions;
}

long long CountInv(long long *a, int n) {
    if (n<=1) return 0;
    int m = n / 2;
    long long inversions = 0;
    inversions += CountInv(a, m);
    inversions += CountInv(a+m,n-m);
    inversions += CountInvMerge(a, n);
    return inversions;
}

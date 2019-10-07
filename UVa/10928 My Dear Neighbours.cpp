#include <bits/stdc++.h>
 
using namespace std;
typedef long long lng;
 
const int N = 1e3 + 5;
int n, t, x, arr[N];
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    scanf("%d", &t);
   
    while (t--) {
        scanf("%d", &n);
        memset(arr, 0, n * sizeof arr[0]);
        for (int i = 0; i < n; ++i) {
            char chr;
            do {
                scanf("%d%c", &x, &chr);
                arr[i]++;
            } while (chr == ' ');
        }
        int mn = *min_element(arr, arr + n);
        bool first = 1;
        for (int i = 0; i < n; i++) {
            if (arr[i] == mn) {
                if (first)
                    first = false;
                else
                    printf(" ");
                printf("%d", i + 1);
            }
        }
        puts("");
    }
   
}
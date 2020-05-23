#include <bits/stdc++.h>

using namespace std;
int n, m;

char a[100], b[100];

int mem[100][100];

int edit(int i, int j) {
    if (i == n) return m - j;
    if (j == m) return n - i;
    int &ret = mem[i][j];
    if (~ret) return ret;

    ret = min({edit(i, j + 1) + 1,
               edit(i + 1, j) + 1,
               edit(i + 1, j + 1) + (a[i] != b[j])}
    );
    return ret;
}

void printPath(int i, int j, int iOffset) {
    if (i == n) {
        //insert all remainder of b
        for (int k = j; k < m; ++k) {
            printf("I%c%02d", b[k], n + k - j + 1 + iOffset);
        }
        return;
    }
    if (j == m) {
        //delete all remainder of a
        for (int k = i; k < n; ++k) {
            printf("D%c%02d", a[k], m + 1);
        }
        return;
    }
    int ret = edit(i, j);
    if (a[i] == b[j]) {    //same letter, so leave it as is
        printPath(i + 1, j + 1, iOffset);
        return;
    }
    if (ret == edit(i + 1, j + 1) + 1) { //replace
        printf("C%c%02d", b[j], i + 1 + iOffset);
        printPath(i + 1, j + 1, iOffset);
        return;
    }
    if (ret == edit(i, j + 1) + 1) {    //insert b[j] into a
        printf("I%c%02d", b[j], i + 1 + iOffset);
        printPath(i, j + 1, iOffset + 1);
        return;
    }
    if (ret == edit(i + 1, j) + 1) {    //delete a[i] from i
        printf("D%c%02d", a[i], i + 1 + iOffset);
        printPath(i + 1, j, iOffset - 1);
        return;
    }
}

char temp[50];
vector<string> build;

void printAllPaths(int i, int j, int iOffset) {
    if (i == n) {
        for (int k = j; k < m; ++k) {
            sprintf(temp, "I%c%02d", b[k], n + k - j + iOffset);
            build.emplace_back(temp);
        }

        for (auto &s : build) cout << s;
        cout << 'E' << endl;

        for (int k = j; k < m; ++k) {
            build.pop_back();
        }
        return;
    }
    if (j == m) {
        for (int k = i; k < n; ++k) {
            sprintf(temp, "D%c%02d", a[k], m + 1);
            build.emplace_back(temp);
        }

        for (auto &s : build) cout << s;
        cout << 'E' << endl;

        for (int k = i; k < m; ++k) {
            build.pop_back();
        }
        return;
    }

    int ret = edit(i, j);
    if (a[i] == b[j]) {    //same letter, so leave it as is
        printAllPaths(i + 1, j + 1, iOffset);
    }
    if (ret == edit(i + 1, j + 1) + 1) {  //replace
        sprintf(temp, "C%c%02d", b[j], i + 1 + iOffset);
        build.emplace_back(temp);

        printAllPaths(i + 1, j + 1, iOffset);

        build.pop_back();
    }
    if (ret == edit(i, j + 1) + 1) {    //insert b[j] into a
        sprintf(temp, "I%c%02d", b[j], i + 1 + iOffset);
        build.emplace_back(temp);

        printAllPaths(i, j + 1, iOffset + 1);

        build.pop_back();
    }
    if (ret == edit(i + 1, j) + 1) {    //delete a[i] from i
        sprintf(temp, "D%c%02d", a[i], i + 1 + iOffset);
        build.emplace_back(temp);

        printAllPaths(i + 1, j, iOffset - 1);

        build.pop_back();
    }
}

int main() {
#ifdef CLION
    freopen("input.in", "rt", stdin);
#endif
    while (scanf("%s", a), a[0] != '#') {
        scanf("%s", b);
        n = strlen(a);
        m = strlen(b);
        memset(mem, -1, sizeof mem);
        printPath(0, 0, 0);
        puts("E");
    }
}

#include <bits/stdc++.h>

using namespace std;
const int N = 1e3 + 7;
typedef long long ll;

int freq[30];

string countSort(string &v) {
    memset(freq, 0, sizeof freq);

    int sz = v.size();
    //frequency
    for (int i = 0; i < sz; ++i) {
        freq[tolower(v[i]) - 'a']++;
    }

    //cumulative
    for (int i = 1; i < 26; ++i) {
        freq[i] = freq[i] + freq[i - 1];
    }

    string ret(sz, ' ');	//create a ret string for output (size sz)

    //count sort
    for (int i = sz - 1; i >= 0; --i) {
        int &pos = freq[tolower(v[i]) - 'a'];
        ret[pos - 1] = tolower(v[i]);

        --pos;
    }

    return ret;
}

//assume:
//size of array is <= 10^5
//range of values is [0, 10^5]
vector<string> input;
vector<string> sorted;
vector<string> output;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.in", "rt", stdin);
    //freopen("output.out", "wt", stdout);
#endif
    string str;

    //The entire problem is one test case, take one word at a time until str is '#'
    while (cin >> str, str != "#") {
        //get a sorted string of the input
        string sortedStr = countSort(str);

        //place both in vectors
        input.push_back(str);
        sorted.push_back(sortedStr);
    }

    int n = input.size();

    //for each string, find if there is a string that matches it
    for (int i = 0; i < n; ++i) {
        bool good = 1;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (sorted[i] == sorted[j]) {
                good = 0;
                break;
            }
        }
        //if ananagram, push onto the output.
        if (good) {
            output.push_back(input[i]);
        }
    }

    //Words must be output in lexicographic (per problem statement)
    //We use regular built-in sort here, because we can't create frequency of string
    sort(output.begin(), output.end());

    //print the output
    for (int i = 0; i < output.size(); ++i) {
        cout << output[i] << endl;
    }

    //Constraints from the statement n < 1000, m < 20
    //Time complexity is: O(n(m+26) + n*n*m).
}

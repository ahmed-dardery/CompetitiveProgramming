#include <iostream>
#include <string>
using namespace std;

typedef int *introw;
introw* Arr;

int Owls = 0, n = 0;

void Check(int x, int y, bool addowl){
	if (x >= n || y >= n || x < 0 || y < 0 || Arr[x][y] == 0) return;
	Arr[x][y] = 0;
	if (addowl) Owls++;
	Check(x - 1, y - 1, false);
	Check(x, y - 1, false);
	Check(x + 1, y - 1, false);
	Check(x - 1, y, false);
	Check(x + 1, y, false);
	Check(x - 1, y + 1, false);
	Check(x, y + 1, false);
	Check(x + 1, y + 1, false);
}

int main() {
	int picture = 1;
	while (cin >> n){
		Arr = new introw[n];

		for (int i = 0; i < n; i++){
			Arr[i] = new int[n];
			string myline;
			cin >> myline;
			for (int j = 0; j < n; j++){
				Arr[i][j] = myline[j] - '0';
			}
		}

		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				Check(i, j, true);
			}
		}

		cout << "Image number " << picture << " contains " << Owls << " war eagles." << endl;
		picture++;
		Owls = 0;
		n = 0;
	}
}
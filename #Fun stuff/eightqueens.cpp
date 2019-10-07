// Program: Individual.cpp
// Author: Ahmed Nasr Eldardery

#include <iostream>
using namespace std;
const int N = 17;
bool colattack[N];
bool diagattack[N * N - 1];
bool queens[N][N];
void place_queen(int i, int j, bool mark) {
	queens[i][j] = mark;
	int diff = mark ? 1 : -1;
	colattack[j] = mark;

}
/*
####
####
####
####

##
##
*/
bool eight_queens(int i = 0, int j = 0, int left = N) {
	if (j == N)
		return eight_queens(i + 1, 0);

	if (i == N)
		return (left == 0);

	if (cell[i][j] == 0) {
		place_queen(i, j, 1);
		if (eight_queens(i + 1, 0, left - 1)) return 1;
		place_queen(i, j, 0);
	}

	if (eight_queens(i, j + 1, left)) return 1;

	return 0;
}

int main() {

	eight_queens();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << (queens[i][j] ? "X" : ".") << " ";
		cout << endl;
	}

}
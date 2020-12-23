char pat[N], str[N];
int F[N];

//I need to know what is the maximum number of characters that can be matched if c is included
int getNewLen(int len, char c) {
	while (len && c != pat[len])
		len = F[len - 1];

	return len + (c == pat[len]);
}
//00012345
//abcabcab
void computeF() {
	F[0] = 0;
	for (int i = 1; pat[i]; i++)
		F[i] = getNewLen(F[i - 1], pat[i]);

}

//returns vector of starting positions where pattern was found
vector<int> KMP() {
	computeF();
	int len = 0;
	vector<int> res;
	for (int i = 0; str[i]; ++i) {
		len = getNewLen(len, str[i]);
		if (!pat[len]) res.push_back(i - len + 1);
	}
	return res;
}
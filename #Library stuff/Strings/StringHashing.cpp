//if assembly not available, mod after each operation and preferably use double or triple hashing
struct H {
	typedef uint64_t ull;
	ull x; H(ull x = 0) : x(x) {}
#define OP(O,A,B) H operator O(H o) { ull r = x; asm \
	(A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B); return r; }
	OP(+, , "d"(o.x)) OP(*, "mul %1\n", "r"(o.x) : "rdx")
		H operator-(H o) { return *this + ~o.x; }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3; // (order ~ 3e9; random also ok)

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(str.size() + 1), pw(ha) {
		pw[0] = 1;
		for(int i = 0; i < str.size(); ++i)
			ha[i + 1] = ha[i] * C + str[i],
			pw[i + 1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

//get hashes of all substrings of specific length
vector<H> getHashes(string& str, int length) {
	if (str.size() < length) return {};
	H h = 0, pw = 1;
	for(int i = 0; i < length; ++i)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = { h };
	for (int i = length; i < str.size(); ++i)
		ret.push_back(h = h * C + str[i] - pw * str[i - length]);
	
	return ret;
}

H hashString(string& s) { H h{}; for (char c : s) h = h * C + c; return h; }

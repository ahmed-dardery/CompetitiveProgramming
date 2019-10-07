#include <bits/stdc++.h>

using namespace std;

typedef int T;

class BSTFCI {
	struct BSTNode {
		BSTNode* right = nullptr;
		BSTNode* left = nullptr;
		T val;
		int level;
	};
	BSTNode* root = nullptr;

	bool _isBalanced(BSTNode* x) {
		if (x == nullptr)
			return 1;
		int r_level = 0, l_level = 0;
		if (x->right) {
			r_level = x->right->level;
			if (!_isBalanced(x->right)) return 0;
		}
		if (x->left) {
			l_level = x->left->level;
			if (!_isBalanced(x->left)) return 0;
		}
		return abs(r_level - l_level) <= 1;
	}
	int insert(T val, BSTNode*& x) {
		if (x == nullptr) {
			x = new BSTNode;
			x->val = val;
			return x->level = 0;
		}
		else if (val > x->val) {
			int lvl = insert(val, x->right) + 1;
			return x->level = max(lvl, x->level);
		}
		else if (val < x->val) {
			int lvl = insert(val, x->left) + 1;
			return x->level = max(lvl, x->level);
		}
		return x->level;
	}
public:
	bool isBalanced() {
		return _isBalanced(root);
	}
};

int main() {

}
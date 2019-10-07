struct node {
	node* left;
	node* right;
	int value;
};

struct binary_tree {
	node * root = nullptr;

	void LPR(node* p) {
		if (p->left)
			LPR(p->left);
		cout << p->value << " ";
		if (p->right)
			LPR(p->right);
	}
	node* search(int v) {
		return search(root, v);
	}
	node* search(node* p, int v) {
		if (p == nullptr) return nullptr;
		else if (v < p->value) return search(p->left, v);
		else if (v > p->value) return search(p->right, v);
		else return p;
	}
	void insert(int v) {
		insert(root, v);
	}
	void insert(node*& p, int v) {
		if (p == nullptr) {
			p = new node();
			p->value = v;
		}
		else {
			if (v < p->value)
				insert(p->left, v);
			else
				insert(p->right, v);
		}
	}
};
class treap {
private:
    node *root = nullptr;

    int cnt(node *u) {
        return u ? u->sz : 0;
    }

    void updateNode(node *u) {
        if (u) {
            u->sz = 1 + cnt(u->lf) + cnt(u->rt);
        }
    }

    void split(node *u, int preSz, node *&lf, node *&rt) {
        if (!u) return lf = rt = 0, void();
        int szLf = cnt(u->lf);
        if (szLf < preSz)
            split(u->rt, preSz - szLf - 1, u->rt, rt), lf = u;
        else
            split(u->lf, preSz, lf, u->lf), rt = u;
        updateNode(u);
    }

    void merge(node *lf, node *rt, node *&u) {
        if (!lf || !rt) u = lf ? lf : rt;
        else if (lf->pr > rt->pr) merge(lf->rt, rt, lf->rt), u = lf;
        else merge(lf, rt->lf, rt->lf), u = rt;
        updateNode(u);
    }


    void dfs(node *u) {
        if (!u) return;
        dfs(u->lf);
        cout << u->val << " ";
        dfs(u->rt);
    }

    int &kth(node *u, int k) {
        //if (!u) return -1;
        int szLf = cnt(u->lf);
        if (szLf > k) return kth(u->lf, k);
        else if (szLf == k) return u->val;
        return kth(u->rt, k - szLf - 1);
    }

public:
    void insert(int i, int val) {
        node *lf, *rt;
        split(root, i, lf, rt);
        merge(lf, new node(val), lf);
        merge(lf, rt, root);
    }

    void erase(int i) {
        node *lf, *md, *rt;
        split(root, i, lf, rt);
        split(rt, 1, md, rt);
        delete md;
        merge(lf, rt, root);
    }

    void print() {
        dfs(root);
        cout << endl;
    }

    int &operator[](int i) {
        return kth(root, i);
    }

    void cycleShiftRight(int qs, int qe, int v) {
        node *lf, *md, *rt, *x, *y;
        split(root, qe, lf, rt);
        split(lf, qs, lf, md);

        split(md, md->sz - v, x, y);
        merge(y, x, md);

        merge(lf, md, lf);
        merge(lf, rt, root);
    }

};

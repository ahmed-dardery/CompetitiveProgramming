#include <bits/stdc++.h>

#define endl '\n'

using namespace std;
typedef long long ll;
const int N = 1e5 + 7, M = 2 * N;

mt19937 rng;

struct node {
    int val, pr, sz;
    node *lf = 0, *rt = 0;

    node(int val) : val(val), sz(1), pr(rng()) {}
};

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

    void split(node *u, int val, node *&lf, node *&rt) {
        if (!u) lf = rt = 0;
        else if (val >= u->val) split(u->rt, val, u->rt, rt), lf = u;
        else split(u->lf, val, lf, u->lf), rt = u;
        updateNode(u);
    }

    void merge(node *lf, node *rt, node *&u) {
        if (!lf || !rt) u = lf ? lf : rt;
        else if (lf->pr > rt->pr) merge(lf->rt, rt, lf->rt), u = lf;
        else merge(lf, rt->lf, rt->lf), u = rt;
        updateNode(u);
    }

    void erase(node *&u, int val) {
        if (!u) return;
        if (val == u->val) {
            node *tmp = u;
            merge(u->lf, u->rt, tmp);
            delete u;
            u = tmp;
        } else
            erase(val < u->val ? u->lf : u->rt, val);
        updateNode(u);
    }

    void dfs(node *u) {
        if (!u) return;
        dfs(u->lf);
        cout << u->val << " ";
        dfs(u->rt);
    }


    int kth(node *u, int k) {
        if (!u) return -1;
        int szLf = cnt(u->lf);
        if (szLf > k) return kth(u->lf, k);
        else if (szLf == k) return u->val;
        return kth(u->rt, k - szLf - 1);
    }

    bool exists(node *u, int val) {
        if (!u) return 0;
        if (u->val == val) return 1;
        return exists(val < u->val ? u->lf : u->rt, val);
    }

public:
    void insert(int val) {
        if (exists(root, val)) return;
        node *lf, *rt;
        split(root, val, lf, rt);
        node *nd = new node(val);
        merge(lf, nd, lf);
        merge(lf, rt, root);
    }

    void erase(int val) {
        erase(root, val);
    }

    void eraseAll(int val) {
        node *lf, *md, *rt;
        split(root, val, lf, rt);
        split(lf, val - 1, lf, md);
        merge(lf, rt, root);
        delete md;
    }

    void print() {
        dfs(root);
        cout << endl;
    }

    int operator[](int i) {
        return kth(root, i);
    }

    int countSmaller(int val) {
        node *lf, *rt;
        split(root, val - 1, lf, rt);
        int sz = cnt(lf);
        merge(lf, rt, root);
        return sz;
    }
};

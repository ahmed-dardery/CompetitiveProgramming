
enum {
    L, R
};
extern struct node *empty;

struct node {
    int v, sz;
    node *ch[2];
    node *par;
    bool rev;

    node() : v(0), sz(0), rev(0) {
        ch[L] = ch[R] = par = this;
    }

    node(int v) : v(v), sz(1), rev(0) {
        ch[L] = ch[R] = par = empty;
    }

    void updateSz() {
        if (this != empty)
            sz = ch[L]->sz + ch[R]->sz + 1;
    }

    void pushDown() {
        if (this != empty && rev) {
            swap(ch[L], ch[R]);
            ch[L]->rev = !ch[L]->rev;
            ch[R]->rev = !ch[R]->rev;
            rev = 0;
        }
    }

    void linkChild(node *v, int dir) {
        if (v != empty) {
            node *&p = v->par;
            //p->ch[p->getDirTo(v)] = empty;
            //p->updateSz();
            p = this;
        }
        if (this != empty) {
            //ch[dir]->par = empty;
            ch[dir] = v;
            updateSz();
        }
    }

    int getDirTo(node *v) {
        return ch[R] == v;
    }
};

node *empty = new node();

struct splayTree {
    node *root = empty;

    void rotate(node *u, int dir) {
        node *p = u->par;
        int parDir = p->getDirTo(u);
        node *ch = u->ch[!dir];
        node *gc = ch->ch[dir];
        u->linkChild(gc, !dir);
        ch->linkChild(u, dir);
        p->linkChild(ch, parDir);
    }

    void splay(node *u) {
        while (u->par != empty) {
            node *p = u->par;
            node *gp = p->par;

            int pDir = p->getDirTo(u);
            if (gp == empty) {
                rotate(p, !pDir);
                return;
            }
            int gpDir = gp->getDirTo(p);
            if (gpDir == pDir) {
                rotate(gp, !pDir);
                rotate(p, !pDir);
            } else {
                rotate(p, !pDir);
                rotate(gp, !gpDir);
            }
        }
    }

    node *splayByIndex(node *u, int idx) {
        u->pushDown();
        int lfSz = u->ch[L]->sz;
        if (lfSz == idx)
            return splay(u), u;
        else if (lfSz > idx)
            return splayByIndex(u->ch[L], idx);
        else
            return splayByIndex(u->ch[R], idx - lfSz - 1);
    }

    void merge(node *lf, node *rt, node *&u) {
        if (lf == empty || rt == empty) return u = (lf == empty ? rt : lf), void();
        u = splayByIndex(rt, 0);
        u->linkChild(lf, L);
    }

    void split(node *u, int preSz, node *&lf, node *&rt) {
        if (preSz == u->sz)
            return lf = u, rt = empty, void();
        u = splayByIndex(u, preSz);
        lf = u->ch[L], rt = u;
        empty->linkChild(lf, L);
        rt->linkChild(empty, L);
    }

    void reverse(int qs, int qe) {
        node *lf, *rt;
        split(root, qe + 1, lf, rt);
        split(lf, qs, lf, root);

        root->rev = !root->rev;

        merge(lf, root, root);
        merge(root, rt, root);
    }

    void unlazy(node *u) {
        if (u == empty) return;
        unlazy(u->par);
        u->pushDown();
    }

    int indexOf(node *u) {
        unlazy(u);
        int i = u->ch[L]->sz;
        while (u->par != empty) {
            int d = u->par->getDirTo(u);
            u = u->par;
            if (d == R)
                i += u->ch[L]->sz + 1;
        }
        return i;
    }

    void print(node *rt, int dpth, bool rev) {
        if (rt == empty)
            return;
        print(rt->ch[L^rev], dpth + 1, rev ^ rt->ch[L^rev]->rev);
        printf("%s%2d,%2d,%1d\n", string(dpth * 7, ' ').c_str(), rt->v, rt->par->v, (int) rt->rev);
        print(rt->ch[R^rev], dpth + 1, rev ^ rt->ch[R^rev]->rev);
    }

    void print(node *rt) {
        print(rt, 0, rt->rev);
        puts("----------");
        fflush(stdout);
    }
};

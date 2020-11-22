template<int... ArgsT>
struct BIT {
    ll val = 0;
    void update(ll v) {
        val += v;
    }
    ll query() {
        return val;
    }
};

template<int N, int... Ns>
struct BIT<N, Ns...> {
    BIT<Ns...> bit[N];
    template<typename... Args>
    void update(int i, Args... args) {
        for (++i; i <= N; bit[i - 1].update(args...), i += i & -i);
    }
    template<typename... Args>
    ll query(int l, int r, Args... args) {
        ll ans = 0;
        for (++r; r; ans += bit[r - 1].query(args...), r -= r & -r);
        for (; l; ans -= bit[l - 1].query(args...), l -= l & -l);
        return ans;
    }
};


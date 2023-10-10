#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
#define int LL

int qmi(int a, int b, int m){
    int res = 1 % m; a %= m;
    while(b)
    {
        if(b & 1) res = res * a % m;
        b >>= 1;
        a = a * a % m;
    }
    return res;
}


struct Node_t{
    int l, r;
    mutable int v;
    Node_t(const int &il, const int &ir, const int &iv) : l(il), r(ir), v(iv) {}
    bool operator<(const Node_t &w) const { return l < w.l; }
};

struct ODT{
    set<Node_t> odt;
    ODT(){}
    auto split(int x){
        auto it = --odt.upper_bound(Node_t{x, 0, 0});
        if(it != odt.end() && it->l == x)
            return it;
        int l = it->l, r = it->r, v = it->v;
        odt.erase(it);
        odt.insert(Node_t(l, x - 1, v));
        return odt.insert(Node_t(x, r, v)).first;
    }
    void assign(int l, int r, int v) {
        auto itr = split(r + 1), itl = split(l);
        odt.erase(itl, itr);
        odt.insert(Node_t(l, r, v));
    }
    
    void add(int l, int r, int v){
        auto end = split(r + 1);
        for(auto i = split(l); i != end; i ++)
            i->v += v;
    }
    int get_kth_small(int l, int r, int k){
        auto end = split(r + 1);
        vector<array<int, 2>> v;
        for(auto i = split(l); i != end; i ++)
            v.push_back({i->v, i->r - i->l + 1});
        sort(v.begin(), v.end());
        for(auto i : v)
        {
            k -= i[1];
            if(k <= 0)
                return i[0];
        }
        return v.back()[0];
    }
    int sum_of_pow(int l, int r, int x, int y){
        auto end = split(r + 1);
        int res = 0;
        for(auto i = split(l); i != end; i ++)
            res += qmi(i->v, x, y) * (i->r - i->l + 1), res %= y;
        return res;
    }
};

void solve(){
    int n, m, seed, vmax; cin >> n >> m >> seed >> vmax;
    auto rnd = [&]() ->int {
        int ret = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return ret;
    };
    auto ot = ODT();
    for(int i = 1; i <= n; i ++)
    {
        int r = rnd();
        ot.odt.insert(Node_t(i, i, r % vmax + 1)); 
    }
    for(int i = 1; i <= m; i ++)
    {
        int opr = rnd() % 4 + 1, l = rnd() % n + 1, r = rnd() % n + 1, x, y;
        if (l > r)
            swap(l, r);
        if (opr == 3)
            x = rnd() % (r - l + 1) + 1;
        else
            x = rnd() % vmax + 1;
        if (opr == 4)
            y = rnd() % vmax + 1;
        switch (opr)
        {
        case 1:
            ot.add(l, r, x);
            break;
        case 2:
            ot.assign(l, r, x);
            break;
        case 3:
            cout << ot.get_kth_small(l, r, x) << "\n";
            break;
        case 4:
            cout << ot.sum_of_pow(l, r, x, y) << "\n";
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
struct Substring_auto{
    string s;
    int n;
    vector<vector<int>> nxt;
    Substring_auto(string _s, int m = 26){
        this->s = " " + _s;
        this->n = _s.size();
        vector<vector<int>> ((n + 1), vector<int>(m, -1)).swap(nxt);
    }
    void build(){
        for(int i = n; i >= 1 ; i --)
        {
            int t = s[i] - 'a';
            for(int j = 0; j < 26; j ++)
                if(j != t)
                    nxt[i - 1][j] = nxt[i][j];
                else
                    nxt[i - 1][j] = i;
        }
    }
    bool is_substring(string t){
        int idx = 0;
        for(auto i : t) 
        {
            if(nxt[idx][i - 'a'] != -1)
                idx = nxt[idx][i - 'a'];
            else
                return false;
        }
        return true; 
    }
};

int main (){
    ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; cin >> n >> q;
    string s; cin >> s;
    auto s_ac = Substring_auto(s);
    s_ac.build();
    while(q --)
    {
        string t; cin >> t;
        if(s_ac.is_substring(t))
            cout << "YES\n";
        else
            cout << "NO\n";
    } 
    return 0;
}
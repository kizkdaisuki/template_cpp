struct Trie_string{
    int idx = 0;
    vector<vector<int>> tr;
    vector<int> cnt;
    int n;
    Trie_string(int _n)
    {
        vector<vector<int>> (_n + 1, vector<int>(26)).swap(tr);
        cnt.resize(_n + 1);
        this->n = _n; 
    }
    void insert(string& s){
        int p = 0;
        for(auto& i : s)
        {
            int u = i - 'a';
            if(!tr[p][u]) tr[p][u] = ++ idx ;
            p = tr[p][u];
        } 
        cnt[p] ++ ;
    }
    int query_cnt(string& s){
        int p = 0;
        for(auto& i : s)
        {
            int u = i - 'a';
            if(!tr[p][u]) return 0;
            p = tr[p][u];
        }
        return cnt[p];
    }
    bool query_exist(string& s){
        int p = 0;
        for(auto & i : s)
        {
            int u = i - 'a';
            if(!tr[p][u]) return false;
            p = tr[p][u];
        }
        return cnt[p];
    }
};
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
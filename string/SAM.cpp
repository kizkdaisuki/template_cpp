class SAM // 最长公共子串
{
    const int shift = 97;
    struct node
    {
        int ch[26];
        int len;
        int father;
        long long cnt;
        node()
        {
            memset(ch, 0, sizeof(ch));
            len = father = cnt = 0;
        }
    } NIL;
    vector<node> t;
    int last, ind;
    void insert(int c)
    {
        int p = last;
        int np = last = ++ind;
        t.push_back(NIL);
        t[np].len = t[p].len + 1;
        t[np].cnt = 1;
        for (; p && !t[p].ch[c]; p = t[p].father)
            t[p].ch[c] = np;
        if(!p)
            t[np].father = 1;
        else
        {
            int q = t[p].ch[c];
            if (t[p].len + 1 == t[q].len)
                t[np].father = q;
            else
            {
                int nq = ++ind;
                t.push_back(t[q]);
                t[nq].cnt = 0;
                t[nq].len = t[p].len + 1;
                t[q].father = t[np].father = nq;
                for (; p && t[p].ch[c] == q; p = t[p].father)
                    t[p].ch[c] = nq;
            }
        }
    }
 
public:
    SAM(string s)
    {
        last = ind = 1;
        t.push_back(NIL);
        t.push_back(NIL);
        for (auto i : s)
            insert(i - shift);
        vector<vector<int>> graph(t.size());
        for (int i = 2; i <= ind;i++)
            graph[t[i].father].push_back(i);
        function<void(int)> dfs = [&](int place)
        {
            for (auto i : graph[place])
            {
                dfs(i);
                t[place].cnt += t[i].cnt;
            }
        };
        dfs(1);
    }
    int query(string ask)
    {
        int ans = 0, place = 1, now = 0;
        for (auto i : ask)
        {
            while (place > 1 && t[place].ch[i - shift] == 0)
            {
                place = t[place].father;
                now = t[place].len;
            }
            if (place == 1 && t[place].ch[i - shift] == 0)
                continue;
            place = t[place].ch[i - shift];
            now++;
            ans = max(ans, now);
        }
        return ans;
    }
};
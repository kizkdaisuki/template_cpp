#include <bits/stdc++.h>
 
typedef long long LL;

#define int LL

using namespace std;
class PAM
{
    struct node
    {
        int ch[26];
        int fail;
        int len; // 回文串的长度
        long long cnt; // 记录以当前节点为结尾的回文串的个数
        node ()
        {
            memset(ch, 0, sizeof(ch));
            fail = len = cnt = 0;
        }
    };
    vector<node> t; // 存储回文自动机的节点
    vector<int> ans; // 存储每个位置的回文串长度 -> 
    int tot, len, last; // tot表示节点总数，len表示字符串长度，last表示最后一个字符所在的节点
    string s;
    int getfail(int x,int place)
    {
        while (s[place - t[x].len - 1] != s[place])
            x = t[x].fail;
        return x;
    }
    int newnode(int x)
    {
        node temp = *new node;
        temp.len = x;
        t.push_back(temp);
        return ++tot;
    }
 
public:
    PAM(string s)
    {
        int n = s.length();
        this->len = n;
        this->last = 0;
        s = "$" + s;
        this->s = s;
        this->tot = 1;
        this->t.push_back(*new node);
        this->t.push_back(*new node);
        t[0].len = 0;
        t[0].fail = 1;
        t[1].len = -1;
        ans.resize(n);
        for (int i = 1; i <= n;i++)
        {
            int p = getfail(last, i);
            if (!t[p].ch[s[i] - 97])
            {
                int q = newnode(t[p].len + 2);
                t[q].fail = t[getfail(t[p].fail, i)].ch[s[i] - 97];
                t[p].ch[s[i] - 97] = q;
            }
            last = t[p].ch[s[i] - 97];
            t[last].cnt++;
            ans[i - 1] = t[last].len;
        }
        for (int i = tot; i >= 2; i--)
            if (t[i].fail > 1)
                t[t[i].fail].cnt += t[i].cnt;
    }
    int get_ans(){
        int res = 0;
        for(int i = 1; i <= tot; i ++)
            res += t[i].cnt;
        return res;
    }
};
 
void solve() {
    string s; cin >> s;
    PAM res(s);
    cout << res.get_ans() << "\n"; 
}
 
signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T = 1;
    
    while (T--) {
        solve();
    }
    
    return 0;
}
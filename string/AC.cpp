struct node
{
    int fail;
    int ch[27];
    int ans;
};
struct node NIL = {0};
struct trie
{
    vector<node> tr;
    vector<int> in;
    map<int, int> ref;
    int siz = 0;
    void insert(string& s,int x, char offset = 'a')
    {
        if(!tr.size())
            tr.push_back(NIL);
        int place = 0;
        for (char i : s)
        {
            int t = isalpha(i) ? i - offset : 26;
            if (tr[place].ch[t] == 0)
            {
                tr[place].ch[t] = ++siz;
                tr.push_back(NIL);
                in.push_back(0);
            }
            place = tr[place].ch[t];
        }
        ref[x] = place;
    }
    void build()
    {
        queue<int> q;
        for (int i = 0; i < 26;i++)
            if(tr[0].ch[i])
                q.push(tr[0].ch[i]);
        while(!q.empty())
        {
            int tp = q.front();
            q.pop();
            for (int i = 0; i < 26;i++)
                if(tr[tp].ch[i])
                {
                    tr[tr[tp].ch[i]].fail = tr[tr[tp].fail].ch[i];
                    in[tr[tr[tp].fail].ch[i]]++;
                    q.push(tr[tp].ch[i]);
                }
                else
                    tr[tp].ch[i] = tr[tr[tp].fail].ch[i];
        }
    }
    void query(string& t, char offset = 'a')
    {
        int place = 0;
        for (char i : t)
        {
            int t = isalpha(i) ? i - offset : 26;
            place = tr[place].ch[t];
            tr[place].ans++;
        }
    }
    void topo()
    {
        queue<int> q;
        for (int i = 1; i <= siz;i++)
            if(!in[i])
                q.push(i);
        while(!q.empty())
        {
            int tp = q.front();
            q.pop();
            tr[tr[tp].fail].ans += tr[tp].ans;
            in[tr[tp].fail]--;
            if(!in[tr[tp].fail])
                q.push(tr[tp].fail);
        }
    }
};

void test(){
    int n; cin >> n;
	string b = "";
	trie acam;
	string a;
	for(int i = 1; i <= n; i ++)
	    cin >> a, acam.insert(a, i), b += a, b += '#';
	acam.build();
	acam.query(b); acam.topo();
	int res = 0;
	for(int i = 1; i <= n; i ++)
	    cout << acam.tr[acam.ref[i]].ans << "\n";
}
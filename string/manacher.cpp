vector<int> manacher(string a)
{
    string b = "$|";
    for (auto i : a)
    {
        b += i;
        b += '|';
    }
    int len = b.length();
    vector<int> hw(b.length());
    int maxright = 1, mid = 1;
    for (int i = 1; i < len; i++)
    {
        if (i < maxright)
            hw[i] = min(hw[mid * 2 - i], hw[mid] + mid - i);
        else
            hw[i] = 1;
        while (b[i - hw[i]] == b[i + hw[i]])
            hw[i]++;
        if (i + hw[i] > maxright)
        {
            maxright = i + hw[i];  // 跟新区间记得注意
            mid = i;
        }
    }
    return hw;
}
int get_all_strings(string& a){
    unordered_set<string> s;
    string b = "$|";
    for (auto i : a)
    {
        b += i;
        b += '|';
    }
    int len = b.length();
    vector<int> hw(b.length());
    int maxright = 1, mid = 1;
    vector<pair<int, int>> v;
    for (int i = 1; i < len; i++)
    {
        if (i < maxright)
            hw[i] = min(hw[mid * 2 - i], hw[mid] + mid - i);
        else
            hw[i] = 1;
        while (b[i - hw[i]] == b[i + hw[i]])
            hw[i]++;
        if (i + hw[i] > maxright)
        {
            maxright = i + hw[i];  // 跟新区间记得注意
            mid = i;
            v.emplace_back(mid, maxright - 1);
        }
    }
    for(auto [l, r] : v)
    {
        string t = "";
        if(l % 2 == 0) t += a[(l >> 1) - 1];
        for(int i = l / 2; i < r / 2; i ++)
        {
            t = a[i] + t + a[i];
            s.insert(t);
        }
        s.insert(t);
    }
    return s.size();
}
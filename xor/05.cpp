
#include <bits/stdc++.h>
 
typedef long long LL;
#define int LL

using namespace std;

const int mod = 1e9 + 7;
// 求所有连续子数组中 两两配对的异或值
signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n); for(int& i : a) cin >> i;
    LL res = 0;
    for(int k = 0; k < 30; k ++)
    {
    	vector<int> l(n), r(n);
    	for(int i = 0; i < n; i ++)
    		r[i] = (a[i] >> k) & 1, l[i] = 1 - r[i];
    	vector<LL> s0(n + 1), s1(n + 1);
    	for(int i = 0; i < n; i ++)
    		if(r[i])
    		{
    			s1[i + 1] = s1[i] + i + 1;
    			s0[i + 1] = s0[i];	
    		}
    		else
    		{
    			s0[i + 1] = s0[i] + i + 1;
    			s1[i + 1] = s1[i];
    		}
    	for(int i = n - 1; i >= 0; i --)
    	{
    		if(r[i])
    			res += (n - i) * (1 << k) % mod * s0[i] % mod;
    		else
    			res += (n - i) * (1 << k) % mod * s1[i] % mod;
    	}
    	res %= mod;
    }
    cout << res << "\n";
    
    return 0;
}

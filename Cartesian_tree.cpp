// 区间最小值 -> 左右端点的LCA
template <class T>
struct CartesianTree{
    vector<T> a;
    vector<int> l, r;
    int root, n;
    CartesianTree(int _n) : n(_n), a(_n + 1), l(_n + 1), r(_n + 1) {}
    CartesianTree(vector<T> _a) : n(_a.size() - 1), a(_a), l(_a.size(), 0), r(_a.size(), 0) {this->init();}
    void init(){
        stack<int> st;
        int n = this->a.size();
        for(int i = 1; i <= n; i ++)
        {
            int last = 0;
            while(st.size() && a[st.top()] > a[i])
            {
                last = st.top();
                st.pop();
            }
            if(st.size()) r[st.top()] = i;
            else
                this->root = i;
            l[i] = last;
            st.push(i);
        }
    }
    void print(){
    	for(int i = 1; i <= n; i ++)
    		cout << " i : " << i << " " << " a[i] : " << a[i] << " " << " l[i] : " << l[i] << " r[i] " << r[i] << "\n";
    }
}; 
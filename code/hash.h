
#define MH 600006
#define Base1 10000019
#define Base2 10000079
#define MOD1 1000000007
#define MOD2 1000000009
ll B1[MH], B2[MH];
void init_hash()
{
    B1[0] = B2[0] = 1;
    for (int i = 1; i < MH; i++)
    {
        B1[i] = (B1[i - 1] * Base1) % MOD1;
        B2[i] = (B2[i - 1] * Base2) % MOD2;
    }
}
struct Hash
{
    pll *H;
    int *digit;
    int len;
    Hash()
    {
        H = new pll[MH];
        digit = new int[MH];
        len = 0;
        H[0] = pll(0, 0);
    }
    void clear()
    {
        len = 0;
        H[0] = pll(0, 0);
    }
    ~Hash()
    {
        delete (H);
        delete (digit);
    }
    void insert(char ch)
    {
        len++;
        digit[len] = ch - 'a' + 1;
        H[len].ff = (((H[len - 1].ff * Base1) % MOD1) + digit[len]) % MOD1;
        H[len].ss = (((H[len - 1].ss * Base2) % MOD2) + digit[len]) % MOD2;
    }
    pll substr(int l, int r)
    {
        if (l > len || r < 1 || r < l)
            return pll(0, 0);
        int sub_len = r - l + 1;
        pll ans;
        ans.ff = (H[r].ff - ((H[l - 1].ff * B1[sub_len]) % MOD1) + MOD1) % MOD1;
        ans.ss = (H[r].ss - ((H[l - 1].ss * B2[sub_len]) % MOD2) + MOD2) % MOD2;
        return ans;
    }
    pll concate(pll h, int l, int r)
    {
        pll x = substr(l, r);
        int sub_len = r - l + 1;
        h.ff = (((h.ff * B1[sub_len]) % MOD1) + x.ff) % MOD1;
        h.ss = (((h.ss * B2[sub_len]) % MOD2) + x.ss) % MOD2;
        return h;
    }
    bool operator==(const Hash &p) const
    {
        return len == p.len && H[len] == p.H[len];
    }
    pll &operator[](int index)
    {
        return H[index];
    }
};
No array
    string s;
#define Base1 10000019
#define Base2 10000079
#define MOD1 1000000007
#define MOD2 1000000009
map<pll, bool> mp;
pll calc_hash()
{
    int len = s.size();
    ll ans1 = 0;
    ll ans2 = 0;
    for (int i = 0; i < len; i++)
    {
        ll x = s[i] - 'a' + 1;
        ans1 = ((ans1 * Base1) % MOD1 + x) % MOD1;
        ans2 = ((ans2 * Base2) % MOD2 + x) % MOD2;
    }
    return MP(ans1, ans2);
}
const int N = 3 * 1e5 + 9;
pll power[N];
void pre()
{
    power[0].ff = 1;
    power[0].ss = 1;
    for (int i = 1; i < N; i++)
    {
        power[i].ff = (power[i - 1].ff * Base1) % MOD1;
        power[i].ss = (power[i - 1].ss * Base2) % MOD2;
    }
}
pll get_val(int pos, int val)
{
    int px = s.size() - pos - 1;
    px = max(0, px);
    ll div1 = (power[px].ff * (val + 1)) % MOD1;
    ll div2 = (power[px].ss * (val + 1)) % MOD2;
    return MP(div1, div2);
}
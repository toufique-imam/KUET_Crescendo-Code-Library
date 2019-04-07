Finding sum(i ^ k)
//Faulhaber's Formula: sum(i ^ k) = 1 / (a + 1) * sum_(j = 0->a) _(-1) ^ j * a + 1_C_j * bernoulli[j] * n ^ (a + 1 - j) const int MAX_N = 1e3 + 9;
const int INF = 2000000000;
const ll MOD = 1e9 + 7;
ll combi[MAX_N + 2][MAX_N + 2]; //aCb = combi[a][b]
void makeCombiMod()
{
    combi[0][0] = 1;
    combi[1][0] = 1;
    combi[1][1] = 1;
    for (int i = 2; i <= MAX_N; i++)
    {
        combi[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            combi[i][j] = combi[i - 1][j] + combi[i - 1][j - 1];
            combi[i][j] %= MOD;
        }
    }
}

// a x + b y = gcd(a, b)
ll extgcd(ll a, ll b, ll &x, ll &y)
{
    ll g = a;
    x = 1;
    y = 0;
    if (b != 0)
        g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}
// 1/a mod m
ll mod_inverse(ll a)
{
    ll x, y;
    extgcd(a, MOD, x, y);
    return (MOD + x % MOD) % MOD;
}

ll B[MAX_N + 2];
void initBernoulliMod()
{
    makeCombiMod();
    for (int i = 0; i < MAX_N + 1; i++)
    {
        if (i % 2)
            B[i] = 0;
        else
            B[i] = -INF;
    }
    B[0] = 1;
    B[1] = -mod_inverse(2) + MOD;
}

ll BernoulliMod(int n)
{
    if (B[n] == -INF)
    {
        ll sum = (1 + combi[n + 1][1] * B[1]) % MOD;
        for (int i = 2; i < n; i += 2)
            sum = (sum + (combi[n + 1][i] * BernoulliMod(i) % MOD)) % MOD;
        B[n] = sum * mod_inverse(n + 1) % MOD;
        B[n] *= -1;
        while (B[n] < 0)
            B[n] += MOD;
    }
    return B[n];
}
ll powMod(ll n, ll p)
{
    ll ans = 1, ln = n % MOD;
    if (p <= 0)
        return 1;
    while (p != 0)
    {
        if ((p & 1) == 1)
            ans = (ans * ln) % MOD;
        ln = (ln * ln) % MOD;
        p = p >> 1;
    }
    return ans;
}
int main()
{
    ll n, a;
    initBernoulliMod();
    QUERY
    {
        scanf("%lld %lld", &n, &a);
        ll ans = 0;
        ll x;
        int i;
        for (int j = 0; j <= a; j++)
        {
            x = (combi[a + 1][j] * BernoulliMod(j)) % MOD;
            i = a + 1 - j;
            x = (x * powMod(n, i)) % MOD;
            if (j & 1)
                ans -= x;
            else
                ans += x;
            ans %= MOD;
            ans = (ans + MOD) % MOD;
        }
        ll xx = mod_inverse(a + 1);
        ans = (ans * xx) % MOD;
        printf("%lld\n", ans);
    }
}

//LCA
//[0->N)
const int N = 10000;
vector<pii> v[N + 2];
int level[N + 3];
int dist[N + 3];
int T[N + 2];
int sparse_table[N + 2][16];
unsigned int power[16];
int pwrsz;
void cln();
void dfs(int x, int par);
void create_sparse(int n);
int find_lca(int v1, int v2);
int find_dist(int v1, int v2);
int bin_sch(int key);
int find_k(int v1, int k);
int find_kth_par(int v1, int v2, int K);
int main()
{
    for (int i = 0; (1 << i) <= N; i++)
    {
        power[i] = (1 << i);
        pwrsz++;
    }
    fast;
    int test;
    cin >> test;
    while (test--)
    {
        cln();
        int n;
        cin >> n;
        int a, b, c;
        for (int i = 1; i < n; i++)
        {
            cin >> a >> b >> c;
            a--;
            b--;
            v[a].pb(make_pair(b, c));
            v[b].pb(make_pair(a, c));
        }
        dfs(0, 0);
        create_sparse(n);
        string s;
        while (cin >> s)
        {
            if (s[0] == 'D' and s[1] == 'O')
                break;
            cin >> a >> b;
            a--;
            b--;
            if (s[0] == 'D')
                cout << find_dist(a, b) << endl;
            else
            {
                cin >> c;
                c--;
                cout << find_kth_par(a, b, c) + 1 << endl;
            }
        }
    }
}
void cln()
{
    for (int i = 0; i <= N; i++)
    {
        v[i].clear();
        level[i] = 0;
        T[i] = 0;
        dist[i] = 0;
    }
}
void dfs(int x, int par)
{
    T[x] = par;
    int u, dis;
    for (int i = 0; i < (int)v[x].size(); i++)
    {
        u = v[x][i].ff;
        dis = v[x][i].ss;
        if (par == u)
            continue;
        level[u] = level[x] + 1;
        dist[u] = dist[x] + dis;
        dfs(u, x);
    }
}
void create_sparse(int n)
{
    memset(sparse_table, -1, sizeof sparse_table);
    for (int i = 0; i < n; i++)
        sparse_table[i][0] = T[i];
    for (int j = 1; (1 << j) < n; j++)
        for (int i = 0; i < n; i++)
            if (sparse_table[i][j - 1] != -1)
                sparse_table[i][j] = sparse_table[sparse_table[i][j - 1]][j - 1];
}
int find_lca(int v1, int v2)
{
    if (level[v1] < level[v2]) //Bigger level in V1
        swap(v1, v2);
    int lg = 1;
    int nxt = lg + 1;
    while ((1 << nxt) <= level[v1]) //highest depth for 2^i
    {
        lg++;
        nxt = lg + 1;
    }
    for (int i = lg; i > -1; i--)
        if (level[v1] - (1 << i) >= level[v2])
            v1 = sparse_table[v1][i];
    if (v1 == v2)
        return v1;
    for (int i = lg; i >= 0; i--)
        if (sparse_table[v1][i] != -1 and sparse_table[v1][i] != sparse_table[v2][i])
            v1 = sparse_table[v1][i], v2 = sparse_table[v2][i];
    return T[v1];
}
int find_dist(int v1, int v2)
{
    int x = find_lca(v1, v2);
    return dist[v1] + dist[v2] - 2 * dist[x];
}
int bin_sch(int key)
{
    int ans = 0, lo = 0, hi = pwrsz - 1;
    int mid;
    while (hi >= lo)
    {
        mid = (hi + lo) / 2;
        if (power[mid] <= key)
            ans = mid, lo = mid + 1;
        else
            hi = mid - 1;
    }
    return ans;
}
int find_k(int v1, int k)
{
    int ans = v1, j;
    while (k > 0)
    {
        j = bin_sch(k);
        k -= power[j];
        ans = sparse_table[ans][j];
    }
    return ans;
}
int find_kth_par(int v1, int v2, int K)
{
    int x = find_lca(v1, v2);
    int X = level[v1] - level[x];
    int Y = level[v2] - level[x];
    if (K <= X)
        return find_k(v1, K);
    else
        return find_k(v2, Y - K + X);
}

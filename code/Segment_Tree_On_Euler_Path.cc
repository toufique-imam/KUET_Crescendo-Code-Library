int dfs_low[N];
int dfs_high[N];
ll tree_[10 * N];
int lazy[10 * N];
vector<int> edge[N];
int color[N];
int tim = 0;
void dfs(int x, int par = 0)
{
    dfs_low[x] = ++tim;
    for (int i = 0; i < edge[x].size(); i++)
    {
        if (dfs_low[edge[x][i]] == 0)
            dfs(edge[x][i], x);
    }
    dfs_high[x] = tim;
}
void push_down(int node, int st, int en)
{
    int lt = node * 2;
    int rg = node * 2 + 1;

    tree_[lt] = (1ll << lazy[node]);
    tree_[rg] = (1ll << lazy[node]);

    if (st != en)
    {
        lazy[lt] = lazy[node];
        lazy[rg] = lazy[node];
    }
    lazy[node] = 0;
}
void update1(int node, int st, int en, int l, int r, int col)
{
    if (st >= l && en <= r)
    {
        tree_[node] |= (1ll << col);
        return;
    }
    if (st > r || en < l)
        return;
    int mid = (st + en) / 2;
    int lt = node * 2;
    int rg = node * 2 + 1;
    update1(lt, st, mid, l, r, col);
    update1(rg, mid + 1, en, l, r, col);
    tree_[node] = tree_[lt] | tree_[rg];
}
ll query(int node, int st, int en, int l, int r)
{
    if (lazy[node])
        push_down(node, st, en);
    if (st > r || en < l)
        return 0ll;
    if (st >= l && en <= r)
    {
        return tree_[node];
    }
    int mid = (st + en) / 2;
    int lt = node * 2;
    int rg = node * 2 + 1;
    ll x = query(lt, st, mid, l, r);
    ll y = query(rg, mid + 1, en, l, r);
    return x | y;
}
void update2(int node, int st, int en, int l, int r, int col)
{
    if (lazy[node])
        push_down(node, st, en);
    if (st > r || en < l)
        return;
    if (st >= l && en <= r)
    {
        tree_[node] = (1ll << col);
        if (st != en)
            lazy[node] = col;
        return;
    }
    int mid = (st + en) / 2;
    int lt = node * 2;
    int rg = node * 2 + 1;
    update2(lt, st, mid, l, r, col);
    update2(rg, mid + 1, en, l, r, col);
    tree_[node] = tree_[lt] | tree_[rg];
}
int main()
{
    int n, q, a, b;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &color[i]);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        edge[a].emplace_back(b);
        edge[b].emplace_back(a);
    }
    dfs(1);
    //    for(int i=1;i<=n;i++){
    //        cerr<<i<<" "<<dfs_low[i]<<" "<<dfs_high[i]<<"\n";
    //    }
    for (int i = 1; i <= n; i++)
    {
        update1(1, 1, tim, dfs_low[i], dfs_low[i], color[i]);
        //update1(1,1,tim,dfs_high[i],dfs_high[i],color[i]);
    }
    int c;
    while (q--)
    {
        scanf("%d", &a);
        if (a == 1)
        {
            scanf("%d %d", &b, &c);
            update2(1, 1, tim, dfs_low[b], dfs_high[b], c);
        }
        else
        {
            scanf("%d", &b);
            ll x = query(1, 1, tim, dfs_low[b], dfs_high[b]);
            ll ans = total_1s(x);
            //ans=max(1ll,ans);
            printf("%I64d\n", ans);
        }
    }
}

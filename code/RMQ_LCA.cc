/*
Dont be confused with topcoder's tutorial
use : x+2^(j-1) during initialization not x+2^(j-1)-1
Query function is ok in topcoder's tutorial
*/
const int N = 100000 + 9;
pair<int, int> tree[N][30];
int ara[N];

int myLog2(int x)
{
    return __builtin_clz(1) - __builtin_clz(x);
}
void build(int n)
{
    for (int i = 1; i <= n; i++)
    {
        tree[i][0] = MP(i, i);
    }
    int limi = myLog2(n);
    for (int j = 1; j <= limi; j++)
    {
        for (int i = 1; i + ((1 << j) - 1) <= n; i++)
        {
            if (ara[tree[i][j - 1].ff] > ara[tree[i + (1 << (j - 1))][j - 1].ff])
                tree[i][j].ff = tree[i][j - 1].ff;
            else
                tree[i][j].ff = tree[i + (1 << (j - 1))][j - 1].ff;

            if (ara[tree[i][j - 1].ss] < ara[tree[i + (1 << (j - 1))][j - 1].ss])
                tree[i][j].ss = tree[i][j - 1].ss;
            else
                tree[i][j].ss = tree[i + (1 << (j - 1))][j - 1].ss;
        }
    }
}
int query_min(int l, int r)
{
    int k = myLog2(r - l + 1);
    int val1 = ara[tree[l][k].ss];
    int val2 = ara[tree[r - (1 << k) + 1][k].ss];
    return min(val1, val2);
}
int query_max(int l, int r)
{

    int k = myLog2(r - l + 1);
    int val1 = ara[tree[l][k].ff];
    int val2 = ara[tree[r - (1 << k) + 1][k].ff];
    return max(val1, val2);
}
//If We want to Update range L-R 1 to R-L+1
#define sum(x) x *(x + 1) / 2
void push_down(int node, ll st, ll en)
{
    if (st != en)
    {
        ll mid = (st + en) / 2, lt = node * 2, rg = node * 2 + 1;

        tree[lt].lazy = tree[rg].lazy = 1;

        tree[lt].start += tree[node].start;
        tree[lt].en += tree[node].start + (mid - st) * tree[node].inc;

        tree[rg].start += (tree[node].start + (mid - st + 1) * tree[node].inc);
        tree[rg].en += tree[node].en;

        tree[lt].inc += tree[node].inc;
        tree[rg].inc += tree[node].inc;

        tree[lt].sum += (tree[node].start * (mid - st + 1)) + tree[node].inc * sum(mid - st);

        tree[rg].sum += (tree[node].start * (en - st + 1)) + tree[node].inc * sum(en - st) - (tree[node].start * (mid - st + 1)) - tree[node].inc * sum(mid - st);
    }
    tree[node].en = tree[node].start = tree[node].inc = 0;
    tree[node].lazy = 0;
}
void update(int node, ll st, ll en, ll L, ll R)
{
    if (tree[node].lazy)
        push_down(node, st, en);
    if (en < L || st > R)
        return;
    if (st >= L and en <= R)
    {
        ll fx, fs;
        st == L ? fx = 1 : fx = (st - L + 1);
        en == R ? fs = R - L + 1 : fs = (R - L + 1) - (R - en);
        tree[node].sum += sum(fs) - sum(fx - 1);
        tree[node].lazy = 1;
        tree[node].start += fx;
        tree[node].en += fs;
        tree[node].inc++;
        return;
    }
    ll mid = (st + en) / 2;
    update(node * 2, st, mid, L, R);
    update(node * 2 + 1, mid + 1, en, L, R);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
    tree[node].en = tree[node].start = tree[node].inc = 0;
    tree[node].lazy = 0;
}

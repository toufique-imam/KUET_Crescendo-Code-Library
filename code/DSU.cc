int par[N];
int hight[N];
int find_(int x)
{
    while(x!=par[x])
    {
        par[x]=par[par[x]];
        x=par[x];
    }
    return x;
}
void UNION(int x,int y)
{
    x=find_(x);
    y=find_(y);
    if(x!=y)
    {
        if(hight[x]<hight[y])
            swap(x,y);
        par[y]=x;
        hight[x]+=hight[y];
    }
}

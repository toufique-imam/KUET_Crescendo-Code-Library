//2D RMQ
//sparse_table N*logN*M*logM
const int N = 501;
int table[N][12][N][12];
int n, m;
void create_sparse()
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 1; (1 << k) <= m; k++)
            for (int j = 0; j + (1 << k) - 1 < m; j++)
                table[i][0][j][k] = max(table[i][0][j][k - 1], table[i][0][j + 1 << (k - 1)][k - 1]);
    }
    for (int pi = 1; (1 << pi) <= n; pi++)
        for (int i = 0; i < n; i++)
            for (int pj = 0; (1 << pj) <= m; pj++)
                for (int j = 0; j < m; j++)
                    table[i][pi][j][pj] = max(table[i][pi - 1][j][pj], table[i + (1 << (pi - 1))][pi - 1][j][pj]);
}
int query(int x1, int y1, int x2, int y2)
{
    int lenx = x2 - x1 + 1;
    int leny = y2 - y1 + 1;
    int kx = log(lenx);
    int ky = log(leny);
    return max(table[x1][kx][y1][ky], max(table[x1][kx][y2 + 1 - (1 << ky)][ky], max(table[x2 + 1 - (1 << kx)][kx][y1][ky], table[x2 + 1 - (1 << kx)][kx][y2 + 1 - (1 << ky)][ky])));
}

//Less Space Complexity
//loj square queries 
const int N = 503;
unsigned int table[N][N][10];
int n, m;
void create_sparse()
{
    for (int k = 1; (1 << k) <= m; k++)
        for (int i = 0; i + (1 << k) - 1 < n; i++)
            for (int j = 0; j + (1 << k) - 1 < m; j++)
            {
                table[i][j][k] = max(table[i][j][k - 1], max(table[i][j + (1 << (k - 1))][k - 1], max(table[i + (1 << (k - 1))][j][k - 1], table[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1])));
            }
}
unsigned int query(int i, int j, int S)
{
    int p = log2(S);
    assert((j + S - (1 << p)) > -1 and (j + S - (1 << p)) < n);
    assert((i + S - (1 << p)) > -1 and (i + S - (1 << p)) < n);
    return max(table[i][j][p], max(table[i][j + S - (1 << p)][p], max(table[i + S - (1 << p)][j][p], table[i + S - (1 << p)][j + S - (1 << p)][p])));
}
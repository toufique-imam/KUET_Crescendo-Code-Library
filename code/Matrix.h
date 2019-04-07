typedef vector<vector<ll>> matrix;
matrix base, I, zero;
int mod = 10;
int K = 2;
matrix mul(matrix A, matrix B)
{
    matrix c(K + 1, vector<ll>(K + 1));
    for (int i = 1; i <= K; i++)
        for (int j = 1; j <= K; j++)
            for (int k = 1; k <= K; k++)
                c[i][j] = (c[i][j] + A[i][k] * B[k][j]) % mod;
    return c;
}
matrix pow(matrix A, int p)
{
    if (p == 0)
        return I;
    if (p == 1)
        return A;
    if (p % 2)
        return mul(A, pow(A, p - 1));
    matrix x = pow(A, p / 2);
    return mul(x, x);
}
matrix sum(matrix A, matrix B)
{
    matrix c(K + 1, vector<ll>(K + 1));
    for (int i = 1; i <= K; i++)
        for (int j = 1; j <= K; j++)
            c[i][j] = (A[i][j] + B[i][j]) % mod;
    return c;
}
matrix bigsum(int p)
{
    if (p == 0)
        return zero;
    if (p % 2 == 1)
        return sum(mul(bigsum(p / 2), sum(I, pow(base, p / 2))), pow(base, p));
    p /= 2;
    return mul(bigsum(p), sum(I, pow(base, p)));
}
int solve()
{
    // create vector F1
    vector<ll> F1(K + 1);
    F1[1] = 1;
    F1[2] = 1;
    // create matrix T
    matrix T(K + 1, vector<ll>(K + 1));
    T[1][1] = 0, T[1][2] = 1;
    T[2][1] = 1, T[2][2] = 1;

    // raise T to the (N-1)th power
    if (N == 1)
        return 1;
    T = pow(T, N - 1);
    // the answer is the first row of T . F1
    ll res = 0;
    REP(i, K)
    res = (res + T[1][i] * F1[i]) % mod;
    return res;
}

Matrix identity(int n) {
    Matrix res(n, n);
    REP(i,n) res.x[i][i] = 1;
    return res;
}

string ans;
string mid_inc(string t)
{
    int i = (t.size() - 1) / 2;
    int j = i + 1;
    int c = 1;
    if (t[i] == '9')
    {
        c = 1;
        t[i] = '0';
    }
    else
    {
        c = 0;
        t[i] += 1;
    }
    i--;
    if (t.size() % 2 == 0)
    {
        if (t[j] == '9')
        {
            c = 1;
            t[j] = '0';
        }
        else
        {
            c = 0;
            t[j] = t[j] + 1;
        }
        j++;
    }
    while (i > -1 && j < t.size() && c)
    {
        if (t[i] == '9')
        {
            c = 1;
            t[i] = t[j] = '0';
        }
        else
        {
            c = 0;
            t[i] += 1;
            t[j] = t[i];
        }
        i--;
        j++;
    }
    return t;
}

bool check_9(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] - '0' != 9)
            return 0;
    }
    ans = "1";
    for (int i = 1; i < s.size(); i++)
        ans += '0';
    ans += '1';
    return 1;
}
bool is_palindrome(string t)
{
    int i = 0, j = t.size() - 1;
    for (; i < j; i++, j--)
    {
        if (t[i] != t[j])
            return 0;
    }
    ans = mid_inc(t);
    return 1;
}
void next_palindrome(string t)
{
    if (check_9(t))
    {
        cout << ans << endl;
        return;
    }
    else if (is_palindrome(t))
    {
        cout << ans << endl;
        return;
    }
    int i = t.size() / 2 - 1;
    int j;
    if (t.size() % 2)
        j = t.size() / 2 + 1;
    else
        j = t.size() / 2;
    while (i > -1 && t[i] == t[j])
        i--, j++;
    bool bigger = 0;
    if (t[i] > t[j])
        bigger = 1;
    while (i > -1)
    {
        t[j] = t[i];
        j++;
        i--;
    }
    if (!bigger)
        ans = mid_inc(t);
    else
        ans = t;
    cout << ans << endl;
}
int main()
{
    string s;
    QUERY
    {
        ans = "";
        cin >> s;
        printf("Case %d: ", _T);
        next_palindrome(s);
    }
}

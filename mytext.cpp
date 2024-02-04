#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pq = priority_queue<int>;

int main(void)
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int m, n;
    cin >> m >> n;
    vector<int> man(m);
    for (auto &x : man)
        cin >> x;
    sort(man.begin(), man.end());

    vector<pq> farm(n);
    int num, tmp, mxt = 0;
    for (auto &i : farm)
    {
        cin >> num;
        mxt = max(mxt, num);
        for (int k = 0; k < num; ++k)
        {
            cin >> tmp;
            i.push(tmp);
        }
    }

    bool flag = true;
    ll ans = 0;
    vector<int> c(m);
    for (int i = 0; i < mxt; ++i)
    {
        int mx = 0;
        for (int j = 0; j < n; ++j)
        {
            if (farm[j].empty())
                continue;
            mx = max(mx, farm[j].top());
        }

        int j = m - 1;
        if (man[j] < mx)
        {
            flag = false;
            goto end;
        }

        while (j > 0 && man[j - 1] >= mx)
            j--;

        for (int k = 0; k < n; ++k)
        {
            if (!farm[k].empty())
                farm[k].pop();
        }
        c[j]++;
    }

    for (int i = 0; i < m; ++i)
    {
        if (c[i] > 1)
        {
            if (i == m - 1)
            {
                flag = false;
                break;
            }

            c[i + 1] += c[i] - 1;
            c[i] = 1;
        }
        if (c[i] == 1)
            ans += man[i];
    }

end:;
    if (flag)
        cout << ans << '\n';
    else
        cout << "-1\n";
    return 0;
}
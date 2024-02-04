// 数据1：
/*
3 4
2 9 6
2 3 7
1 5
3 2 2 3
3 1 1 1
*/
// 数据2：
/*
3 4
2 9 6
2 3 6
1 5
3 2 2 3
3 1 1 1
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(void)
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int m, n;
    cin >> m >> n;
    vector<int> a(m); // 输入冒险者的能力并对其进行排序
    for (auto &i : a)
        cin >> i;
    sort(a.begin(), a.end());

    vector<vector<int>> b(n); // 开二维数组，录入各个村庄委托，并对其排序
    int mxk = 0;              // mxk 是最多委托数量
    for (auto &i : b)
    {
        int k;
        cin >> k;
        i.resize(k); // 设置数组大小
        for (auto &j : i)
            cin >> j;
        sort(i.begin(), i.end());
        mxk = max(mxk, k);
    }

    vector<int> c(m); // c[] 作用 --> 记录使用情况
    ll ans = 0;
    for (int t = 0; t < mxk; ++t)
    {
        int mx = 0;
        for (int i = 0; i < n; ++i)
        {
            if (!b[i].empty())             // 取 vector 之前要判断元素是否为空
                mx = max(mx, b[i].back()); // mx 为所有委托里面最耗费精力的任务，肯定是我们要做到的委托
        }

        int j = m - 1;
        if (a[j] < mx) // 最难的任务不能被任何冒险者完成
        {
            cout << "-1\n";
            goto end;
        }

        while (j > 0 && a[j - 1] >= mx) // 找可以完成任务且消耗最小的冒险者
            j--;

        for (int i = 0; i < n; ++i) // 完成的任务扔掉
        {
            if (!b[i].empty())
                b[i].pop_back();
        }

        c[j]++; // 记录使用
    }

    for (int i = 0; i < m; ++i)
    {
        if (c[i] > 1)
        {
            if (i == m - 1) // 当前没有比这个冒险者更强的了，但是仍然需要，所以输出 -1
            {
                cout << "-1\n";
                goto end;
            }
            c[i + 1] += c[i] - 1;
            c[i] = 1;
        }
        if (c[i] == 1)
            ans += a[i];
    }

    cout << ans << '\n';
end:;
    return 0;
}
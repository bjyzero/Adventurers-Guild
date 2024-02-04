#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pq = priority_queue<int>;    //这里给每个村庄的委托排序，开优先队列

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
        mxt = max(mxt, num);    //找到最大的委托数量，来确定需要派出冒险者多少次
        for (int k = 0; k < num; ++k)
        {
            cin >> tmp;
            i.push(tmp);
        }
    }

    bool flag = true;
    ll ans = 0;
    vector<int> c(m);    //数组c 主要来记录冒险者的出勤次数
    for (int i = 0; i < mxt; ++i)
    {
        int mx = 0;
        for (int j = 0; j < n; ++j)
        {
            if (farm[j].empty())
                continue;
            mx = max(mx, farm[j].top());    //找难度值最大的委托，肯定是后面需要做到的委托，以此来确定冒险者
        }
        
        int j = m - 1;
        if (man[j] < mx)
        {
            flag = false;
            goto end;    //这里特别注释说明一下，如果要使用 goto 来跳跃语句，则在跳跃的范围内不能有变量的初始化
        }

        while (j > 0 && man[j - 1] >= mx)    //找到刚刚可以完成该任务的冒险者
            j--;

        for (int k = 0; k < n; ++k)
        {
            if (!farm[k].empty())    //每次在取出队列中的数值先判断是否为空
                farm[k].pop();
        }
        c[j]++;
    }

    for (int i = 0; i < m; ++i)    //这里就是如果冒险者的出勤次数不是 1，且后面有能力更大的冒险者，则往后推
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

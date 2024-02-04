// ����1��
/*
3 4
2 9 6
2 3 7
1 5
3 2 2 3
3 1 1 1
*/
// ����2��
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
    vector<int> a(m); // ����ð���ߵ������������������
    for (auto &i : a)
        cin >> i;
    sort(a.begin(), a.end());

    vector<vector<int>> b(n); // ����ά���飬¼�������ׯί�У�����������
    int mxk = 0;              // mxk �����ί������
    for (auto &i : b)
    {
        int k;
        cin >> k;
        i.resize(k); // ���������С
        for (auto &j : i)
            cin >> j;
        sort(i.begin(), i.end());
        mxk = max(mxk, k);
    }

    vector<int> c(m); // c[] ���� --> ��¼ʹ�����
    ll ans = 0;
    for (int t = 0; t < mxk; ++t)
    {
        int mx = 0;
        for (int i = 0; i < n; ++i)
        {
            if (!b[i].empty())             // ȡ vector ֮ǰҪ�ж�Ԫ���Ƿ�Ϊ��
                mx = max(mx, b[i].back()); // mx Ϊ����ί��������ķѾ��������񣬿϶�������Ҫ������ί��
        }

        int j = m - 1;
        if (a[j] < mx) // ���ѵ������ܱ��κ�ð�������
        {
            cout << "-1\n";
            goto end;
        }

        while (j > 0 && a[j - 1] >= mx) // �ҿ������������������С��ð����
            j--;

        for (int i = 0; i < n; ++i) // ��ɵ������ӵ�
        {
            if (!b[i].empty())
                b[i].pop_back();
        }

        c[j]++; // ��¼ʹ��
    }

    for (int i = 0; i < m; ++i)
    {
        if (c[i] > 1)
        {
            if (i == m - 1) // ��ǰû�б����ð���߸�ǿ���ˣ�������Ȼ��Ҫ��������� -1
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
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

namespace SA
{
	const int MAXN = 1000010;

	char str[MAXN];
	int cnt[MAXN], sa[MAXN], rank[MAXN], height[MAXN], t1[MAXN], t2[MAXN];

	inline void Solve(int n, int m)
	{
		int *x = t1, *y = t2;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) ++cnt[x[i] = str[i]];
		for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) sa[--cnt[x[i]]] = i;
		for (int k = 1; k <= n; k <<= 1)
		{
			int p = 0;
			for (int i = n - k; i < n; ++i) y[p++] = i;
			for (int i = 0; i < n; ++i)
			if (sa[i] >= k) y[p++] = sa[i] - k;
			memset(cnt, 0, sizeof(cnt));
			for (int i = 0; i < n; ++i) ++cnt[x[y[i]]];
			for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
			for (int i = n - 1; i >= 0; --i) sa[--cnt[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1;
			x[sa[0]] = 0;
			for (int i = 1; i < n; ++i)
				x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++);
			if (p >= n) break;
			m = p;
		}
	}

	inline void GetHeight(int n)
	{
		for (int i = 0; i < n; ++i) rank[sa[i]] = i;
		for (int i = 0, k = 0; i < n - 1; ++i)
		{
			if (k) --k;
			int j = sa[rank[i] - 1];
			while (str[i + k] == str[j + k]) ++k;
			height[rank[i]] = k;
		}
	}
}

using namespace SA;

int main()
{
	int n = fread(str, 1, MAXN, stdin);
	Solve(n + 1, 128);
	for (int i = 1; i <= n; ++i) printf("%d ", sa[i] + 1);
	printf("\n");
	return 0;
}
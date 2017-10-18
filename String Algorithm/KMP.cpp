#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

namespace KMP
{
	const int MAXN = 1000010;

	char str[MAXN], pat[MAXN];
	int n, m, next[MAXN];

	inline void GetNext()
	{
		next[0] = -1;
		int i = 0, j = -1;
		while (i < m)
		{
			if (j == -1 || pat[i] == pat[j])
			{
				if (pat[++i] != pat[++j]) next[i] = j;
				else next[i] = next[j];
			}
			else j = next[j];
		}
	}

	inline int Solve()
	{
		int ret = 0;
		for (int i = 0, j = 0; i < n; ++i, ++j)
		{
			while (j != -1 && str[i] != pat[j]) j = next[j];
			if (j == m - 1) ++ret;
		}
		return ret;
	}
}

using namespace KMP;

int main()
{
	scanf("%s%s", str, pat);
	n = strlen(str), m = strlen(pat);
	GetNext();
	printf("%d\n", Solve());
	return 0;
}

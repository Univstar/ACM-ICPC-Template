#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

namespace IO
{
	const int MAXL = 1 << 15;
	char buf[MAXL], *S, *T, ch;

	inline char Getch()
	{
		if (S == T) T = (S = buf) + fread(buf, 1, MAXL, stdin);
		return S == T ? EOF : *S++;
	}

	inline void Read(int &x)
	{
		x = 0;
		while (!isdigit(ch = Getch()));
		do { x = x * 10 + (ch ^ '0'); } while (isdigit(ch = Getch()));
	}
}

const int inf = ~0U >> 1;

namespace Dinic
{
	const int MAXN = 1000010, MAXM = 8000010;

	int n, m, st, ed;
	struct Edge { int adj, flow, next; } e[MAXM];
	int tot, head[MAXN], cur[MAXN], dist[MAXN], que[MAXN];

	inline void AddEdge(int u, int v, int f)
	{
		e[tot].adj = v, e[tot].flow = f, e[tot].next = head[u];
		head[u] = tot++;
		e[tot].adj = u, e[tot].flow = 0, e[tot].next = head[v];
		head[v] = tot++;
	}

	inline bool BFS()
	{
		memset(dist, -1, sizeof(dist));
		int begin = 0, end = 0;
		que[end++] = st, dist[st] = 0;
		while (begin != end)
		{
			int u = que[begin++];
			for (int i = head[u]; ~i; i = e[i].next)
			{
				int v = e[i].adj;
				if (e[i].flow && !~dist[v])
				{
					dist[v] = dist[u] + 1;
					if (v == ed) return true;
					que[end++] = v;
				}
			}
		}
		return ~dist[ed];
	}

	int DFS(int u, int uMin)
	{
		if (!uMin || u == ed) return uMin;
		int flow = 0;
		for (int &i = cur[u]; ~i; i = e[i].next)
		{
			int v = e[i].adj, delta;
			if (dist[v] == dist[u] + 1 && (delta = DFS(v, min(uMin, e[i].flow))))
			{
				e[i].flow -= delta, e[i ^ 1].flow += delta;
				uMin -= delta, flow += delta;
				if (!uMin) break;
			}
		}
		return flow;
	}

	inline LL Solve()
	{
		LL maxFlow = 0;
		while (BFS())
		{
			memcpy(cur, head, sizeof(cur));
			maxFlow += DFS(st, inf);
		}
		return maxFlow;
	}
}

using namespace Dinic;

inline void Init()
{
	memset(head, -1, sizeof(head)), tot = 0;
	IO::Read(n), IO::Read(m), IO::Read(st), IO::Read(ed);
	for (int i = 0; i < m; ++i)
	{
		int u, v, f;
		IO::Read(u), IO::Read(v), IO::Read(f);
		AddEdge(u, v, f);
	}
}

int main()
{
	Init();
	printf("%lld\n", Solve());
	return 0;
}

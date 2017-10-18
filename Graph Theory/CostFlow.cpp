#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

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

namespace CostFlow
{
	const int MAXN = 410, MAXM = 30010;

	struct Edge { int adj, flow, cost, next; } e[MAXM];
	int tot, head[MAXN], dist[MAXN];
	int n, m, st, ed, maxFlow, minCost;
	bool vis[MAXN];
	queue<int> que;

	inline void AddEdge(int u, int v, int f, int c)
	{
		e[tot].adj = v, e[tot].flow = f, e[tot].cost = c, e[tot].next = head[u];
		head[u] = tot++;
		e[tot].adj = u, e[tot].flow = 0, e[tot].cost = -c, e[tot].next = head[v];
		head[v] = tot++;
	}

	inline bool SPFA()
	{
		memset(dist, 0x3f, sizeof(dist));
		dist[ed] = 0, vis[ed] = true;
		que.push(ed);
		while (!que.empty())
		{
			int u = que.front();
			que.pop();
			vis[u] = false;
			for (int i = head[u]; ~i; i = e[i].next)
			{
				int v = e[i].adj;
				if (e[i ^ 1].flow && dist[v] > dist[u] - e[i].cost)
				{
					dist[v] = dist[u] - e[i].cost;
					if (!vis[v])
					{
						vis[v] = true;
						que.push(v);
					}
				}
			}
		}
		return dist[st] < 0x3f3f3f3f;
	}

	int DFS(int u, int uMin)
	{
		if (!uMin || u == ed) return uMin;
		if (vis[u]) return 0;
		vis[u] = true;
		int flow = 0;
		for (int i = head[u]; ~i; i = e[i].next)
		{
			int v = e[i].adj, delta;
			if (dist[v] == dist[u] - e[i].cost && (delta = DFS(v, min(uMin, e[i].flow))))
			{
				e[i].flow -= delta, e[i ^ 1].flow += delta;
				uMin -= delta, flow += delta;
				if (!uMin) break;
			}
		}
		vis[u] = false;
		return flow;
	}

	void Solve()
	{
		while (SPFA())
		{
			int delta = DFS(st, inf);
			maxFlow += delta;
			minCost += delta * dist[st];
		}
	}
}

using namespace CostFlow;

inline void Init()
{
	memset(head, -1, sizeof(head));
	IO::Read(n), IO::Read(m);
	for (int i = 0; i < m; ++i)
	{
		int u, v, f, c;
		IO::Read(u), IO::Read(v), IO::Read(f), IO::Read(c);
		AddEdge(u, v, f, c);
	}
	st = 1, ed = n;
}

int main()
{
	Init();
	Solve();
	printf("%d %d\n", maxFlow, minCost);
	return 0;
}

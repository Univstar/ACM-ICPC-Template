#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
namespace IO
{
	const int MAXL=1<<15;
	char buf[MAXL],*S,*T,ch;
	inline char igetch()
	{
		if(S==T)T=(S=buf)+fread(buf,1,MAXL,stdin);
		return S==T?EOF:*S++;
	}
	inline void read(int &x)
	{
		x=0;
		while(!isdigit(ch=igetch()));
		do{x=x*10+(ch^'0');}while(isdigit(ch=igetch()));
	}
}
const int MAXS=1000010;
struct edge{int adj,next;};
int inp[MAXS];
namespace DAG
{
	edge e[MAXS];
	int n,tot,head[MAXS],opp[MAXS],deg[MAXS],que[MAXS],mark[MAXS];
	inline void add_edge(int u,int v)
	{
		tot++,deg[v]++;
		e[tot].adj=v,e[tot].next=head[u];
		head[u]=tot;
	}
	inline void solve()
	{
		int begin=0,end=0;
		for(int u=1;u<=n;u++)
			if(!deg[u])que[end++]=u;
		while(begin!=end)
		{
			int u=que[begin++];
			if(!mark[u])mark[u]=1,mark[opp[u]]=-1;
			for(int i=head[u];i;i=e[i].next)
			{
				int &v=e[i].adj;
				if(!--deg[v])que[end++]=v;
			}
		}
	}
}
namespace origin
{
	edge e[MAXS];
	int n,tot,head[MAXS],sta[MAXS],len,idx,DFN[MAXS],low[MAXS];
	bool vis[MAXS];
	void Tarjan(int u)
	{
		low[u]=DFN[u]=++idx;
		sta[len++]=u;
		vis[u]=true;
		for(int i=head[u];i;i=e[i].next)
		{
			int &v=e[i].adj;
			if(!DFN[v])
			{
				Tarjan(v);
				low[u]=min(low[u],low[v]);
			}
			else if(vis[v])low[u]=min(low[u],DFN[v]);
		}
		if(low[u]==DFN[u])
		{
			++DAG::n;
			while(true)
			{
				int v=sta[--len];
				inp[v]=DAG::n,vis[v]=false;
				if(u==v)break;
			}
		}
	}
	inline void add_edge(int u,int v)
	{
		u++,v++;
		tot++;
		e[tot].adj=v,e[tot].next=head[u];
		head[u]=tot;
	}
	inline void init()
	{
		int tn,tm;
		IO::read(tn),IO::read(tm);
		while(tn--)
		{
			int u,su,v,sv;
			IO::read(u),IO::read(su),IO::read(v),IO::read(sv);
			int t1=2*u-su-1,t2=2*v-sv-1;//Open is smaller.
			add_edge(t1^1,t2);
			add_edge(t2^1,t1);
		}
		n=tm<<1;
	}
	inline void solve()
	{
		for(int u=1;u<=n;u++)
			if(!DFN[u])Tarjan(u);
	}
}
inline bool build()
{
	for(int u=1;u<=origin::n;u+=2)
	{
		if(inp[u]==inp[u+1])return false;
		DAG::opp[inp[u]]=inp[u+1],DAG::opp[inp[u+1]]=inp[u];
	}
	for(int u=1;u<=origin::n;u++)
		for(int i=origin::head[u];i;i=origin::e[i].next)
		{
			int &v=origin::e[i].adj;
			if(inp[u]!=inp[v])DAG::add_edge(inp[v],inp[u]);
		}
	return true;
}
int main(void)
{
	origin::init();
	origin::solve();
	if(build())
	{
		DAG::solve();
		for(int u=1;u<=origin::n;u+=2)
			puts(DAG::mark[inp[u]]==1?"1":"0");
	}
	else puts("IMPOSSIBLE");
	return 0;
}

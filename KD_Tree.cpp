#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN=100100,k=2,inf=~0u>>1;
inline LL sq(int x){return (LL)x*x;}
int n,idx;
struct node
{
	node *ch[2];
	int id,x[k],lower[k],upper[k];
	bool operator<(const node &o)const{return x[idx]<o.x[idx];}
	void update()
	{
		for(int i=0;i<k;i++)
		{
			lower[i]=min(x[i],min(ch[0]->lower[i],ch[1]->lower[i]));
			upper[i]=max(x[i],max(ch[0]->upper[i],ch[1]->upper[i]));
		}
	}
}pool[MAXN],*null,temp;
inline LL get_dist(node *a,node *b)
{
	LL ret=0;
	for(int i=0;i<k;i++)ret+=sq(a->x[i]-b->x[i]);
	return ret;
}
namespace KDTree
{
	node *sta[25],*root;
	int len;
	LL dist[25];
	inline LL eva(node *u,node *v)
	{
		LL ret=0;
		for(int i=0;i<k;i++)ret+=max(sq(v->x[i]-u->lower[i]),sq(v->x[i]-u->upper[i]));
		return ret;
	}
	void build(node *&u,int l,int r,int dep)
	{
		idx=dep%k;
		if(l>r){u=null;return;}
		int mid=l+r>>1;
		nth_element(pool+l,pool+mid,pool+r+1);
		u=pool+mid;
		build(u->ch[0],l,mid-1,dep+1);
		build(u->ch[1],mid+1,r,dep+1);
		u->update();
	}
	void query(node *u,node *v,int dep,int m)
	{
		if(u==null)return;
		idx=dep%k;
		LL r=get_dist(u,v),dl=(u->ch[0]!=null?eva(u->ch[0],v):-1),dr=(u->ch[1]!=null?eva(u->ch[1],v):0);
		int p=len-1;
		while(p>=0&&(r>dist[p]||(r==dist[p]&&sta[p]->id>u->id)))dist[p+1]=dist[p],sta[p+1]=sta[p],p--;
		p++;
		dist[p]=r,sta[p]=u;
		if(len<m)len++;
		if(dl>dr)
		{
			if(len<m||dl>=dist[len-1])query(u->ch[0],v,dep+1,m);
			if(len<m||dr>=dist[len-1])query(u->ch[1],v,dep+1,m);
		}
		else
		{
			if(len<m||dr>=dist[len-1])query(u->ch[1],v,dep+1,m);
			if(len<m||dl>=dist[len-1])query(u->ch[0],v,dep+1,m);
		}
	}
	inline void query(node *v,int m)
	{
		len=0;
		query(root,v,0,m);
	}
}
int main(void)
{
	null=pool;
	null->ch[0]=null->ch[1]=null;
	for(int i=0;i<2;i++)null->lower[i]=inf,null->upper[i]=-inf;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&pool[i].x[0],&pool[i].x[1]),pool[i].id=i;
	KDTree::build(KDTree::root,1,n,0);
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int m;
		scanf("%d%d%d",&temp.x[0],&temp.x[1],&m);
		KDTree::query(&temp,m);
		printf("%d\n",KDTree::sta[m-1]->id);
	}
	return 0;
}

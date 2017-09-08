#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN=1000010;
struct node
{
	int key,dist;
	node *ch[2];
}tree[MAXN],*null;
struct statu
{
	node *root;
	int cnt,sum;
	statu(){}
	statu(node *_root,int _cnt,int _sum):root(_root),cnt(_cnt),sum(_sum){}
}sta[MAXN];
int n,o,tot,a[MAXN],b[MAXN];
inline node *add_node(int key)
{
	tot++;
	tree[tot].key=key;
	tree[tot].ch[0]=tree[tot].ch[1]=null;
	return &tree[tot];
}
node *merge(node *u,node *v)
{
	if(u==null)return v;
	if(v==null)return u;
	if(u->key<v->key)swap(u,v);
	u->ch[1]=merge(u->ch[1],v);
	if(u->ch[0]->dist<u->ch[1]->dist)swap(u->ch[0],u->ch[1]);
	u->dist=u->ch[1]->dist+1;
	return u;
}
int main(void)
{
	null=&tree[tot];
	null->dist=-1;
	null->ch[0]=null->ch[1]=null;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]-=i;
		sta[o++]=statu(add_node(a[i]),1,1);
		while(o>1&&sta[o-1].root->key<sta[o-2].root->key)
		{
			sta[o-2].root=merge(sta[o-2].root,sta[o-1].root);
			sta[o-2].cnt+=sta[o-1].cnt,sta[o-2].sum+=sta[o-1].sum;
			while(sta[o-2].sum>(sta[o-2].cnt+1>>1))sta[o-2].root=merge(sta[o-2].root->ch[0],sta[o-2].root->ch[1]),sta[o-2].sum--;
			o--;
		}
	}
	LL ans=0;
	for(int i=0,j=1;i<o;i++)
	{
		fill(b+j,b+j+sta[i].cnt,sta[i].root->key);
		j+=sta[i].cnt;
	}
	for(int i=1;i<=n;i++)
	{
		LL temp=(LL)a[i]-b[i];
		if(temp<0)temp=-temp;
		ans+=temp;
	}
	cout<<ans<<endl;
	return 0;
}

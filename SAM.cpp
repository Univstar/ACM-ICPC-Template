#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN=300005;
struct edge{int adj,next;}e[MAXN<<1];
struct node
{
	node *pre,*ch[26];
	int step;
	LL size;
}pool[MAXN<<1],*cur=pool,*root;
int n,q,tot,head[MAXN<<1];
char str[MAXN],alpha[30];
inline void add_edge(int u,int v)
{
	tot++;
	e[tot].adj=v,e[tot].next=head[u];
	head[u]=tot;
}
inline node *extend(int k,node *last)
{
	if(last->ch[k]&&last->step+1==last->ch[k]->step+1)return last->ch[k];
	node *p=last,*u=cur++;
	u->step=p->step+1;
	for(;p&&!p->ch[k];p=p->pre)p->ch[k]=u;
	if(!p)u->pre=root;
	else
	{
		node *q=p->ch[k];
		if(p->step+1==q->step)u->pre=q;
		else
		{
			node *v=cur++;
			*v=*q;
			v->step=p->step+1;
			q->pre=u->pre=v;
			for(;p&&p->ch[k]==q;p=p->pre)p->ch[k]=v;
		}
	}
	return u;
}
void build(int u,node *last,int fa)
{
	last=extend(str[u]-'a',last);
	for(int i=head[u];i;i=e[i].next)
	{
		int &v=e[i].adj;
		if(v==fa)continue;
		build(v,last,u);
	}
}
void prepare(node *u)
{
	u->size=1;
	for(int i=0;i<26;i++)
	{
		if(!u->ch[i])continue;
		if(!u->ch[i]->size)prepare(u->ch[i]);
		u->size+=u->ch[i]->size;
	}
}
inline void init()
{
	scanf("%d%d%s",&n,&q,str+1);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v),add_edge(v,u);
	}
	root=cur++;
	build(1,root,0);
}
inline void query(LL k)
{
	node *u=root;
	k--;
	while(k)
	{
		for(int i=0;i<26;i++)
		{
			int j=alpha[i]-'a';
			if(!u->ch[j])continue;
			if(k>u->ch[j]->size)k-=u->ch[j]->size;
			else
			{
				u=u->ch[j];
				putchar(j+'a');
				k--;
				break;
			}
		}
	}
	puts("");
}
int main(void)
{
	init();
	prepare(root);
	printf("%lld\n",root->size);
	while(q--)
	{
		LL k;
		scanf("%s%lld",alpha,&k);
		if(k<=root->size)query(k);
		else puts("-1");
	}
	return 0;
}

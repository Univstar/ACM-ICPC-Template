#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=502,MAXL=50010,MAXS=500010;
struct node
{
	node *ch[63],*fail;
	int cnt;
}pool[MAXS],*cur=pool,*root,*inp[MAXN],*que[MAXS];
char str[MAXL];
int n,m,begin,end;
inline int id(char ch)
{
	if(isdigit(ch))return ch-'0';
	else if(islower(ch))return ch-'a'+10;
	else if(isupper(ch))return ch-'A'+36;
	else return 62;
}
inline void init()
{
	scanf("%d",&n);
	root=cur++;
	for(int i=0;i<n;i++)
	{
		scanf("%s",str);
		node *u=root;
		for(char *j=str;*j;j++)
		{
			int k=id(*j);
			if(!u->ch[k])u->ch[k]=cur++;
			u=u->ch[k];
		}
		inp[i]=u;
	}
}
inline void get_fail()
{
	que[end++]=root;
	while(begin!=end)
	{
		node *u=que[begin++];
		for(int i=0;i<63;i++)
			if(u->ch[i])
			{
				if(u==root)u->ch[i]->fail=u;
				else
				{
					node *p=u->fail;
					for(;p;p=p->fail)
						if(p->ch[i]){u->ch[i]->fail=p->ch[i];break;}
					if(!p)u->ch[i]->fail=root;
				}
				que[end++]=u->ch[i];
			}
	}
}
inline void solve()
{
	scanf("%d",&m);
	while(m--)
	{
		scanf("%s",str);
		node *u=root;
		for(char *i=str;*i;i++)
		{
			int k=id(*i);
			while(u&&!u->ch[k])u=u->fail;
			if(u)u=u->ch[k];
			else u=root;
			u->cnt++;
		}
	}
	for(int i=end-1;i;i--)que[i]->fail->cnt+=que[i]->cnt;
	for(int i=0;i<n;i++)printf("%d\n",inp[i]->cnt);
}
int main(void)
{
	init();
	get_fail();
	solve();
	return 0;
}

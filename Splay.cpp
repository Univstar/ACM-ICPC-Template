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
const int MAXN=100010;
struct node
{
	node *ch[2];
	int val,size,rev;
	int cmp(int k)
	{
		if(k==ch[0]->size)return -1;
		else return k>ch[0]->size;
	}
	void flip();
	void update(){size=ch[0]->size+ch[1]->size+1;}
	void download()
	{
		if(rev)
		{
			ch[0]->flip(),ch[1]->flip();
			rev^=1;
		}
	}
}pool[MAXN],*cur=pool,*root,*null;
void node::flip()
{
	if(this==null)return;
	swap(ch[0],ch[1]);
	rev^=1;
}
inline node *add_node(int val)
{
	cur->val=val,cur->size=1;
	cur->ch[0]=cur->ch[1]=null;
	return cur++;
}
inline void rotate(node *&u,int d)
{
	node *t=u->ch[d^1];
	u->ch[d^1]=t->ch[d],t->ch[d]=u;
	u->update(),t->update();
	u=t;
}
void splay(node *&u,int k)
{
	u->download();
	int d=u->cmp(k);
	if(d==1)k-=u->ch[0]->size+1;
	if(~d)
	{
		node *&t=u->ch[d];
		t->download();
		int d2=t->cmp(k);
		if(d2==1)k-=t->ch[0]->size+1;
		if(~d2)
		{
			splay(t->ch[d2],k);
			if(d==d2)rotate(u,d^1);
			else rotate(u->ch[d],d);
		}
		rotate(u,d^1);
	}
}
inline void split(node *u,node *&left,node *&right,int k)
{
	if(k<0){left=null,right=u;return;}
	splay(u,k);
	left=u,right=u->ch[1];
	u->ch[1]=null;
	u->update();
}
inline node *merge(node *left,node *right)
{
	if(left==null)return right;
	if(right==null)return left;
	splay(left,left->size-1);
	left->ch[1]=right;
	left->update();
	return left;
}
void build(node *&u,int l,int r)
{
	int mid=l+r>>1;
	u=add_node(mid);
	if(l<mid)build(u->ch[0],l,mid-1);
	if(r>mid)build(u->ch[1],mid+1,r);
	u->update();
}
void output(node *u)
{
	if(u==null)return;
	u->download();
	output(u->ch[0]);
	printf("%d ",u->val);
	output(u->ch[1]);
}
int n,m;
int main(void)
{
	null=cur++;
	null->ch[0]=null->ch[1]=null;
	IO::read(n),IO::read(m);
	build(root,1,n);
	while(m--)
	{
		int a,b,c;
		IO::read(a),IO::read(b),IO::read(c);
		node *A,*B,*C,*rest;
		split(root,A,rest,a-1);
		split(rest,B,rest,b-1);
		rest=merge(A,rest);
		split(rest,C,rest,c-1);
		B->flip();
		root=merge(merge(C,B),rest);
	}
	output(root);
	printf("\n");
	return 0;
}

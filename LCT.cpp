namespace LCT
{
	struct node
	{
		node *ch[2],*fa,*lower;
		int val,rev;
		void flip();
		void init(int);
		void download()
		{
			if(rev)
			{
				ch[0]->flip(),ch[1]->flip();
				rev^=1;
			}
		}
		node *imin(node *a,node *b){return a->val<b->val?a:b;}
		void update(){lower=imin(imin(ch[0]->lower,ch[1]->lower),this);}
	}pool[MAXN<<1],*null,*anc[MAXN<<1];
	void node::flip()
	{
		if(this==null)return;
		rev^=1;
		swap(ch[0],ch[1]);
	}
	void node::init(int k)
	{
		rev=0,val=k;
		lower=this,lower->fa=null;
		ch[0]=ch[1]=null;
	}
	inline void rotate(node *&u,int d)
	{
		node *t=u->ch[d^1];
		u->ch[d^1]=t->ch[d],t->ch[d]=u;
		t->fa=u->fa,u->fa=t,u->ch[d^1]->fa=u;
		u->update(),t->update();
		u=t;
	}
	void splay(node *&u,int k)
	{
		u->download();
		int d=(k?(u->ch[1]==anc[k-1]):-1);
		if(~d)
		{
			k--;
			node *&t=u->ch[d];
			t->download();
			int d2=(k?(t->ch[1]==anc[k-1]):-1);
			if(~d2)
			{
				k--;
				splay(t->ch[d2],k);
				if(d==d2)rotate(u,d^1);
				else rotate(u->ch[d],d);
			}
			rotate(u,d^1);
		}
	}
	inline bool isroot(node *u){return u->fa->ch[0]!=u&&u->fa->ch[1]!=u;}
	inline void splay(node *u)
	{
		int cnt=0;
		for(;!isroot(u);u=u->fa)anc[cnt++]=u;
		splay(u,cnt);
	}
	inline void access(node *u)
	{
		for(node *v=null;u!=null;v=u,u=u->fa)
		{
			splay(u);
			u->ch[1]=v;
			u->update();
		}
	}
	inline void make_root(node *u)
	{
		access(u);
		splay(u);
		u->flip();
	}
	inline node *get_fa(node *u)
	{
		access(u);
		splay(u);
		while(u->ch[0]!=null)u=u->ch[0];
		return u;
	}
	inline void link(node *u,node *v)
	{
		make_root(u);
		u->fa=v;
	}
	inline void cut(node *u,node *v)
	{
		make_root(u);
		access(v);
		splay(v);
		u->fa=v->ch[0]=null;
		v->update();
	}
	inline node *query(node *u,node *v)
	{
		make_root(u);
		access(v);
		splay(v);
		return v->lower;
	}
}

struct Treap_node
{
	Treap_node *ch[2];
	int key,fix;
	int cmp(int _key)
	{
		if(_key==key)return -1;
		else return _key>key;
	}
}pool[MAXN+MAXQ],*cur=pool,*null;
struct Treap
{
	Treap_node *root;
	Treap_node *add_node(int key)
	{
		cur->ch[0]=cur->ch[1]=null;
		cur->key=key,cur->fix=rand();
		return cur++;
	}
	void rotate(Treap_node *&u,int d)
	{
		Treap_node *t=u->ch[d^1];
		u->ch[d^1]=t->ch[d],t->ch[d]=u;
		u=t;
	}
	void insert(Treap_node *&u,int key)
	{
		if(u==null){u=add_node(key);return;}
		int d=u->cmp(key);
		insert(u->ch[d],key);
		if(u->ch[d]->fix>u->fix)rotate(u,d^1);
	}
	void remove(Treap_node *&u,int key)
	{
		int d=u->cmp(key);
		if(d==-1)
		{
			d=u->ch[1]->fix>u->ch[0]->fix;
			if(u->ch[d]==null){u=null;return;}
			rotate(u,d^1);
			remove(u->ch[d^1],key);
		}
		else remove(u->ch[d],key);
	}
	int get_pre(Treap_node *u,int key)
	{
		if(u==null)return -inf;
		int d=u->cmp(key);
		if(d==1)return max(get_pre(u->ch[1],key),u->key);
		else return get_pre(u->ch[0],key);
	}
	int get_next(Treap_node *u,int key)
	{
		if(u==null)return inf;
		int d=u->cmp(key);
		if(d==0)return min(get_next(u->ch[0],key),u->key);
		else return get_next(u->ch[1],key);
	}
}num[MAXN+MAXQ];

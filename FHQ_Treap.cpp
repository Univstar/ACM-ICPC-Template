struct node
{
	node *ch[2];
	int key,size;
	int cmp(int _key)
	{
		if(key==_key)return -1;
		else return segm[key].calc(x0)<segm[_key].calc(x0);
	}
}pool[MAXS],*null,*cur=pool,*root[MAXN];
typedef pair<Point,int> ppi;
typedef pair<int,int> pii;
typedef pair<node*,node*> pnn;
typedef pair<Point,pii> ppp;
inline node *add_node(int key,node *lc=null,node *rc=null)
{
	cur->key=key,cur->ch[0]=lc,cur->ch[1]=rc;
	cur->size=lc->size+rc->size+1;
	return cur++;
}
inline node *copy_node(node *u)
{
	if(u==null)return u;
	else return add_node(u->key,u->ch[0],u->ch[1]);
}
node *merge(node *u,node *v)
{
	if(u==null)return copy_node(v);
	else if(v==null)return copy_node(u);
	if(irand()%(u->size+v->size)<=u->size)return add_node(u->key,u->ch[0],merge(u->ch[1],v));
	else return add_node(v->key,merge(u,v->ch[0]),v->ch[1]);
}
pnn split(node *u,int k)//The left will be in the size of k.
{
	if(u==null)return pnn(null,null);
	if(!k)return pnn(null,copy_node(u));
	int r=u->ch[0]->size;
	if(r>=k)
	{
		pnn temp=split(u->ch[0],k);
		return pnn(temp.first,add_node(u->key,temp.second,u->ch[1]));
	}
	else
	{
		pnn temp=split(u->ch[1],k-r-1);
		return pnn(add_node(u->key,u->ch[0],temp.first),temp.second);
	}
}
int get_rank(node *u,int key)//indexed from 0
{
	int ret=0;
	while(u!=null)
	{
		int d=u->cmp(key);
		if(!~d){ret+=u->ch[0]->size;break;}
		if(d)ret+=u->ch[0]->size+1;
		u=u->ch[d];
	}
	return ret;
}
void debug(node *u)
{
	if(u==null)return;
	cout<<"#### "<<u->key<<' '<<u->size<<endl;
	if(u->ch[0]!=null)cout<<" Left Child: "<<u->ch[0]->key<<endl;
	if(u->ch[1]!=null)cout<<"right Child: "<<u->ch[1]->key<<endl;
	debug(u->ch[0]);
	debug(u->ch[1]);
}
node *insert(node *u,int key)
{
	pnn temp=split(u,get_rank(u,key));
	return merge(merge(temp.first,add_node(key)),temp.second);
}
node *remove(node *u,int key)
{
	pnn temp1=split(u,get_rank(u,key));
	pnn temp2=split(temp1.second,1);
	return merge(temp1.first,temp2.second);
}
inline int query(node *u,int x,int y)
{
	int k=0;
	node *v=null;
	while(u!=null)
	{
		if(segm[u->key].calc(x)<=y)
		{
			v=u;
			k+=u->ch[0]->size+1;
			u=u->ch[1];
		}
		else u=u->ch[0];
	}
	if(v==null)return -1;
	if(fabs(segm[v->key].calc(x)-y)<1e-6||k%2)return segm[v->key].id;
	else return -1;
}

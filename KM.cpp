namespace KM
{
	int n,m,g[MAXN][MAXN],slack[MAXN],ls[MAXN],lt[MAXN],mat[MAXN],rev[MAXN];
	bool vis[MAXN],vit[MAXN];
	bool augm(int u)
	{
		vis[u]=true;
		for(int v=1;v<=m;v++)
		{
			if(vit[v])continue;
			int d=g[u][v]-ls[u]-lt[v];
			if(d==0)
			{
				vit[v]=true;
				if(!mat[v]||augm(mat[v])){mat[v]=u;return true;}
			}
			else slack[v]=min(slack[v],d);
		}
		return false;
	}
	inline void solve(int _n,int _m,int &ret,vector<int> &op)
	{
		n=_n,m=_m;
		fill(mat+1,mat+m+1,0);
		fill(ls+1,ls+n+1,inf);
		fill(lt+1,lt+m+1,0);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				ls[i]=min(ls[i],g[i][j]);
		for(int i=1;i<=n;i++)
		{
			fill(slack+1,slack+m+1,inf);
			while(true)
			{
				fill(vis+1,vis+n+1,false);
				fill(vit+1,vit+m+1,false);
				if(augm(i))break;
				int d=inf;
				for(int j=1;j<=m;j++)
					if(!vit[j])d=min(d,slack[j]);
				for(int j=1;j<=n;j++)
					if(vis[j])ls[j]+=d;
				for(int j=1;j<=m;j++)
				{
					if(vit[j])lt[j]-=d;
					else slack[j]-=d;
				}
			}
		}
		ret=0,op.clear();
		for(int i=1;i<=m;i++)
			if(mat[i])rev[mat[i]]=i;
		for(int i=1;i<=n;i++)
		{
			ret+=g[i][rev[i]];
			op.push_back(rev[i]);
		}
	}
}

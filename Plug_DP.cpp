#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=110,MAXM=10,inf=1000000000,MAXS=10000,mod=1007;
struct ihash
{
	int tot,head[mod],val[MAXS],statu[MAXS],next[MAXS];
	void clear(){tot=0;fill(head,head+mod,0);}
	void insert(int u,int v)
	{
		for(int i=head[u%mod];i;i=next[i])
			if(statu[i]==u){val[i]=max(val[i],v);return;}
		tot++;
		statu[tot]=u,val[tot]=v,next[tot]=head[u%mod];
		head[u%mod]=tot;
	}
}iha[2];
int n,m,w[MAXN][MAXM];
inline int pos(int u,int x){return u>>(x<<1)&3;}
inline void trans(int &u,int x,int y)
{
	u&=~(3<<(x<<1));
	u|=y<<(x<<1);
}
inline int get_1(int u,int x)
{
	int cnt=0;
	for(int i=x;i>=0;i--)
	{
		if(pos(u,i)==2)cnt++;
		else if(pos(u,i)==1)cnt--;
		if(!cnt)return i;
	}
	return -1;
}
inline int get_2(int u,int x)
{
	int cnt=0;
	for(int i=x;i<=m;i++)
	{
		if(pos(u,i)==1)cnt++;
		else if(pos(u,i)==2)cnt--;
		if(!cnt)return i;
	}
	return -1;
}
inline int DP()
{
	int cur=0,ans=-inf;
	iha[cur].insert(0,0);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++,cur^=1)
		{
			iha[cur^1].clear();
			for(int k=1;k<=iha[cur].tot;k++)
			{
				int u=iha[cur].statu[k],f=iha[cur].val[k]+w[i][j];
				int lpl=pos(u,j-1),upl=pos(u,j);
				if(lpl&&upl)
				{
					if(lpl==1&&upl==1)
					{
						int upl2=get_2(u,j);
						trans(u,j-1,0),trans(u,j,0),trans(u,upl2,1);
						iha[cur^1].insert(u,f);
					}
					else if(lpl==2&&upl==1)
					{
						trans(u,j-1,0),trans(u,j,0);
						iha[cur^1].insert(u,f);
					}
					else if(lpl==2&&upl==2)
					{
						int lpl1=get_1(u,j-1);
						trans(u,j-1,0),trans(u,j,0),trans(u,lpl1,2);
						iha[cur^1].insert(u,f);
					}
					else
					{
						trans(u,j-1,0),trans(u,j,0);
						if(!u)ans=max(ans,f);
					}
				}
				else if(lpl)
				{
					if(i<n)iha[cur^1].insert(u,f);
					if(j<m)
					{
						trans(u,j-1,0),trans(u,j,lpl);
						iha[cur^1].insert(u,f);
					}
				}
				else if(upl)
				{
					if(j<m)iha[cur^1].insert(u,f);
					if(i<n)
					{
						trans(u,j-1,upl),trans(u,j,0);
						iha[cur^1].insert(u,f);
					}
				}
				else
				{
					iha[cur^1].insert(u,f-w[i][j]);
					if(i<n&&j<m)
					{
						trans(u,j-1,1),trans(u,j,2);
						iha[cur^1].insert(u,f);
					}
				}
			}
		}
		for(int j=1;j<=iha[cur].tot;j++)iha[cur].statu[j]<<=2;
	}
	return ans;
}
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&w[i][j]);
	printf("%d\n",DP());
	return 0;
}

int ex_gcd(int a,int b,LL &x,LL &y)
{
	if(b==0){x=1,y=0;return a;}
	int r=ex_gcd(b,a%b,x,y);
	LL t=x;
	x=y;
	y=t-a/b*y;
	return r;
}
inline int get_inv(int a)
{
	LL x,y;
	ex_gcd(a,p,x,y);
	return (x%p+p)%p;
}
inline int get_log(int a,int q)
{
	int m=(int)ceil(sqrt(p)),e=1;
	int v=get_inv(quick_pow(a,m));
	map<int,int> f;
	f[1]=0;
	for(int i=1;i<m;i++)
	{
		e=(LL)e*a%p;
		if(!f.count(e))f[e]=i;
	}
	for(int i=0;i<m;i++)
	{
		if(f.count(q))return i*m+f[q]+1;
		q=(LL)q*v%p;
	}
	return -1;
}

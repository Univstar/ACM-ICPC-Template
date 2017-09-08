#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXL=300000;
const double PI=acos(-1.0);
struct complex
{
	double real,imag;
	complex(double _real=0,double _imag=0):real(_real),imag(_imag){}
	complex operator+(complex o){return complex(real+o.real,imag+o.imag);}
	complex operator-(complex o){return complex(real-o.real,imag-o.imag);}
	complex operator*(complex o){return complex(real*o.real-imag*o.imag,real*o.imag+imag*o.real);}
}a[MAXL];
inline void rever(complex num[],int len)
{
	for(int i=1,j=len>>1;i<len-1;i++)
	{
		if(i<j)swap(num[i],num[j]);
		int k=len>>1;
		while(j>=k)j-=k,k>>=1;
		j+=k;
	}
}
inline void FFT(complex num[],int len,int flag)
{
	rever(num,len);
	for(int i=2;i<=len;i<<=1)
	{
		complex w0(cos(-flag*2*PI/i),sin(-flag*2*PI/i));
		for(int j=0;j<len;j+=i)
		{
			complex w(1,0);
			for(int k=j;k<j+i/2;k++)
			{
				complex u=num[k],t=w*num[k+i/2];
				num[k]=u+t,num[k+i/2]=u-t;
				w=w*w0;
			}
		}
	}
	if(flag==-1)
		for(int i=0;i<len;i++)
			num[i]=complex(num[i].real/len,num[i].imag);
}
int n,sum[MAXL];
char str1[MAXL],str2[MAXL];
int main(void)
{
	scanf("%d%s%s",&n,str1,str2);
	int len=1;
	while(len<n*2)len<<=1;
	for(int i=0;i<n;i++)a[i]=complex((str1[n-i-1]-'0')+(str2[n-i-1]-'0'),(str1[n-i-1]-'0')-(str2[n-i-1]-'0'));
//	for(int i=0;i<n;i++)b[i]=complex(str2[n-i-1]-'0',0);
	FFT(a,len,1);
	for(int i=0;i<len;i++)a[i]=a[i]*a[i];
	FFT(a,len,-1);
	for(int i=0;i<len;i++)sum[i]=(int)round(a[i].real*0.25);
	for(int i=0;i<len;i++)sum[i+1]+=sum[i]/10,sum[i]%=10;
	len=len*2-1;
	while(len&&!sum[len])len--;
	for(int i=len;i>=0;i--)putchar(sum[i]+'0');
	puts("");
	return 0;
}

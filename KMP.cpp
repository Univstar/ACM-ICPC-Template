n=strlen(str);
next[0]=-1;
int i=0,j=-1;
while(i<n)
{
	if(j==-1||str[i]==str[j])
	{
		if(str[++i]!=str[++j])next[i]=j;
		else next[i]=next[j];
	}
	else j=next[j];
}

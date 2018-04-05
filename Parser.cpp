#include <bits/stdc++.h>

using namespace std;

char string1[100];
int len,indx;

int expr();
int expr2();
int term();
int term2();
int factor();


int expr()
{
	if(term())
	{
		if(expr2())
		{
			printf("Inside expr\n");
			return 1;
		}
			
		else
			return 0;
	}
	else
	{
		return 0;
	}
}

int expr2()
{
	if(string1[indx]=='+')
	{
		indx++;
		if(term())
		{
			if(expr2())
			{
				printf("Inside expr2\n");
				return 1;
			}	
			else
				return 0;
		}
		else
			return 0;
	}
	else if(string1[indx]=='-')
	{
		indx++;
		if(term())
		{
			if(expr2())
			{
				printf("Inside expr2\n");
				return 1;
			}
			else
				return 0;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		printf("Inside expr2 Ephsilon\n");
		return 1;
	}

}

int term()
{
	if(factor())
	{
		if(term2())
		{
			printf("Inside term\n");
			return 1;
		}
		else
			return 0;
	}
	else 
	{
		return 0;
	}
}

int term2()
{
	if(string1[indx] == '*')
	{
		if(factor())
		{
			if(term2())
			{
				printf("Inside term2\n");
				return 1;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else if(string1[indx] == '/')
	{
		if(factor())
		{
			if(term2())
			{
				printf("Inside term2\n");
				return 1;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else
	{
		printf("Inside term2 Ephsilon\n");
		return 1;
	}
}

int factor()
{
	if(string1[indx]== '(')
	{
		indx++;
		if(expr() && string1[indx]==')')
			{
				printf("Inside factor\n");
				indx++;
				return 1;
			}
		else
			{
				printf("expecting )\n");
				return 0;
			}
	}
	
	if(string1[indx]>=48 && string1[indx]<=57)
	{
		indx++;
		printf("Inside factor\n");
		return 1;
	}	
	if(string1[indx]>=97 && string1[indx]<=122)
	{
		printf("Inside factor\n");
		indx++;
		return 1;
	}
}

int main(){
	scanf("%s",string1);
	int ans;
	ans = expr();
	if(ans==1)
		printf("Yes\n");
	else if(ans==0)
		printf("No\n");
}
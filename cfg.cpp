#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

char str[100],tok;
int tok_no=0;

int expr();
int expr2();
int term();
int term2();
int factor();

char nextToken()
{
	char c = str[tok_no];
	while(c==' ')
	{
		tok_no++;
		c=str[tok_no];
	}
	//printf("%c\n",c );
	tok_no++;
	return c;
}
int expr()
{
	//printf("IN expr\n");
	printf("****expr");
	char cur_tok= tok_no;
	//printf("now term\n");
	int k=term();
	if(k==2)
	{
		//printf("expr 2\n");
		
		if(expr2())
		{
			printf("****term expr2");
			//printf("true\n");
			return 1;
		}
		else
			return 0;
	}
	else if(k==1)
	{
		//printf("expr 1\n");
		int t= expr2();
		if(t!=0)
		{
			printf("****term expr2");
			return t;
		}
	}
	else
	{
		//printf("expr=%c\n",tok );
		//printf("false\n");
		//tok_no=cur_tok;
		return 0;
	}
}

int expr2()
{
	//printf("IN expr2\n");
	char cur_tok= tok_no;
	char prev_tok;
	//printf("In expr2=%c\n",tok );
	if(tok=='+' || tok=='-')
	{
		//printf("+- matched\n");
		prev_tok=tok;
		tok=nextToken();
		//tok=nextToken();
		//printf("+- matched %c\n",tok);
		//printf("now term in expr2\n");
		if(term())
		{
			int t=expr2();
			if(t!=0)
				printf("**** %c term expr2",prev_tok);
			return t;
		}	
	}
	else if(tok=='\n') 
	{
		//printf("invalid expr2=%c\n",tok);
		//tok_no=cur_tok;
		return 1;
	}
	else 
	{
		//printf("expr2=%c\n",tok );
		printf("****\n");
		//tok_no=cur_tok;
		return 1;
	}
}
int term()
{
	//printf("IN term\n");
	char cur_tok= tok_no;
	if(factor())
	{	
		int t =term2();
		if(t!=0)
		{
			printf("****factor term2");
		}
		return t;
	}
	else
	{
		//printf("term=%c\n",tok );
		//tok_no=cur_tok;
		return 0;
	}
}
int term2()
{
	//printf("IN term2\n");
	//printf("IN term2=%c\n",tok );
	///tok=nextToken();//////////
	char cur_tok= tok_no;
	char prev_tok;
	if(tok== '*' || tok=='\\' )
	{
		prev_tok=tok;
		tok= nextToken();
		if(factor())
		{
			int t=term2();
			if(t!=0)
			{
				printf("**** %c factor term2\n", prev_tok);
			}
			return t;
		}
		else
			return 0;
	}
	else if(tok=='+' || tok=='-')
	{

		//printf("term2=%c\n",tok ); 
		//tok_no=cur_tok;
		return 2;
	}
	else if(tok=='\n')
	{
		//printf("str end term2\n");
		return 1;
	}
	else
	{
		printf("****\n");
		return 1;
	}
}

int factor()
{
	//printf("IN factor %c j\n",tok);
	char cur_tok= tok_no;
	if(tok=='(')
	{
		//printf("bracket\n");
		tok= nextToken();
		printf("****(");
		if(expr())
		{
			/////////change
			
			if(tok==')')
			{
				printf(")");
				tok=nextToken();
				return 1;
			}
			else
			{
				//tok=nextToken();
				return 0;	
			}
		}
		else
		{
			//printf("syntax error\n");
			//printf("factor1=%c\n",tok );
			//tok_no=cur_tok;
			return 0;
		}
	}
	else if(tok >='0' && tok<='9') //check number
	{
		//printf("%c is a digit\n", tok );
		printf("****%c",tok );
		tok=nextToken();
		return 1;
	}
	else if(tok >='a' && tok<= 'z')
	{
		//printf("%c is a letter\n", tok );
		printf("****%c",tok );
		tok=nextToken();
		return 1;
	}
	else
	{
		//printf("factor2=%c\n",tok );
		//tok_no=cur_tok;
		return 0;
	}
}

main()
{
	fgets(str,100,stdin);
	//printf("start\n");
	tok = nextToken();
	if(expr())
	{
		//tok=nextToken();
		//printf("tok in main %d\n",tok);
		if (tok=='\n' || tok=='\0')
		{
			printf("\nYES\n");
		}	
		else
			printf("NO\n");
	}
	else
		printf("NO\n");
}
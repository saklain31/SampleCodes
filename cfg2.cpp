#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

char str[100],tok;
int tok_no=0;
std::stack<std::string> rules;

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
	tok_no++;
	return c;
}
int expr()
{
	char cur_tok= tok_no;
	int k=term();
	if(k==2)
	{
		if(expr2())
		{
			rules.push("expr-> term expr2");
			return 1;
		}
		else
			return 0;
	}
	else if(k==1)
	{
		int t= expr2();
		if(t!=0)
		{
			rules.push("expr-> term expr2");
			return t;
		}
	}
	else
	{
		return 0;
	}
}

int expr2()
{
	char cur_tok= tok_no;
	char prev_tok;
	if(tok=='+' || tok=='-')
	{
		prev_tok=tok;
		tok=nextToken();
		if(term())
		{
			int t=expr2();
			if(t!=0)
			{
				if(prev_tok=='+')
					rules.push("expr2-> + term expr2");
				else if(prev_tok=='-')
					rules.push("expr2-> - term expr2");
			}
			return t;
		}	
	}
	else if(tok=='\n' || tok=='\0') 
	{
		rules.push("expr2-> epsilon");
		return 1;
	}
	else 
	{
		rules.push("expr2-> epsilon");
		return 1;
	}
}
int term()
{
	char cur_tok= tok_no;
	if(factor())
	{	
		int t =term2();
		if(t!=0)
		{
			rules.push("term-> factor term2");
			//printf("term= %c %d \n",tok,tok);
		}
		return t;
	}
	else
	{
		return 0;
	}
}
int term2()
{
	char cur_tok= tok_no;
	char prev_tok;
	//printf("tok=%c %d\n",tok,tok);
	if((tok>='0' && tok<='9') || (tok>='a' && tok<='z'))
		printf("Operator missing\n");
	if(tok== '*' || tok=='\\' )
	{
		prev_tok=tok;
		tok= nextToken();
		if(factor())
		{
			int t=term2();
			if(t!=0)
			{
				if(prev_tok=='*')
					rules.push("term2-> * factor term2");
				else if(prev_tok=='\\')
					rules.push("term2-> \\ factor term2");
			}
			return t;
		}
		else
		{	
			return 0;
		}
	}
	else if(tok=='+' || tok=='-')
	{

		rules.push("term2-> epsilon");
		return 2;
	}
	else if(tok=='\n' || tok=='\0')
	{
		rules.push("term2-> epsilon");
		return 1;
	}
	else
	{
		rules.push("term2-> epsilon");
		return 1;
	}
}

int factor()
{
	char cur_tok= tok_no;
	if(tok=='(')
	{
		tok= nextToken();
		if(expr())
		{
			if(tok==')')
			{
				rules.push("factor-> (expr)");
				tok=nextToken();
				return 1;
			}
			else
			{
				printf("Matching ) missing\n");
				return 0;	
			}
		}
		else
		{
			printf("Parentheses ( doesn't match\n");
			return 0;
		}
	}
	else if(tok >='0' && tok<='9') //check number
	{
		rules.push("factor-> number");
		tok=nextToken();
		return 1;
	}
	else if(tok >='a' && tok<= 'z')
	{
		rules.push("factor-> identifier");	
		tok=nextToken();
		return 1;
	}
	else
	{
		printf("Illegal token\n");
		return 0;
	}
}

main()
{
	fgets(str,100,stdin);
	tok = nextToken();
	if(expr())
	{
		//printf("tok in main %c %d\n",tok ,tok );
		if (tok=='\n' || tok=='\0')
		{	
			printf("goal-> expr\n");
			while(!rules.empty())
			{	
				cout<<rules.top();
				printf("\n");
				rules.pop();
			}
			printf("\nSuccessful\n");
		}	
		else
		{	
			if(tok==')')
				printf("Unexpected )\n");
			else
				printf("Illegal token\n");
			printf("Unsuccessful\n");
		}
	}
	else
	{	

		//printf("Illegal token\n");
		printf("NO\n");
	}
}
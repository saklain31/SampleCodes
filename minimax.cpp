#include <bits/stdc++.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int m=-1,n=-1;

char board[3][3] =
    {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

struct Move
{
    int row, col;
};

bool isEmpty()
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='-')
                return true;
    return false;
}
 
int calculateval()
{
	for(int c=0;c<3;c++)
	{
		if(board[c][0]==board[c][1] && board[c][2]==board[c][1])
		{
			if(board[c][0]=='x')
				return 1;
			else if(board[c][0]=='o')
				return -1;
		}
	}

	for(int r=0;r<3;r++)
	{
		if(board[0][r]==board[1][r] && board[2][r]==board[1][r])
		{
			if(board[0][r]=='x')
				return 1;
			else if(board[0][r]=='o')
				return -1;
		}
	}

	if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		if(board[0][0]=='x')
			return 1;
		else if(board[0][0]=='o')
			return -1;
	}

	if(board[2][0] == board[1][1] && board[0][2] == board[1][1])
	{
		if(board[2][0]=='x')
			return 1;
		else if(board[2][0]=='o')
			return -1;		
	}

	return 0;
}

int minimax(bool flag)
{
    int val = calculateval();

    if(val == 1)
        return val;
    if(val == -1)
        return val;

    if(isEmpty()==false)
        return 0;

    if(flag)
    {
        int best = -100;
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                if (board[i][j]=='-')
                {
                    board[i][j] = 'x';
                    best = max(best,minimax(!flag) );
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }

    else
    {
        int best = 100;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]=='-')
                {
                    board[i][j] = 'o';
                    best = min(best,minimax(!flag));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }
}

Move findBestMovePlayer()
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (board[i][j]=='-')
            {
                board[i][j] = 'x';
                int moveVal = minimax(false);
                board[i][j] = '-';

                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
 
    //printf("Best Move is : %d\n",bestVal);
    printf("%d %d\n",bestMove.row,bestMove.col );

    if(bestVal>=0)
    {
    	//board[bestMove.row][bestMove.col]='x';
    	m=bestMove.row;
    	n=bestMove.col;
    }
    else {
    	printf("opponent wins\n");
    }	

 
    return bestMove;
}

Move findBestMoveOpponent()
{
    int bestVal = 1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (board[i][j]=='-')
            {
                board[i][j] = 'o';
                int moveVal = minimax(true);
                board[i][j] = '-';

                if (moveVal < bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
 
    //printf("Best Move is : %d\n",bestVal);
    printf("%d %d\n",bestMove.row,bestMove.col );

    if(bestVal<=0)
    {	
    	//board[bestMove.row][bestMove.col]='o';
    	m=bestMove.row;
    	n=bestMove.col;
    }
    else {
    	printf("player wins\n");
    }
 
    return bestMove;
}

int main()
{
	int f=0;
	int cnt=0;

	while(cnt<9)
	{
		m=-1,n=-1;
		if(f==0)
		{
			Move bestMove = findBestMovePlayer();
			f=1;
			scanf("%d %d",&m,&n);
			board[m][n]='x';
			cnt++;
		}	
		else
		{
			Move bestMove = findBestMoveOpponent();
			f=0;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
				{
					/*if(board[i][j]=='-')
					{
						if(m!=i && n!=j)
						{	board[i][j]='o'; break;
						}
					}*/
				}
			board[m][n]='o';
			cnt++;
		}
		char c;
	    scanf("%c",&c);
		for(int i=0;i<3;i++)
	    {
	    	for(int j=0;j<3;j++)
	    	{
	    		printf("%c ",board[i][j]);
	    	}
	    	printf("\n");
	    }
	    printf("*****\n");

	}
    
 
    
    return 0;
}
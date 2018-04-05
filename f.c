#include <time.h>
#include <stdlib.h>
#include <stdio.h>
main()
{
	srand(time(NULL));   // should only be called once
	int i;
	for(i=0;i<100;i++)printf("%d\n", rand()%1000); 
}
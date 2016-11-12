#include<stdio.h>
#include<time.h>

void main()
{
    time_t t;
    time(&t);
    printf("\ncurrent time is : %s",ctime(&t));
    int i, j;
    char s[10];
    for(j = 0; j < 5; j++)
    {
    	s[j] = 'a';
    }
    s[5] = '\0';
 	for(j = 0; j < 5; j++)
 	{
 		printf("%c\n", s[j]);
	    for(i = 0; i < 100000000; i++)
	    {

	    }
	 }
    time(&t);
    printf("\ncurrent time is : %s",ctime(&t));
}


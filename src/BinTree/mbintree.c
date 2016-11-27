#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i;
	boolean x;
	BinTree P;
	P = NilTree;
	infoTree Y;
	DealokTree(&P);
	LoadTree("skill2.txt", &P);
	SaveTree("skill.txt", P);
	PrintTree(P, 0 , 3);
	srand(time(NULL));
	for(i = 1; i <= 10; i++)
	{
		x = true;
		UnlockSkillRandom(&P, 7, 3, &Y, &x);
		printf("%s\n", SkillName(Y));
		printf("Unlocked\n\n");
	}
	DealokTree(&P);
	if(P == NilTree)
	{
		printf("Tree kosong\n");
	}
	return 0;
}
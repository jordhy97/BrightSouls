/* File: Driver untuk ADT BinTree */

#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	/* KAMUS LOKAL */
	int i;
	boolean x;
	BinTree P;
	P = NilTree;
	infoTree Y;

	/* ALGORITMA */
	printf("TESTING BinTree\n\n");
	printf("Reading from testtree1.txt\n");
	LoadTree("../../src/BinTree/testtree1.txt", &P);
	if(!IsUnlocked(P,SkillID(Akar(P))))
	{
		printf("%s not Unlocked\n",SkillName(Akar(P)));
		/* Unlocking skill */
		UnlockSkill(&P, 1, &Y);
		printf("%s Unlocked\n\n", SkillName(Akar(P)));
	}
	else
	{
		/* Printing tree */
		PrintTree(P, 0 , 3);
	}
	/* Unlocking skill */
	printf("Unlocking skills randomly\n");
	srand(time(NULL));
	for(i = 1; i <= 10; i++)
	{
		x = true;
		UnlockSkillRandom(&P, 7, 3, &Y, &x);
		printf("%s\n", SkillName(Y));
		printf("Unlocked\n\n");
	}
	printf("Writing to testtree2....\n");
	SaveTree("../../src/BinTree/testtree2.txt", P);
	DealokTree(&P);
	
	printf("\ntesttree2.txt:\n");
	LoadTree("../../src/BinTree/testtree2.txt", &P);
	/* Printing tree */
	PrintTree(P, 0 , 3);
	printf("\n");
	return 0;
}
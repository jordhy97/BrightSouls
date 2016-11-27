/* File: Driver untuk ADT MATRIKS */

#include <stdio.h>
#include "matriks.h"

int main()
{
	/* KAMUS */
	int Neff, i;
	MATRIKS MTest[100];
	
	/* ALGORITMA */
	Neff = 0;
	printf("TESTING MATRIKS\n\n");
	printf("BACA MATRIKS DARI FILE 'testmatriks.txt'\n");
	STARTMATRIKS("../src/Matriks/testmatriks.txt");
	while(!EndMATRIKS)
	{
		Neff++;
		AssignMATRIKS(CMATRIKS,&MTest[Neff]);
		ADVMATRIKS();
	}
	printf("ISI FILE 'testmatriks.txt' :\n");
	for(i = 1; i <= Neff; i++)
	{
		CetakMATRIKS(MTest[i]);
		printf("\n");
	}

	return 0;
}
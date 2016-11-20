/* Nama file    : mmatriks.c               */
/* Tanggal      : 29 Oktober 2016          */
/* Deskripsi    : Driver untuk matriks.c   */
#include <stdio.h>
#include "matriks.h"

int main()
{
	int Neff, i;
	MATRIKS MTest[100];
	Neff = 0;
	printf("TESTING MATRIKS\n\n");
	printf("BACA MATRIKS DARI FILE 'testmatriks.txt'\n");
	STARTMATRIKS("testmatriks.txt");
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
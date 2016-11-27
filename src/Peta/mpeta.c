/* Deskripsi    : Driver untuk peta.c dan area.c    */

#include <stdio.h>
#include "peta.h"

int main()
{
	/* KAMUS */
	int i, j;
	Peta MAP;
	POINT P, X;

	/* ALGORITMA */
	P = MakePOINT(2,3);
	CreateRandomPeta(&MAP,"../../src/Peta/testpeta.txt");
	printf("TESTING PETA AND AREA\n\n");
	printf("Isi MAP (diacak dari testpeta.txt):\n");
	for(i = IDMin; i <= GetLastID(MAP); i++)
	{
		printf("Area %d:\n", i);
		PrintArea(SubPeta(MAP,i), P);
		printf("\n");
	}
	printf("MAP Connection Data:\n");
	for(i = IDMin; i <= GetLastID(MAP); i++)
	{
		printf("%d ", i);
		for(j = 1; j <= 4; j++)
		{
			printf("%d", Koneksi(MAP,i,j));	
			if(j != 4)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\nTESTING CONNECTION Area 1\n\n");
	printf("Area 1\n");
	PrintArea(SubPeta(MAP,1), P);
	printf("\n");
	for(i = 1; i <= 4; i++)
	{
		if(Koneksi(MAP,1,i) != IDUndef)
		{
			switch(i)
			{
				case 1:
					printf("North of Area 1:\n");
					break;
				case 2:
					printf("East of Area 1:\n");
					break;
				case 3:
					printf("South of Area 1:\n");
					break;
				case 4:
					printf("West of Area 1:\n");
					break;
			}
			PrintArea(Neighbour(SubPeta(MAP,1),i), P);
			printf("\n");
		}
	}
	
	printf("TESTING SAVE AND LOAD PETA\n\n");
	SavePeta(MAP, "../../src/Peta/testsubpeta.txt", "../../src/Peta/testkoneksi.txt");
	DealokasiPeta(&MAP);
	LoadPeta(&MAP, "../../src/Peta/testsubpeta.txt", "../../src/Peta/testkoneksi.txt");
	printf("Isi MAP (dari testsubpeta.txt):\n");
	for(i = IDMin; i <= GetLastID(MAP); i++)
	{
		printf("Area %d:\n", i);
		PrintArea(SubPeta(MAP,i), P);
		printf("\n");
	}
	printf("MAP Connection Data:\n");
	for(i = IDMin; i <= GetLastID(MAP); i++)
	{
		printf("%d ", i);
		for(j = 1; j <= 4; j++)
		{
			printf("%d", Koneksi(MAP,i,j));
			if(j != 4)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\nTESTING CONNECTION Area 1\n\n");
	printf("Area 1\n");
	PrintArea(SubPeta(MAP,1), P);
	printf("\n");
	for(i = 1; i <= 4; i++)
	{
		if(Koneksi(MAP,1,i) != IDUndef)
		{
			switch(i)
			{
				case 1:
					printf("North of Area 1:\n");
					break;
				case 2:
					printf("East of Area 1:\n");
					break;
				case 3:
					printf("South of Area 1:\n");
					break;
				case 4:
					printf("West of Area 1:\n");
					break;
			}
			PrintArea(Neighbour(SubPeta(MAP,1),i), P);
			printf("\n");
		}
	}
	X = MakePOINT(1,1);
	if(IsPassable(SubPeta(MAP,1), X))
	{
		printf("Area 1 <1,1> is passable\n");
	}
	else
	{	
		printf("Area 1 <1,1> is not passable\n");
	}
	if(IsEnemy(SubPeta(MAP,1), X))
	{
		printf("Area 1 <1,1> is an enemy\n");
	}	
	else
	{
		printf("Area 1 <1,1> is not an enemy\n");
	}
	if(IsMedicine(SubPeta(MAP,1), X))
	{
		printf("Area 1 <1,1> is a medicine\n");
	}
	else
	{
		printf("Area 1 <1,1> is not a medicine\n");
	}
	if(IsBoss(SubPeta(MAP,1), X))
	{
		printf("Area 1 <1,1> is a boss\n");
	}
	else
	{
		printf("Area 1 <1,1> is not a boss\n");
	}
	ClearPOINT(&SubPeta(MAP,1), X);
	printf("Area 1 <1,1> cleared\n");
	printf("\n");
	PrintArea(SubPeta(MAP,1), P);
	printf("\n");
	DealokasiPeta(&MAP);
	return 0;
}
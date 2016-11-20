/* Nama file    : mmpeta.c                 			*/
/* Tanggal      : 10 November 2016         			*/
/* Deskripsi    : Driver untuk peta.c dan area.c    */

#include <stdio.h>
#include "peta.h"

int main()
{
	/* KAMUS */
	int i, j;
	Peta MAP;
	POINT P;

	/* ALGORITMA */
	P = MakePOINT(2,3);
	CreateRandomPeta(&MAP,"testpeta.txt");
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
	SavePeta(MAP, "testsubpeta.txt", "testkoneksi.txt");
	DealokasiPeta(&MAP);
	LoadPeta(&MAP, "testsubpeta.txt", "testkoneksi.txt");
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
	DealokasiPeta(&MAP);
	return 0;
}
/* NIM/Nama     : 13515004/Jordhy Fernando */
/* Nama file    : mmpeta.c                 */
/* Tanggal      : 10 November 2016         */
/* Deskripsi    : Driver untuk peta.c 	   */

#include <stdio.h>
#include "peta.h"

int main()
{
	char pilihan;
	Peta MAP;
	Area Start;
	POINT P;

	LoadPeta(&MAP, "peta.txt", "koneksi.txt");
	P = MakePOINT(3,3);
	Start = SubPeta(MAP,1);
	system("clear");
	printf("TESTING PETA AND AREA\n\n");
	PrintArea(Start,P);
	printf("INPUT: ");
	scanf("%c", &pilihan);
	while(pilihan != 'e')
	{
		switch(pilihan)
		{
			case 'u' : 
			{
				Ordinat(P)--;
				break;
			}
			case 'd' :
			{
				Ordinat(P)++;
				break;
			}
			case 'r' :
			{
				Absis(P)++;
				break;
			}
			case 'l' :
			{
				Absis(P)--;
				break;
			}
		}
		if(Absis(P) > GetLastIdxKol(Info(Start)))
		{
			Start = East(Start);
			Absis(P) = 1;
		}
		if(Ordinat(P) > GetLastIdxBrs(Info(Start)))
		{
			Start = South(Start);
			Ordinat(P) = 1;
		}
		if(Absis(P) == 0)
		{
			Start = West(Start);
			Absis(P) = GetLastIdxKol(Info(Start));
		}
		if(Ordinat(P) == 0)
		{
			Start = North(Start);
			Ordinat(P) = GetLastIdxBrs(Info(Start));
		}
		system("clear");
		printf("TESTING PETA AND AREA\n\n");
		PrintArea(Start,P);
		printf("INPUT: ");
		scanf("\n%c", &pilihan);
	}
	DealokasiPeta(&MAP);
	return 0;
}
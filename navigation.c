/* Nama file    : mmpeta.c                 			*/
/* Tanggal      : 10 November 2016         			*/
/* Deskripsi    : Driver untuk peta.c dan area.c    */

#include <stdio.h>
#include "peta.h"
#include "../MesinKarKata/mesinkata.h"
#include <stdlib.h>

int main()
{
	/* KAMUS */
	Peta MAP;
	Area Start;
	POINT P;
	Kata Masukan, GU, GD, GL, GR, EXIT;

	/* ALGORITMA */
	CreateKata(&GU, "GU");
	CreateKata(&GR, "GR");
	CreateKata(&GD, "GD");
	CreateKata(&GL, "GL");
	CreateKata(&EXIT, "EXIT");
	P = MakePOINT(3,3);
	CreateRandomPeta(&MAP,"testpeta.txt");
	Start = SubPeta(MAP,IDMin);
	system("clear");
	printf("TESTING PETA AND AREA WITH SIMPLE MAP NAVIGATION\n\n");
	PrintArea(Start,P);
	printf("INPUT: ");
	BacaKata(&Masukan);
	while(!IsKataSama(Masukan,EXIT))
	{
		if(IsKataSama(Masukan,GU))
		{
			if(IsPassable(Start,Ordinat(P) - 1,Absis(P)))
			{
				SetPOINT(&P, PlusDelta(P, 0, (-1)));
			}
		}
		else if(IsKataSama(Masukan,GD))
		{
			if(IsPassable(Start,Ordinat(P) + 1,Absis(P)))
			{
				SetPOINT(&P, PlusDelta(P, 0, 1));
			}
		}
		else if(IsKataSama(Masukan,GR))
		{
			if(IsPassable(Start,Ordinat(P),Absis(P) + 1))
			{
				SetPOINT(&P, PlusDelta(P, 1, 0));
			}
		}
		else if(IsKataSama(Masukan,GL))
		{
			if(IsPassable(Start,Ordinat(P),Absis(P) - 1))
			{
				SetPOINT(&P, PlusDelta(P, (-1), 0));
			}
		}
		if(Ordinat(P) == 0)
		{
			Start = Neighbour(Start, 1);
			SetPOINT(&P, P_Neighbour(Start, 3));
		}
		else if(Absis(P) > GetLastIdxKol(Info(Start)))
		{
			Start = Neighbour(Start, 2);
			SetPOINT(&P, P_Neighbour(Start, 4));
		}
		else if(Ordinat(P) > GetLastIdxBrs(Info(Start)))
		{
			Start = Neighbour(Start, 3);
			SetPOINT(&P, P_Neighbour(Start, 1));
		}
		else if(Absis(P) == 0)
		{
			Start = Neighbour(Start, 4);
			SetPOINT(&P, P_Neighbour(Start, 2));
		}
		system("clear");
		printf("TESTING PETA AND AREA WITH SIMPLE MAP NAVIGATION\n\n");
		PrintArea(Start,P);
		printf("INPUT: ");
		BacaKata(&Masukan);
	}
	SavePeta(MAP, "coba1.txt", "coba2.txt");
	DealokasiPeta(&MAP);
	return 0;
}
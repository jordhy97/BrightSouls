/* NIM/Nama     : 13515004/Jordhy Fernando 			*/
/* Nama file    : mmpeta.c                 			*/
/* Tanggal      : 10 November 2016         			*/
/* Deskripsi    : Driver untuk peta.c dan area.c    */

#include <stdio.h>
#include "peta.h"
#include "../MesinKarKata/mesinkata.h"

int main()
{
	int i;
	Peta MAP;
	Area Start;
	POINT P;
	Kata Masukan, GU, GD, GL, GR, EXIT;

	GU.TabKata[1] = 'G';
	GU.TabKata[2] = 'U';
	GU.Length = 2;
	GD.TabKata[1] = 'G';
	GD.TabKata[2] = 'D';
	GD.Length = 2;
	GL.TabKata[1] = 'G';
	GL.TabKata[2] = 'L';
	GL.Length = 2;
	GR.TabKata[1] = 'G';
	GR.TabKata[2] = 'R';
	GR.Length = 2;
	EXIT.TabKata[1] = 'E';
	EXIT.TabKata[2] = 'X';
	EXIT.TabKata[3] = 'I';
	EXIT.TabKata[4] = 'T';
	EXIT.Length = 4;
	LoadPeta(&MAP, "peta.txt", "koneksi.txt");
	P = MakePOINT(3,3);
	Start = SubPeta(MAP,1);
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
				Ordinat(P)--;
			}
		}
		else if(IsKataSama(Masukan,GD))
		{
			if(IsPassable(Start,Ordinat(P) + 1,Absis(P)))
			{
				Ordinat(P)++;
			}
		}
		else if(IsKataSama(Masukan,GR))
		{
			if(IsPassable(Start,Ordinat(P),Absis(P) + 1))
			{
				Absis(P)++;
			}
		}
		else if(IsKataSama(Masukan,GL))
		{
			if(IsPassable(Start,Ordinat(P),Absis(P) - 1))
			{
				Absis(P)--;
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
		printf("TESTING PETA AND AREA WITH SIMPLE MAP NAVIGATION\n\n");
		PrintArea(Start,P);
		printf("INPUT: ");
		BacaKata(&Masukan);
	}
	DealokasiPeta(&MAP);
	return 0;
}
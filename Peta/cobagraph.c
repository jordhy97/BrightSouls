#include <stdio.h>
#include "peta.h"
#include "../Matriks/matriks.h"
#include "../Matriks/mesinkar.h"
#include "../Area/area.h"
#include <stdlib.h>

int posx, posy;

void CetakMATRIKS (MATRIKS M)
{
	int i, j;
	for(i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++)
	{
		for(j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++)
		{
			if(posx == j && posy == i)
			{
				printf("P");
			}
			else
			{
				printf("%c", Elmt(M,i,j));
			}
			if(j != GetLastIdxKol(M))
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main()
{
	char pilihan;
	Peta MAP;
	Area Start;
	posx = 3;
	posy = 3;
	LoadPeta(&MAP, "peta.txt", "koneksi.txt");
	Start = SubPeta(MAP,1);
	system("clear");
	CetakMATRIKS(Info(Start));
	printf("INPUT: ");
	scanf("%c", &pilihan);
	while(pilihan != 'e')
	{
		switch(pilihan)
		{
			case 'u' : 
			{
				posy--;
				break;
			}
			case 'd' :
			{
				posy++;
				break;
			}
			case 'r' :
			{
				posx++;
				break;
			}
			case 'l' :
			{
				posx--;
				break;
			}
		}
		if(posx > GetLastIdxKol(Info(Start)))
		{
			Start = East(Start);
			posx = 1;
		}
		if(posy > GetLastIdxBrs(Info(Start)))
		{
			Start = South(Start);
			posy = 1;
		}
		if(posx == 0)
		{
			Start = West(Start);
			posx = GetLastIdxKol(Info(Start));
		}
		if(posy == 0)
		{
			Start = North(Start);
			posy = GetLastIdxBrs(Info(Start));
		}
		system("clear");
		CetakMATRIKS(Info(Start));
		printf("INPUT: ");
		scanf("\n%c", &pilihan);
	}
	return 0;
}
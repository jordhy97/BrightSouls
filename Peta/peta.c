/* NIM/Nama     : 13515004/Jordhy Fernando */
/* Nama file    : peta.c 	 	           */
/* Tanggal      : 30 Oktober 2016          */
/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada peta.h */

#include "peta.h"
#include "../Matriks/mesinkar.h"
#include <stdio.h>

void LoadPeta(Peta *P, char *namafileSubPeta, char *namafileKoneksi)
{
	/* ALGORITMA */
	LoadSubPeta(P, namafileSubPeta);
	LoadKoneksi(P, namafileKoneksi);
}

void LoadSubPeta(Peta *P, char *namafile)
{
	/* KAMUS LOKAL */
	ID i;

	/* ALGORITMA */
	i = 1;
	STARTMATRIKS(namafile);
	while(!EndMATRIKS)
	{
		SubPeta(*P,i) = Alokasi(CMATRIKS);
		i++;
		ADVMATRIKS();
	}
}

void LoadKoneksi(Peta *P, char *namafile)
{
	/* KAMUS LOKAL */
	ID Node, tetangga;
	int arah;

	/* ALGORITMA */
	START(namafile);
	while(CC != MARK)
	{
		Node = 0;
		arah = 0;
		while(CC != BLANK)
		{
			Node = Node * 10 + (CC - '0');
			ADV();
		}
		ADV();
		while((CC != ENTER) && (CC != MARK))
		{
			tetangga = 0;
			while((CC != BLANK) && (CC != ENTER) && (CC != MARK))
			{
				tetangga = tetangga * 10 + (CC - '0');
				ADV();
			}
			arah++;
			Koneksi(*P,Node,arah) = tetangga;
			if(tetangga != 0)
			{
				switch(arah)
				{
					case 1 :
					{
						InsNorth(&SubPeta(*P,Node), SubPeta(*P,tetangga));
						break;
					}
					case 2 :
					{
						InsEast(&SubPeta(*P,Node), SubPeta(*P,tetangga));
						break;
					}
					case 3 :
					{
						InsSouth(&SubPeta(*P,Node), SubPeta(*P,tetangga));
						break;
					}
					case 4 :
					{
						InsWest(&SubPeta(*P,Node), SubPeta(*P,tetangga));
						break;
					}
				}
			}
			if(CC == BLANK)
			{
				ADV();
			}	
		}
		if(CC == ENTER)
		{
			ADV();
		}
	}
}
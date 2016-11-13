/* NIM/Nama     : 13515004/Jordhy Fernando */
/* Nama file    : peta.c 	 	           */
/* Tanggal      : 30 Oktober 2016          */
/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada peta.h */

#include "peta.h"
#include "../MesinKarKata/mesinkar.h"
#include <stdio.h>


/****************** KONSTRUKTOR (VIA FILE EKSTERNAL) ******************/
void LoadPeta(Peta *P, char *namafileSubPeta, char *namafileKoneksi)
/* I.S. P sembarang, namafileSubPeta dan namafileKoneksi terdefinisi */
/* F.S. Terbentuk Peta P sesuai dengan data yang ada di dalam file eksternal */
{
	/* ALGORITMA */
	LoadSubPeta(P, namafileSubPeta);
	LoadKoneksi(P, namafileKoneksi);
	CreateKoneksi(P);
}

void LoadSubPeta(Peta *P, char *namafile)
/* I.S. P sembarang, namafile terdefinisi */
/* F.S. Terbentuk SubPeta P (kumpulan Area) sesuai dengan data yang ada di file dengan nama namafile */
{
	/* KAMUS LOKAL */
	ID i;

	/* ALGORITMA */
	i = 0;
	STARTMATRIKS(namafile);
	while(!EndMATRIKS)
	{
		i++;
		CreateEmptyArea(&SubPeta(*P,i));
		SubPeta(*P,i) = Alokasi(CMATRIKS);
		ADVMATRIKS();
	}
	IDEff(*P) = i;
}

void LoadKoneksi(Peta *P, char *namafile)
/* I.S. P sembarang, namafile terdefinisi */
/* F.S. Terbentuk koneksi antar-Area di P sesuai dengan data yang ada di file dengan nama namafile */
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

void CreateKoneksi(Peta *P)
/* I.S. P terdefinisi */
/* F.S. Antar-Area pada P terhubung berdasarkan data koneksi P */
{
	/* KAMUS LOKAL */
	int Node, tetangga, arah;

	/* ALGORITMA */
	for(Node = 1; Node <= IDEff(*P); Node++)
	{
		for(arah = 1; arah <= 4; arah++)
		{
			tetangga = Koneksi(*P,Node,arah);
			if(tetangga)
			{
				switch(arah)
				{
					case 1 :
					{
						SetNorth(&SubPeta(*P,Node), SubPeta(*P,tetangga));
						break;
					}
					case 2 :
					{
						SetEast(&SubPeta(*P,Node), SubPeta(*P,tetangga));
						break;
					}
					case 3 :
					{
						SetSouth(&SubPeta(*P,Node), SubPeta(*P,tetangga));
						break;
					}
					case 4 :
					{
						SetWest(&SubPeta(*P,Node), SubPeta(*P,tetangga));
						break;
					}
				}
			}
		}
	}
}

/****************** Manajemen Memori ******************/
void DealokasiPeta(Peta *P)
/* I.S. P terdefinisi */
/* F.S. Semua address di P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian semua address (Area) di P */
{	
	/* KAMUS LOKAL */
	int i;
	
	/* ALGORITMA */
	for(i = 1; i <= IDEff(*P); i++)
	{
		Dealokasi(SubPeta(*P,i));
	}
}
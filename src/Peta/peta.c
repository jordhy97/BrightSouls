/* NIM/Nama     : 13515004/Jordhy Fernando */
/* Nama file    : peta.c 	 	           */
/* Tanggal      : 30 Oktober 2016          */
/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada peta.h */

#include "peta.h"
#include "../MesinKarKata/mesinkar.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "boolean.h"

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
		SubPeta(*P,i) = AlokasiArea(CMATRIKS);
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
						SetNeighbour(&SubPeta(*P,Node), SubPeta(*P,tetangga), 1);
						break;
					}
					case 2 :
					{
						SetNeighbour(&SubPeta(*P,Node), SubPeta(*P,tetangga), 2);
						break;
					}
					case 3 :
					{
						SetNeighbour(&SubPeta(*P,Node), SubPeta(*P,tetangga), 3);
						break;
					}
					case 4 :
					{
						SetNeighbour(&SubPeta(*P,Node), SubPeta(*P,tetangga), 4);
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
		DealokasiArea(SubPeta(*P,i));
	}
}

void CreateRandomPeta(Peta *PHasil, char *namafile)
{
	/* KAMUS LOKAL */
	Peta P;
	int arah, count, i;
	ID next, start;
	boolean used[IDMax+1];

	/* ALGORITMA */
	LoadSubPeta(&P, namafile);
	for(i = 1; i <= IDEff(P); i++)
	{
		used[i] = false;
	}
	srand(time(NULL));
	count = 1;
	next = rand() % IDEff(P) + 1;
	SubPeta(*PHasil, count) = SubPeta(P, next);
	SetAreaPoint(&SubPeta(*PHasil, count));
	for(i = 1; i <= 4; i++)
	{
		Koneksi(*PHasil, count, i) = IDUndef;
	}
	used[next] = true;
	do
	{ 
		do
		{
			start = rand() % count + 1;			// Choosing current area to process
			i = 1;
			while((i < 4) && Koneksi(*PHasil, start, i) != IDUndef)
			{
				i++;
			}
		}while(Koneksi(*PHasil, start, i) != IDUndef);
		do
		{
			arah = rand() % 4 + 1;				// Choosing the direction to connect
		}while(Koneksi(*PHasil, start, arah) != IDUndef);
		do
		{
			next = rand() % IDEff(P) + 1;		// Choosing next area to connect to current area
		}while(used[next]);
		count++;
		SubPeta(*PHasil, count) = SubPeta(P, next);
		SetAreaPoint(&SubPeta(*PHasil, count));
		for(i = 1; i <= 4; i++)
		{
			Koneksi(*PHasil, count, i) = IDUndef;
		}
		used[next] = true;
		switch(arah)
		{
			case 1 :
			{
				Koneksi(*PHasil, start, 1) = count;
				Koneksi(*PHasil, count, 3) = start;
				break;
			}
			case 2 :
			{
				Koneksi(*PHasil, start, 2) = count;
				Koneksi(*PHasil, count, 4) = start;
				break;
			}
				case 3 :
			{
				Koneksi(*PHasil, start, 3) = count;
				Koneksi(*PHasil, count, 1) = start;
				break;
			}
			case 4 :
			{
				Koneksi(*PHasil, start, 4) = count;
				Koneksi(*PHasil, count, 2) = start;
				break;
			}
		}
	}while(count != IDEff(P));
	IDEff(*PHasil) = count;
	CreateKoneksi(PHasil);
	CloseUnconnectedSubMapPoint(PHasil);
}

void CloseUnconnectedSubMapPoint(Peta *P)
{
	/* KAMUS LOKAL */
	int i, j;

	/* ALGORITMA */
	for(i = IDMin; i <= IDEff(*P); i++)
	{
		for(j = 1; j <= 4; j++)
		{
			if(Koneksi(*P, i, j) == IDUndef)
			{
				switch(j)
				{
					case 1:
						Elmt(Info(SubPeta(*P,i)), Ordinat(P_Neighbour(SubPeta(*P,i), 1)), Absis(P_Neighbour(SubPeta(*P,i), 1))) = '#';
						break;
					case 2:
						Elmt(Info(SubPeta(*P,i)), Ordinat(P_Neighbour(SubPeta(*P,i), 2)), Absis(P_Neighbour(SubPeta(*P,i), 2))) = '#';
						break;
					case 3:
						Elmt(Info(SubPeta(*P,i)), Ordinat(P_Neighbour(SubPeta(*P,i), 3)), Absis(P_Neighbour(SubPeta(*P,i), 3))) = '#';
						break;
					case 4:
						Elmt(Info(SubPeta(*P,i)), Ordinat(P_Neighbour(SubPeta(*P,i), 4)), Absis(P_Neighbour(SubPeta(*P,i), 4))) = '#';
						break;
				}
			}
		}
	}
}
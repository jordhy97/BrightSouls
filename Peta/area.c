/* NIM/Nama     : 13515004/Jordhy Fernando */
/* Nama file    : area.c 	 	           */
/* Tanggal      : 29 Oktober 2016          */
/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada area.h */

#include "area.h"
#include <stdlib.h>
#include <stdio.h>

/* PROTOTYPE */
/****************** KONSTRUKTOR ******************/
void CreateEmptyArea (Area *A)
/* I.S. A sembarang  */
/* F.S. Terbentuk Area kosong. Lihat definisi di atas. */
{
	/* ALGORITMA */
	*A = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, North(P)=Nil, South(P)=Nil, West(P)=Nil, East(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
{
	/* KAMUS LOKAL */
	address P;

	/* ALGORITMA */
	P = (address) malloc(sizeof(ElmtArea));
	if(P != Nil)
	{
		Info(P) = X;
		North(P) = Nil;
		South(P) = Nil;
		West(P) = Nil;
		East(P) = Nil;
	}
	return P;
}

void Dealokasi (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	/* ALGORITMA */
	free(P);
}

/*** PENAMBAHAN ELEMEN ***/
void SetNorth (Area *A, Area P)
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan North(A) = P */
{
	/* ALGORITMA */
	North(*A) = P; 
}

void SetSouth (Area *A, Area P)
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan South(A) = P */
{
	/* ALGORITMA */
	South(*A) = P;
}

void SetWest (Area *A, Area P)
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan West(A) = P */
{
	/* ALGORITMA */
	West(*A) = P;
}

void SetEast (Area *A, Area P)
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan East(A) = P */
{
	/* ALGORITMA */
	East(*A) = P;
}

/*** Proses Current Area ***/
void PrintArea (Area A, POINT P)
/* I.S. A tidak kosong dan P (posisi Player) terdefinisi*/
/* F.S. Isi Info(A) dicetak dengan posisi di P diganti dengan 'P' */
{
	int i, j;
	for(i = GetFirstIdxBrs(Info(A)); i <= GetLastIdxBrs(Info(A)); i++)
	{
		for(j = GetFirstIdxKol(Info(A)); j <= GetLastIdxKol(Info(A)); j++)
		{
			if(Absis(P) == j && Ordinat(P) == i)
			{
				printf("P");
			}
			else
			{
				printf("%c", Elmt(Info(A),i,j));
			}
			if(j != GetLastIdxKol(Info(A)))
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

boolean IsPassable(Area A, int i, int j)
/* Menghasilkan true jika Elmt(Info(A),i,j) dapat dilewati dan false jika tidak */
{
	return (Elmt(Info(A),i,j) != '#');
}
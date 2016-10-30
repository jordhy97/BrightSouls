/* NIM/Nama     : 13515004/Jordhy Fernando */
/* Nama file    : area.c 	 	           */
/* Tanggal      : 29 Oktober 2016          */
/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada area.h */

#include "area.h"
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST AREA KOSONG ******************/
boolean IsAreaEmpty (Area A)
/* Mengirim true jika A kosong. Lihat definisi di atas. */
{
	/* ALGORITMA */
	return(A == Nil);
}

/****************** KONSTRUKTOR ******************/
void CreateEmptyArea (Area *A)
/* I.S. A sembarang  */
/* F.S. Terbentuk Area kosong. Lihat definisi di atas. */
{
	/* ALGORITMA */
	*A = Nil;
}

void InitArea(Area *A, infotype X)
/* I.S. A sembarang */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen A dengan nilai X jika alokasi berhasil (Info(A) = X). Jika alokasi gagal: Peta adalah PETA kosong*/
{
	/* KAMUS LOKAL */
	address P;

	/* ALGORITMA */
	CreateEmptyArea(A);
	P = Alokasi(X);
	if(P != Nil)
	{
		*A = P;
	}
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

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsNorth (Area *A, Area P)
/* I.S. A tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen North dengan nilai X jika alokasi berhasil. Jika alokasi gagal: I.S. = F.S.*/
{
	/* ALGORITMA */
	North(*A) = P; 
}

void InsSouth (Area *A, Area P)
/* I.S. A tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen South dengan nilai X jika alokasi berhasil. Jika alokasi gagal: I.S. = F.S.*/
{
	/* ALGORITMA */
	South(*A) = P;
}

void InsWest (Area *A, Area P)
/* I.S. A tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen West dengan nilai X jika alokasi berhasil. Jika alokasi gagal: I.S. = F.S.*/
{
	/* ALGORITMA */
	West(*A) = P;
}

void InsEast (Area *A, Area P)
/* I.S. A tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen East dengan nilai X jika alokasi berhasil. Jika alokasi gagal: I.S. = F.S.*/
{
	/* ALGORITMA */
	East(*A) = P;
}
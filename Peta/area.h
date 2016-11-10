/* File : area.h */
/* ADT Area dengan List Quad(empat) Pointer */
/* Representasi berkait dengan address adalah pointer */
/* infotype adalah pointer ke MATRIKS */

#ifndef AREA_H
#define AREA_H

#include "../Matriks/matriks.h"
#include "../Point/point.h"

/* Kamus Umum */
#define Nil NULL

/* Definisi Type Data */
typedef MATRIKS infotype;
typedef struct tElmtArea *address;
typedef struct tElmtArea {
	infotype info;
	address north;
	address south;
	address west;
	address east;
} ElmtArea;
typedef address Area;

/* Definisi Area : */
/* Area kosong : A = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), North(P), South(P), West(P), East(P) */

/* Notasi Akses */
#define Info(P) (P)->info
#define North(P) (P)->north
#define South(P) (P)->south
#define West(P) (P)->west
#define East(P) (P)->east

/* PROTOTYPE */
/****************** KONSTRUKTOR ******************/
void CreateEmptyArea (Area *A);
/* I.S. A sembarang  */
/* F.S. Terbentuk Area kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
address Alokasi (infotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, North(P)=Nil, South(P)=Nil, West(P)=Nil, East(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */

void Dealokasi (address P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/*** PENAMBAHAN ELEMEN ***/
void SetNorth (Area *A, Area P);
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan North(A) = P */
void SetSouth (Area *A, Area P);
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan South(A) = P */
void SetWest (Area *A, Area P);
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan West(A) = P */
void SetEast (Area *A, Area P);
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan West(A) = P */

/*** Proses Current Area ***/
void PrintArea (Area A, POINT P);
/* I.S. A tidak kosong dan P terdefinisi*/
/* F.S. Isi Info(A) dicetak dengan posisi di P diganti dengan 'P' */
#endif
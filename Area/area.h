/* File : area.h */
/* ADT Area dengan List Quad(empat) Pointer */
/* Representasi berkait dengan address adalah pointer */
/* infotype adalah pointer ke MATRIKS */

#ifndef AREA_H
#define AREA_H

#include "../Matriks/matriks.h"

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
/****************** TEST AREA KOSONG ******************/
boolean IsAreaEmpty (Area A);
/* Mengirim true jika A kosong. Lihat definisi di atas. */

/****************** KONSTRUKTOR ******************/
void CreateEmptyArea (Area *A);
/* I.S. A sembarang  */
/* F.S. Terbentuk Area kosong. Lihat definisi di atas. */

void InitArea(Area *A, infotype X);
/* I.S. A sembarang */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen A dengan nilai X jika alokasi berhasil (Info(A) = X). Jika alokasi gagal: I.S. = F.S.*/

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

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsNorth (Area *A, Area P);
/* I.S. A tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen North dengan nilai X jika alokasi berhasil. Jika alokasi gagal: I.S. = F.S.*/
void InsSouth (Area *A, Area P);
/* I.S. A tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen South dengan nilai X jika alokasi berhasil. Jika alokasi gagal: I.S. = F.S.*/
void InsWest (Area *A, Area P);
/* I.S. A tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen West dengan nilai X jika alokasi berhasil. Jika alokasi gagal: I.S. = F.S.*/
void InsEast (Area *A, Area P);
/* I.S. A tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen East dengan nilai X jika alokasi berhasil. Jika alokasi gagal: I.S. = F.S.*/

#endif

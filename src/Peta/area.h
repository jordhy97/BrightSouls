/* File : area.h */
/* ADT Area dengan List Quad(empat) Pointer */
/* Representasi berkait dengan address adalah pointer */
/* infotype adalah pointer ke MATRIKS */

#ifndef AREA_H
#define AREA_H

#include "boolean.h"
#include "../Matriks/matriks.h"
#include "../Point/point.h"
#include <ncurses.h>

/* Kamus Umum */
#define Nil NULL
#define Wall '#'

/* Definisi Type Data */
typedef MATRIKS infotype;
typedef struct tElmtArea *address;
typedef struct tElmtArea {
	infotype info;
	address north;
	address south;
	address west;
	address east;
	POINT P_north;
	POINT P_south;
	POINT P_west;
	POINT P_east;
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
#define P_North(P) (P)->P_north
#define P_South(P) (P)->P_south
#define P_West(P) (P)->P_west
#define P_East(P) (P)->P_east

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

void wPrintArea (WINDOW *menu, Area A, POINT P);
/* I.S. A tidak kosong dan P terdefinisi*/
/* F.S. Isi Info(A) dicetak dengan posisi di P diganti dengan 'P' */

void SetAreaPoint(Area *A);

/*** TEST Daerah***/
boolean IsPassable(Area A, int i, int j);
/* Menghasilkan true jika Elmt(Info(A),i,j) dapat dilewati dan false jika tidak */

#endif
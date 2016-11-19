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
#define NilArea NULL
#define Wall '#'
#define MaxNeighbour 4

/* Definisi Type Data */
typedef MATRIKS infotypeArea;
typedef struct tElmtArea *addressArea;
typedef struct tElmtArea {
	infotypeArea info;
	addressArea neighbour[MaxNeighbour+1];
	POINT P_neighbour[MaxNeighbour+1];
} ElmtArea;
typedef addressArea Area;

/* Definisi Area : */
/* Area kosong : A = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), North(P), South(P), West(P), East(P) */

/* Notasi Akses */
#define Info(P) (P)->info
#define Neighbour(P,i) (P)->neighbour[(i)]
#define P_Neighbour(P,i) (P)->P_neighbour[(i)]

/* PROTOTYPE */
/****************** KONSTRUKTOR ******************/
void CreateEmptyArea (Area *A);
/* I.S. A sembarang  */
/* F.S. Terbentuk Area kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
addressArea AlokasiArea (infotypeArea X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, North(P)=Nil, South(P)=Nil, West(P)=Nil, East(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */

void DealokasiArea (addressArea P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/*** PENAMBAHAN ELEMEN ***/
void SetNeighbour (Area *A, Area P, int i);
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan North(A) = P */

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
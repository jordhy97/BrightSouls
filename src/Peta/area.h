/* File : area.h */
/* Representasi berkait dengan address adalah pointer */
/* infotype adalah pointer ke MATRIKS */

#ifndef AREA_H
#define AREA_H

#include "../Shared/boolean.h"
#include "../Matriks/matriks.h"
#include "../Point/point.h"
#include <ncurses.h>

/* Kamus Umum */
#define NilArea NULL
#define Wall '#'
#define MaxNeighbour 4
#define Musuh 'E'
#define Medicine 'M'
#define Path '.'
#define Boss 'B'

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
/* Area kosong : A = NilArea */
/* Setiap elemen dengan address P dapat diacu Info(P), Neighbour(P,i), dan P_Neighbour(P,i) */

/* Notasi Akses */
#define Info(A) (A)->info
#define Neighbour(A,i) (A)->neighbour[(i)]
#define P_Neighbour(A,i) (A)->P_neighbour[(i)]

/* PROTOTYPE */
/****************** KONSTRUKTOR ******************/
void CreateEmptyArea (Area *A);
/* I.S. A sembarang  */
/* F.S. Terbentuk Area kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
addressArea AlokasiArea (infotypeArea X);
/* Mengirimkan addressArea hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressArea tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, dan semua Neighbour(P) = NilArea */
/* Jika alokasi gagal, mengirimkan NilArea. */

void DealokasiArea (addressArea P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressArea P */

/*** PENAMBAHAN ELEMEN ***/
void SetNeighbour (Area *A, Area P, int i);
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan Neighbour(A,i) = P */

/*** Proses Current Area ***/
void PrintArea (Area A, POINT P);
/* I.S. A tidak kosong dan P terdefinisi*/
/* F.S. Isi Info(A) dicetak dengan posisi di P diganti dengan 'P' */

/*** I/O Khusus Ncurses ***/
void wPrintArea (WINDOW *win, Area A, POINT P);
/* I.S. A tidak kosong dan P terdefinisi*/
/* F.S. Isi Info(A) dicetak ke win dengan posisi di P diganti dengan 'P' */

/*** Operasi Lain pada Area ***/
void SetAreaPoint(Area *A);
/* I.S. Area A tidak kosong dan di keempat sisi A (atas, kanan, bawah, kiri) terdapat maksimal satu karakter '.' */
/* F.S. P_Neighbour(A, i) diisi dengan titik yang sesuai pada posisi i[1..4] yang sesuai */
/* Note : Prosedur khusus untuk area dengan jumlah tetangga maksimal 4 dengan lokasi tetangga di atas, kanan, bawah, kiri */

/*** TEST Daerah***/
boolean IsPassable(Area A, POINT P);
/* Menghasilkan true jika koordinat P pada Area A dapat dilewati dan false jika tidak */

boolean IsEnemy(Area A, POINT P);
/* Menghasilkan true jika koordinat P pada Area A adalah enemy dan false jika tidak */

boolean IsMedicine(Area A, POINT P);
/* Menghasilkan true jika koordinat P pada Area A adalah medicine dan false jika tidak */

boolean IsBoss(Area A, POINT P);
/* Menghasilkan true jika koordinat P pada Area A adalah boss dan false jika tidak */

void ClearPOINT(Area *A, POINT P);
/* I.S. A dan P terdefinisi */
/* F.S. koordinat P pada Area A diganti menjadi path */
#endif
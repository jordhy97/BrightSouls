/* File : peta.h */
/* *** Definisi ABSTRACT DATA TYPE Peta *** */
/* Peta merupakan kumpulan Area yang dibedakan berdasarkan ID tertentu */
/* ID didefinisikan sebagai indeks dari array */

#ifndef PETA_H
#define PETA_H

#include "../Matriks/matriks.h"
#include "../Area/area.h"

/* Kamus Umum */
#define IDMax 10
#define IDMin 1

/* Definisi Type Data */
typedef int ID; /* type ID */
typedef struct {
	Area SubPeta[IDMax+1];
	ID Koneksi[IDMax+1][5];
} Peta;

/* ********** SELEKTOR ********** */
#define SubPeta(P,i) (P).SubPeta[(i)]
#define Koneksi(P,i,j) (P).Koneksi[(i)][(j)]

/* PROTOTYPE */
/****************** TEST AREA KOSONG ******************/

/* Mengirim true jika A kosong. Lihat definisi di atas. */

/****************** KONSTRUKTOR ******************/
void LoadPeta(Peta *P, char *namafileSubPeta, char *namafileKoneksi);

void LoadSubPeta(Peta *P, char *namafile);
/* I.S. P sembarang  */
/* F.S. Terbentuk Area kosong. Lihat definisi di atas. */


/* I.S. A sembarang */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen A dengan nilai X jika alokasi berhasil (Info(A) = X). Jika alokasi gagal: I.S. = F.S.*/

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/

void LoadKoneksi(Peta *P, char *namafile);

#endif

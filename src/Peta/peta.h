/* File : peta.h */
/* *** Definisi ABSTRACT DATA TYPE Peta *** */
/* Peta merupakan kumpulan Area yang dibedakan berdasarkan ID tertentu dan memiliki data hubungan antar-Area*/
/* ID didefinisikan sebagai indeks dari array */

#ifndef PETA_H
#define PETA_H

#include "../Matriks/matriks.h"
#include "area.h"

/* Kamus Umum */
#define IDMax 10
#define IDMin 1
#define EnMax 10
#define IDUndef 999

/* Definisi Type Data */
typedef int ID; /* type ID */
typedef struct {
	Area SubPeta[IDMax+1];
	ID Koneksi[IDMax+1][MaxNeighbour+1];
	int IDEff;
} Peta;

/* ********** SELEKTOR ********** */
#define SubPeta(P,i) (P).SubPeta[(i)]
#define Koneksi(P,i,j) (P).Koneksi[(i)][(j)]
#define IDEff(P) (P).IDEff

/****************** KONSTRUKTOR (VIA FILE EKSTERNAL) ******************/
void LoadPeta(Peta *P, char *namafileSubPeta, char *namafileKoneksi);
/* I.S. P sembarang, namafileSubPeta dan namafileKoneksi terdefinisi */
/* F.S. Terbentuk Peta P sesuai dengan data yang ada di dalam file eksternal */

void LoadSubPeta(Peta *P, char *namafile);
/* I.S. P sembarang, namafile terdefinisi */
/* F.S. Terbentuk SubPeta P (kumpulan Area) sesuai dengan data yang ada di file dengan nama namafile */

void LoadKoneksi(Peta *P, char *namafile);
/* I.S. P sembarang, namafile terdefinisi */
/* F.S. Terbentuk koneksi antar-Area di P sesuai dengan data yang ada di file dengan nama namafile */

void CreateKoneksi(Peta *P);
/* I.S. P terdefinisi */
/* F.S. Antar-Area pada P terhubung berdasarkan data koneksi P */

/****************** Manajemen Memori ******************/
void DealokasiPeta(Peta *P);
/* I.S. P terdefinisi */
/* F.S. Semua address di P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian semua address (Area) di P */

void CreateRandomPeta(Peta *PHasil, char *namafile);

void CloseUnconnectedSubMapPoint(Peta *P);
#endif
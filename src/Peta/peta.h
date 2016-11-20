/* File : peta.h */
/* *** Definisi ABSTRACT DATA TYPE Peta *** */
/* Peta merupakan kumpulan Area yang dibedakan berdasarkan ID tertentu dan memiliki data hubungan antar-Area*/
/* ID didefinisikan sebagai indeks dari array */

#ifndef PETA_H
#define PETA_H

#include "../Matriks/matriks.h"
#include "../MesinKarKata/mesinkata.h"
#include "area.h"
#include "../Shared/boolean.h"

/* Kamus Umum */
#define IDMax 10
#define IDMin 1
#define EnMax 100
#define IDUndef 999

/* Definisi Type Data */
typedef int ID; /* type ID */
typedef struct {
	Area SubPeta[IDMax+1];
	ID Koneksi[IDMax+1][MaxNeighbour+1];
	Kata Enemy[EnMax+1];
	int IDEff;
} Peta;

/* ********** SELEKTOR ********** */
#define SubPeta(P,i) (P).SubPeta[(i)]
#define Koneksi(P,i,j) (P).Koneksi[(i)][(j)]
#define IDEff(P) (P).IDEff
#define Enemy(P,i) (P).Enemy[(i)]

ID GetLastID (Peta P);
/* Mengirimkan ID terbesar P */

/****************** KONSTRUKTOR dan I/O (VIA FILE EKSTERNAL) (KHUSUS AREA DENGAN EMPAT TETANGGA) ******************/
void CreateRandomPeta(Peta *PHasil, char *namafile);
/* I.S. PHasil sembarang, file dengan nama namafile terdefinisi dan siap dibaca */
/* F.S. PHasil berisi Peta yang dikonstruksi dari file Area dengan nama namafile yang dibentuk secara acak */

void CloseUnconnectedSubMapPoint(Peta *P);
/* I.S. P terdefinisi */
/* F.S. setiap titik keluar di keempat sisi P yang tidak memiliki tetangga ditutup (diganti dengan Wall) */

void FindFarthestSubPeta(Peta *P, ID Start, int jarak, int *maks, ID *IDMaks, boolean *visited);
/* I.S. P, Start, jarak, dan visited terdefinisi, maks dan IDMaks sembarang */
/* F.S. maks berisi jarak antara Subpeta terjauh dengan subpeta dengan ID start dan IDMaks berisi IDnya */

void SetBoss(Peta *P);
/* I.S. P terdefinisi */
/* F.S. SubPeta terjauh dari SubPeta(*P,1) diubah menjadi Area Boss dan semua enemy dan medicine dihapus */

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

void SavePeta(Peta P, char *namafileSubPeta, char *namafileKoneksi);
/* I.S. P, namafileSubPeta dan namafileKoneksi terdefinisi */
/* F.S. Data P tersimpan di dalam file eksternal dengan nama namafileSubPeta untuk data SubPeta dan namafileKoneksi untuk data Koneksi */

/****************** Manajemen Memori ******************/
void DealokasiPeta(Peta *P);
/* I.S. P terdefinisi */
/* F.S. Semua address di P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian semua address (Area) di P */

#endif
/* ********** Definisi TYPE MATRIKS dengan indeks integer dan elemen character ********** */

#ifndef MATRIKS_H
#define MATRIKS_H

#include "../Shared/boolean.h"
#include "../MesinKarKata/mesinkar.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define BrsMin 1
#define BrsMax 100
#define KolMin 1
#define KolMax 100

typedef int indeks; /* indeks baris, kolom */
typedef char ElType; 
typedef struct { 
	ElType Mem[BrsMax+1][KolMax+1];
    int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MATRIKS;
/* NBrsEff >= 1 dan NKolEff >= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* State MATRIKS */
extern boolean EndMATRIKS;
extern MATRIKS CMATRIKS;

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M); 
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M);
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (MATRIKS M);
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (MATRIKS M);
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (MATRIKS M);
/* Mengirimkan indeks kolom terbesar M */

/* ********** Assignment  MATRIKS ********** */
void AssignMATRIKS (MATRIKS MIn, MATRIKS * MHsl);
/* Melakukan assignment MHsl dengan MIn */

/* ********* I/O MATRIKS ************** */
void CetakMATRIKS(MATRIKS M);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */


/* ********** Load MATRIKS ********** */
void STARTMATRIKS(char *namafile);
/* I.S. : CC sembarang, file dengan nama namafile terdefinisi dan siap dibaca
   F.S. : EndMATRIKS = true, dan CC = MARK; 
          atau EndMATRIKS = false, CMATRIKS adalah MATRIKS yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir MATRIKS 
   Proses : Membuka file dengan nama namafile dan membaca ukuran MATRIKS yang akan dibaca dan membuat MATRIKS CMATRIKS dengan ukuran tersebut, kemudian mengakuisisi MATRIKS dengan procedure SalinMATRIKS */

void ADVMATRIKS();
/* I.S. : CC adalah karakter pertama MATRIKS yang akan diakuisisi 
   F.S. : CMATRIKS adalah MATRIKS terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari MATRIKS berikutnya, mungkin MARK
          Jika CC = MARK, maka EndMATRIKS = true      
   Proses : Akuisisi MATRIKS menggunakan procedure SalinMATRIKS */

void SalinMATRIKS();
/* Mengakuisisi MATRIKS, menyimpan dalam CMATRIKS  
   I.S. : CC adalah karakter pertama dari MATRIKS
   F.S. : CMATRIKS berisi MATRIKS yang sudah diakuisisi; 
          CC = MARK atau CC = baris kosong; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi. */

#endif
/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "../Shared/boolean.h"
#include "mesinkar.h"
#include <ncurses.h>

#define NMax 50

typedef struct {
	char TabKata[NMax+1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

/* KONSTRUKTOR */
void CreateKata(Kata *K, char *s);
/* I.S. : K sembarang */
/* F.S. : K berisi string s yang diubah menjadi tipe Kata */

/* I/O */
void BacaKata(Kata *K);
/* I.S. : K sembarang */
/* F.S. : K berisi kata yang merupakan input dari user */
/* Proses : Membaca input dari user sampai diinput ENTER atau BLANK */

void TulisKata (Kata K);
/*I.S. Kata terdefinisi*/
/*F.S. Kata ditampilkan ke layar*/

/* I/O KHUSUS NCURSES */
void wBacaKata(WINDOW *win, Kata *K);
/* I.S. : K sembarang */
/* F.S. : K berisi kata yang merupakan input dari user */
/* Proses : Membaca input dari user sampai diinput ENTER atau BLANK */

void wTulisKata(WINDOW *win, Kata K);
/* I.S. : K terdefinisi */
/* F.S. : K ditampilkan ke layar win */

/* MESIN KATA */
void IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA(char *namafile);
/* I.S. : CC sembarang, namafile adalah namafile eksternal yang ingin diakses 
   F.S. : EndKata = true, dan CC = MARK{} 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

/* TEST KATA */
boolean IsKataSama (Kata K1, Kata K2);
/*  Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama 
  dan urutan karakter yang menyusun kata juga sama */

boolean IsKataEmpty(Kata K);
/* Mengembalikan true jika K kosong (K.Length = 0) dan false jika tidak */


/* CONVERT KATA KE TIPE LAIN */
int KataToInteger (Kata K);
/* Prekondisi: K tedefinisi*/
/* Mengembalikan hasil konversi K menjadi bilangan bertipe integer */

#endif
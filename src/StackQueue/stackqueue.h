#ifndef _STACKQUEUE_H
#define _STACKQUEUE_H

#include "boolean.h"
#include <stdlib.h>

/* Konstanta */
#define Nil 0
#define MaxEl 20

/* Deklarasi infotype dan address */
typedef char infotype;
typedef int address;

/* Stack dengan representasi Queue */
typedef struct { infotype T[5];   /* tabel penyimpan elemen */
                 address HEAD;  /* alamat penghapusan */
                 address TAIL;  /* alamat penambahan */
} ElmtStack;

/* Type stack dengan ciri TOP : */
typedef struct { 
	ElmtStack T[MaxEl+1]; /* tabel penyimpan elemen */
	address TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Selektor */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyS (Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyS (Stack S);
/* Mengirim true jika Stack kosong*/
boolean IsFullS (Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, ElmtStack Q);
/* Menambahkan Q sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. Q menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, ElmtStack* Q);
/* Menghapus Q dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. Q adalah nilai elemen TOP yang lama, TOP berkurang 1 */

boolean IsEmptyQ (ElmtStack Q);
/* Mengirim true jika Q kosong */
boolean IsFullQ (ElmtStack Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu NBElmtQ (Q) = 4*/
int NBElmtQ (ElmtStack Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void CreateEmptyQ (ElmtStack * Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dengan
Head(Q) = Nil dan Tail(Q) = Nil */

/* *** Primitif Add/Delete *** */
void Add (ElmtStack * Q, infotype X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void Del (ElmtStack * Q, infotype * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
void RandomStack (Stack *S);
/* Proses: Mengacak urutan elemen stack yang berisi queue-queue aksi monster atau boss*/
/* I.S. Stack tidak mungkin kosong */
/* F.S. Elemen-elemen stack ditukar secara random */

void PrintStack (Stack S);
/* Proses: menampilkan urutan aksi dari tiap ronde battle pada stack*/
/* I.S. Stack tidak kosong */
/* F.S. Urutan aksi dari tiap ronde battle pada stack ditampilkan ke layar */

void PrintQueue (ElmtStack Q);
/* Proses: menampilkan urutan aksi dari salah satu ronde battle pada stack*/
/* I.S. Elemen stack tidak kosong*/
/* F.S. Urutan aksi dari salah satu ronde battle pada stack ditampilkan ke layar*/


#endif

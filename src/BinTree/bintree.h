/* ADT Pohon Biner */
/* Implementasi dengan menggunakan pointer */

#ifndef _BINTREE_H_
#define _BINTREE_H_

/* Modul lain yang digunakan : */
#include "../Shared/boolean.h"
#include <stdio.h>
#include <ncurses.h>

#define NilTree NULL

/* *** Definisi Type Pohon Biner *** */

typedef struct{
  char SkillName[25];
  char Description[100];
  boolean Unlocked;
  int SkillID;
} infoTree;

typedef struct tNode *addrNode;
typedef struct tNode {
  infoTree info;
  addrNode left;
  addrNode right;
} Node;

/* Definisi PohonBiner : */
/* Pohon Biner kosong : P = Nil */

typedef addrNode BinTree;

/* *** PROTOTYPE *** */

/* *** Selektor *** */

/* Selektor infoTree */
#define SkillName(P) (P).SkillName
#define SkillNamechar(P,i) (P).SkillName[(i)]
#define Description(P) (P).Description
#define Descriptionchar(P,i) (P).Description[(i)]
#define Unlocked(P) (P).Unlocked
#define SkillID(P) (P).SkillID

/* Selektor BinTree */
#define Akar(P) (P)->info
#define Left(P) (P)->left
#define Right(P) (P)->right

void copystring (char *dest, char *source);
/* I.S. dest sembarang, source teredefinisi */
/* F.S. dest berisi source */

/* *** Konstruktor *** */
BinTree Tree (infoTree Akar, BinTree L, BinTree R);
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (NilTree) jika alokasi gagal */

void MakeTree (infoTree Akar, BinTree L, BinTree R, BinTree *P);
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R
    jika alokasi berhasil. P = NilTree jika alokasi gagal. */

/* Manajemen Memory */
addrNode AlokNode (infoTree X);
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P,
  maka Akar(P) = X, Left(P) = NilTree, Right(P)=NilTree */
/* Jika alokasi gagal, mengirimkan NilTree */

void DealokNode (addrNode P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */

void DealokTree(BinTree *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty (BinTree P);
/* Mengirimkan true jika P adalah pohon biner kosong */
boolean IsUnerLeft (BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
boolean IsUnerRight (BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
boolean IsBiner (BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/

/* Output */
void PrintTree (BinTree P, int level, int h);
/* I.S. P terdefinisi, level adalah kedalaman dari node dengan level Akar(P) = 0, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */

void wPrintTree (WINDOW *win, BinTree P, int level, int h);
/* I.S. win, P terdefinisi, level adalah kedalaman dari node dengan level Akar(P) = 0, h adalah jarak indentasi (spasi)  (Khusus Ncurses) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */

/* *** Searching *** */
boolean SearchTree (BinTree P, int ID);
/* Mengirimkan true jika ada node dari P yang ber-ID ID */

/* FILE EKSTERNAL */
void LoadTree(char *namafile, BinTree *P);
/* namafile terdefiinsi, P P kosong */
/* P berisi data dari file eksternal dengan nama namafile */

void SaveTree(char *namafile, BinTree P);
/* I.S. namafile dan P terdefinisi */
/* F.S. file eksternal dengan nama namafile berisi data P */

void SaveTree2(FILE *fout, BinTree P, int Parent, boolean Kiri);
/* I.S. fout, P, Parent, dan Kiri terdefinisi */
/* F.S. FILE fout berisi data P sesuai format yang ada */

/* *** Operasi lain *** */
void AddDaun (BinTree *P, int ID, infoTree Y, boolean Kiri);
/* I.S. P tidak kosong, ID adalah salah satu ID daun Pohon Biner P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau 
        sebagai anak Kanan X (jika Kiri = false) */

boolean IsUnlocked(BinTree P, int ID);
/* Mengembalikan true jika Node dengan ID ID sudah di-unlocked */

void UnlockSkill(BinTree *P, int ID, infoTree *X);
/* I.S. P dan ID terdefinisi, X sembarang, infoTree dengan SkillID ID pasti ada di P */
/* F.S. Skill dengan SkillID ID di unlock, X berisi info dari skill tersebut */

void UnlockSkillRandom(BinTree *P, int chanceLeft, int chanceRight, infoTree *X, boolean *locked);
/* I.S. P, chanceLeft, dan chanceRight terdefinisi, X sembarang, locked berfungsi sebagai penanda(basis), ada skill yang belum di-unlock */
/* F.S. X berisi info dari skill yang di-unlock secara acak */

#endif
/* File: enemy.h */

#ifndef __ENEMY_H__
#define __ENEMY_H__

<<<<<<< HEAD
#include "../Shared/boolean.h"
#include "../MesinKarKata/mesinkata.h"
#include "../StackQueue/stackqueue.h"
typedef struct { 
	Kata e_name;
	int e_hp;
	int e_str;
	int e_def;
	int e_exp;
	Stack e_attack;
} Enemy;

/*  Kamus Umum */
#define IdxMax 50
/* Indeks maksimum array, sekaligus ukuran maksimum array dalam C */
#define IdxMin 1
/* Indeks minimum array */
#define IdxUndef -999 
/* Indeks tak terdefinisi*/

typedef int IdxType;  /* type indeks */
typedef Kata ElType;   /* type elemen tabel */
typedef struct { 
	ElType TI[IdxMax+1]; /* memori tempat penyimpan elemen (container) */
	int Neff; /* >=0, banyaknya elemen efektif */
} TabInt;

/*SELEKTOR*/
#define e_name(TEnemy) (TEnemy).e_name
#define e_hp(TEnemy) (TEnemy).e_hp
#define e_str(TEnemy) (TEnemy).e_str
#define e_def(TEnemy) (TEnemy).e_def
#define e_exp(TEnemy) (TEnemy).e_exp
#define e_attack(TEnemy) (TEnemy).e_attack

#define Neff(T)   (T).Neff
#define TI(T)     (T).TI
#define Elmt(T,i) (T).TI[(i)]

int WordToInteger (Kata CKata);
/*Prekondisi: kata tedefinisi*/
/*Konversi kata menjadi bilangan bertipe integer*/

void PrintWord (Kata CKata);
/*I.S. Kata terdefinisi*/
/*F.S. Kata ditampilkan ke layar*/

void LoadNamaEnemy (TabInt *NEnemy);
/*I.S. File eksternal nama-nama enemy terdefinisi*/
/*F.S. Tabel yang berisi nama-nama enemy terdefinisi*/

void LoadFileEnemy (Enemy *TEnemy,char *filename, char in);
/*I.S. File eksternal berisi informasi dan pola serang musuh*/
/*F.S. Tipe bentukan Enemy sudah terisi oleh informasi dan pola serang musuh dari file eksternal*/

void AttackEnemy (Enemy *TEnemy, ElmtStack *Q);
/*I.S. Tipe bentukan enemy telah terdefinisi*/
/*F.S. Tipe bentukan enemy telah diupdate dan mengeluarkan char pola serang musuh yang pertama*/

void PrintEnemy (Enemy TEnemy);
/*I.S. Tipe bentukan enemy terdefinisi*/
/*F.S. Menampilkan isi tipe bentukan enemy ke layar*/

int Damage (int str, int def,int base);
/*Prekondisi: Strength, defense, dan base untuk battle terdefinisi*/
/*Menghitung besarnya damage pada saat battle*/

#endif

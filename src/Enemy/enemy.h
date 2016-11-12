/* File: enemy.h */

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "boolean.h"
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

/*SELEKTOR*/
#define e_name(TEnemy) (TEnemy).e_name
#define e_hp(TEnemy) (TEnemy).e_hp
#define e_str(TEnemy) (TEnemy).e_str
#define e_def(TEnemy) (TEnemy).e_def
#define e_exp(TEnemy) (TEnemy).e_exp
#define e_attack(TEnemy) (TEnemy).e_attack

int WordToInteger (Kata CKata);
/*Prekondisi: kata tedefinisi*/
/*Konversi kata menjadi bilangan bertipe integer*/

void LoadFileEnemy (Enemy *TEnemy,char *filename);
/*I.S. File eksternal berisi informasi dan pola serang musuh*/
/*F.S. Tipe bentukan Enemy sudah terisi oleh informasi dan pola serang musuh dari file eksternal*/

void AttackEnemy (Enemy *TEnemy, ElmtStack *Q);
/*I.S. Tipe bentukan enemy telah terdefinisi*/
/*F.S. Tipe bentukan enemy telah diupdate dan mengeluarkan char pola serang musuh yang pertama*/

void LoadEnemy (Enemy *TDementor, Enemy *TCentaur, Enemy *TDobby, Enemy *TGoblin, Enemy *TThrestral);
/*I.S. File eksternal untuk masing-masing enemy terdefinisi*/
/*F.S. Load masing-masing file eksternal ke tipe bentukan untuk masing-masing enemy*/

void PrintEnemy (Enemy TEnemy);
/*I.S. Tipe bentukan enemy terdefinisi*/
/*F.S. Menampilkan isi tipe bentukan enemy ke layar*/

#endif

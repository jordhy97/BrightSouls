/* File: ADT Enemy */

#include "enemy.h"
#include <stdio.h>

int WordToInteger (Kata CKata)
/*Prekondisi: kata tedefinisi*/
/*Konversi kata menjadi bilangan bertipe integer*/
{
	int bil, X, i;
	bil = 0;
	for (i = 1; i <= CKata.Length; i++)
	{
		X = (CKata.TabKata[i] - '0');
		bil = (bil * 10) + X;
	}
	return bil;
}

void LoadFileEnemy (Enemy *TEnemy,char *filename)
/*I.S. File eksternal berisi informasi dan pola serang musuh*/
/*F.S. Tipe bentukan Enemy sudah terisi oleh informasi dan pola serang musuh dari file eksternal*/
{
	ElmtStack Q;
	int i, j,k;
	CreateEmptyS(&e_attack(*TEnemy));
	STARTKATA(filename);
	e_name(*TEnemy) = CKata;
	ADVKATA();
	e_hp(*TEnemy) = WordToInteger(CKata);
	ADVKATA();
	e_str(*TEnemy) = WordToInteger(CKata);
	ADVKATA();
	e_def(*TEnemy) = WordToInteger(CKata);
	ADVKATA();
	e_exp(*TEnemy) = WordToInteger(CKata);
	for (j = 1; j <= 10; j++)
	{
		CreateEmptyQ(&Q);
		for (i = 1; i <= 4; i++)
		{
			ADVKATA();
			Add(&Q,CKata.TabKata[1]);
		}
		Push(&e_attack(*TEnemy),Q);
	}
}

void AttackEnemy (Enemy *TEnemy, ElmtStack *Q)
/*I.S. Tipe bentukan enemy telah terdefinisi*/
/*F.S. Tipe bentukan enemy telah diupdate dan mengeluarkan char pola serang musuh yang pertama*/
{
	CreateEmptyQ(Q);
	/*prosedur untuk random stack*/
	Pop(&e_attack(*TEnemy),Q);
}

void LoadEnemy (Enemy *TDementor, Enemy *TCentaur, Enemy *TDobby, Enemy *TGoblin, Enemy *TThrestral)
/*I.S. File eksternal untuk masing-masing enemy terdefinisi*/
/*F.S. Load masing-masing file eksternal ke tipe bentukan untuk masing-masing enemy*/
{
	LoadFileEnemy(TDementor,"enemy_dementor.txt");
	LoadFileEnemy(TCentaur,"enemy_centaur.txt");
	LoadFileEnemy(TDobby,"enemy_dobby.txt");
	LoadFileEnemy(TGoblin,"enemy_goblin.txt");
	LoadFileEnemy(TThrestral,"enemy_threstral.txt");
}

void PrintEnemy (Enemy TEnemy)
/*I.S. Tipe bentukan enemy terdefinisi*/
/*F.S. Menampilkan isi tipe bentukan enemy ke layar*/
{
	int i;
	for (i = 1; i <= e_name(TEnemy).Length; i++)
	{
		printf("%c",e_name(TEnemy).TabKata[i]);
	}
	printf("\n");
	printf("%d\n",e_hp(TEnemy));
	printf("%d\n",e_str(TEnemy));
	printf("%d\n",e_def(TEnemy));
	printf("%d\n",e_exp(TEnemy));
	PrintStack(e_attack(TEnemy));
}

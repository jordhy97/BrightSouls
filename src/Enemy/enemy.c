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

void PrintWord (Kata CKata)
/*I.S. Kata terdefinisi*/
/*F.S. Kata ditampilkan ke layar*/
{
	int i;
	for (i = 1; i <= CKata.Length; i++)
	{
		printf("%c",CKata.TabKata[i]);
	}
}

void LoadNamaEnemy (TabInt *NEnemy)
/*I.S. File eksternal nama-nama enemy terdefinisi*/
/*F.S. Tabel yang berisi nama-nama enemy terdefinisi*/
{
	int i;
	i = 0;
	STARTKATA("namaenemy.txt");
	if (!EndKata)
	{
		do
		{
			i++;
			Elmt(*NEnemy,i) = CKata;
			ADVKATA();
		}
		while (!EndKata);
	}
	Neff(*NEnemy) = i;
}

void LoadFileEnemy (Enemy *TEnemy,char *filename, char in)
/*I.S. File eksternal berisi informasi dan pola serang musuh, serta char in yang memuat inisial untuk bos atau enemy, 'b' untuk bos dan 'e' untuk enemy*/
/*F.S. Tipe bentukan Enemy sudah terisi oleh informasi dan pola serang musuh dari file eksternal*/
{
	ElmtStack Q;
	int i,j,k,nb;
	if (in == 'b')
	{
		nb = 20;
	}
	else if (in == 'e')
	{
		nb = 10;
	}
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
	for (j = 1; j <= nb; j++)
	{
		CreateEmptyQ(&Q);
		for (i = 1; i <= 4; i++)
		{
			ADVKATA();
			Add(&Q,CKata.TabKata[1]);
		}
		Push(&e_attack(*TEnemy),Q);
	}
	RandomStack(&e_attack(*TEnemy));
}

void AttackEnemy (Enemy *TEnemy, ElmtStack *Q)
/*I.S. Tipe bentukan enemy telah terdefinisi*/
/*F.S. Tipe bentukan enemy telah diupdate dan mengeluarkan char pola serang musuh yang pertama*/
{
	CreateEmptyQ(Q);
	Pop(&e_attack(*TEnemy),Q);
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

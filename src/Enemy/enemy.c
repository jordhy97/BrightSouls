/* File: ADT Enemy */

#include "enemy.h"
#include <stdio.h>

void LoadNamaEnemy (TabEn *NEnemy, char *namafile)
/*I.S. File eksternal nama-nama enemy terdefinisi*/
/*F.S. Tabel yang berisi nama-nama enemy terdefinisi*/
{
	/* KAMUS LOKAL */
	int i;

	/* ALGORITMA */
	i = 0;
	STARTKATA(namafile);
	if(!EndKata)
	{
		do
		{
			i++;
			ElmtTabEn(*NEnemy,i) = CKata;
			ADVKATA();
		}
		while (!EndKata);
	}
	Neff(*NEnemy) = i;
}

void LoadFileEnemy (Enemy *TEnemy, char *filename, char in)
/*I.S. File eksternal berisi informasi dan pola serang musuh, serta char in yang memuat inisial untuk bos atau enemy, 'b' untuk bos dan 'e' untuk enemy*/
/*F.S. Tipe bentukan Enemy sudah terisi oleh informasi dan pola serang musuh dari file eksternal*/
{
	ElmtStack Q;
	int i,j,nb;
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
	e_hp(*TEnemy) = KataToInteger(CKata);
	ADVKATA();
	e_str(*TEnemy) = KataToInteger(CKata);
	ADVKATA();
	e_def(*TEnemy) = KataToInteger(CKata);
	ADVKATA();
	e_exp(*TEnemy) = KataToInteger(CKata);
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
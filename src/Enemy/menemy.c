/* File: Driver untuk ADT Enemy */

#include <stdio.h>
#include "enemy.h"

int main ()
{
	/* KAMUS */
	int i;
	ElmtStack Q;
	Enemy T1,T2,T3;
	TabEn EnemyList;

	/* ALGORITMA */
	printf("TESTING Enemy\n\n");

	/*load dan print file eksternal*/
	LoadFileEnemy(&T1,"../../src/Enemy/enemy_dobby.txt",'e');
	LoadFileEnemy(&T2,"../../src/Enemy/enemy_threstral.txt",'e');
	LoadFileEnemy(&T3,"../../src/Enemy/bowtruckle.txt",'b');
	LoadNamaEnemy (&EnemyList, "../../src/Enemy/namaenemy.txt");
	PrintEnemy(T1);
	printf("\n\n");
	PrintEnemy(T2);
	printf("\n\n");
	PrintEnemy(T3);
	printf("\n\n");
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sebelum dan sesudahnya*/
	printf("Stack Dobby : \n");
	PrintStack(e_attack(T1));
	AttackEnemy(&T1,&Q);
	printf("Pop Dobby 1 : "); 
	PrintQueue(Q,1,2);
	printf("\n");
	PrintStack(e_attack(T1));
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sesudahnya*/
	AttackEnemy(&T1,&Q);
	printf("Pop Dobby 2 : "); 
	PrintQueue(Q,1,3);
	printf("\n");
	PrintStack(e_attack(T1));
	printf("\n");
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sebelum dan sesudahnya*/
	printf("\nStack Threstral : \n");
	PrintStack(e_attack(T2));
	AttackEnemy(&T2,&Q);
	printf("Pop Threstral : "); 
	PrintQueue(Q,2,4);
	printf("\n");
	PrintStack(e_attack(T2));
	printf("\n\n");
	
	/* EnemyList */
	printf("EnemyList:\n");
	for(i = 1; i <= Neff(EnemyList); i++)
	{
		TulisKata(ElmtTabEn(EnemyList,i));
		printf("\n");
	}
	printf("\n");
	return 0;
}

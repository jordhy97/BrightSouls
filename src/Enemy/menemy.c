/* File: Driver untuk ADT Enemy */

#include <stdio.h>
#include "enemy.h"

int main ()
{
	ElmtStack Q;
	int i;
	Enemy T1,T2,T3;
	TabEn NEnemy;
	
	/*load dan print file eksternal*/
	LoadFileEnemy(&T1,"elf.txt",'e');
	LoadFileEnemy(&T2,"griffin.txt",'e');
	LoadFileEnemy(&T3,"bowtruckle.txt",'b');
	PrintEnemy(T1);
	printf("\n");
	PrintEnemy(T2);
	printf("\n");
	PrintEnemy(T3);
	printf("\n");
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sebelum dan sesudahnya*/
	printf("Stack Elf : \n");
	PrintStack(e_attack(T1));
	AttackEnemy(&T1,&Q);
	printf("Pop Elf 1 : "); 
	PrintQueue(Q,1,2);
	printf("\n");
	PrintStack(e_attack(T1));
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sesudahnya*/
	AttackEnemy(&T1,&Q);
	printf("Pop Elf 2 : "); 
	PrintQueue(Q,1,3);
	printf("\n");
	PrintStack(e_attack(T1));
	printf("\n");
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sebelum dan sesudahnya*/
	printf("Stack Griffin : \n");
	PrintStack(e_attack(T2));
	AttackEnemy(&T2,&Q);
	printf("Pop Griffin : "); 
	PrintQueue(Q,2,4);
	printf("\n");
	PrintStack(e_attack(T2));
	printf("\n");
	
	return 0;
}

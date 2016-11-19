/* File: Driver untuk ADT Enemy */

#include <stdio.h>
#include "enemy.h"

int main ()
{
	ElmtStack Q;
	int i;
	Enemy TDementor, TCentaur, TDobby, TGoblin, TThrestral;
	TabInt NEnemy;
	
	/*load dan print file eksternal*/
	LoadFileEnemy(&TDementor,"enemy_dementor.txt",'e');
	LoadFileEnemy(&TCentaur,"enemy_centaur.txt",'e');
	LoadFileEnemy(&TDobby,"enemy_dobby.txt",'e');
	LoadFileEnemy(&TGoblin,"enemy_goblin.txt",'e');
	LoadFileEnemy(&TThrestral,"enemy_threstral.txt",'e');
	PrintEnemy(TDementor);
	printf("\n");
	PrintEnemy(TCentaur);
	printf("\n");
	PrintEnemy(TDobby);
	printf("\n");
	PrintEnemy(TGoblin);
	printf("\n");
	PrintEnemy(TThrestral);
	printf("\n");
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sebelum dan sesudahnya*/
	printf("Stack Dementor : \n");
	PrintStack(e_attack(TDementor));
	AttackEnemy(&TDementor,&Q);
	printf("Pop dementor : "); 
	PrintQueue(Q,1,2);
	printf("\n");
	PrintStack(e_attack(TDementor));
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sesudahnya*/
	AttackEnemy(&TDementor,&Q);
	printf("Pop dementor : "); 
	PrintQueue(Q,1,3);
	printf("\n");
	PrintStack(e_attack(TDementor));
	printf("\n");
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sebelum dan sesudahnya*/
	printf("Stack Centaur : \n");
	PrintStack(e_attack(TCentaur));
	AttackEnemy(&TCentaur,&Q);
	printf("Pop centaur : "); 
	PrintQueue(Q,2,4);
	printf("\n");
	PrintStack(e_attack(TCentaur));
	printf("\n");
	
	/*load dan print file eksternal yang berisi nama-nama enemy*/
	LoadNamaEnemy(&NEnemy);
	for (i=1;i<=Neff(NEnemy);i++)
	{
		PrintWord(Elmt(NEnemy,i));
		printf("\n");
	}
	return 0;
}

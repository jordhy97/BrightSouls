/* File: Driver untuk ADT Enemy */

#include <stdio.h>
#include "enemy.h"

int main ()
{
	ElmtStack Q;
	Enemy TDementor, TCentaur, TDobby, TGoblin, TThrestral;
	/*load dan print file eksternal*/
	LoadEnemy(&TDementor, &TCentaur, &TDobby, &TGoblin, &TThrestral);
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
	PrintStack(e_attack(TDementor));
	AttackEnemy(&TDementor,&Q);
	printf("Pop : "); PrintQueue(Q);
	printf("\n");
	PrintStack(e_attack(TDementor));
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sesudahnya*/
	AttackEnemy(&TDementor,&Q);
	printf("Pop : "); PrintQueue(Q);
	printf("\n");
	PrintStack(e_attack(TDementor));
	printf("\n");
	
	/*mengeluarkan 1 buah queue elemen stack secara random dan di-print, mencetak stack sebelum dan sesudahnya*/
	PrintStack(e_attack(TCentaur));
	AttackEnemy(&TCentaur,&Q);
	printf("Pop : "); PrintQueue(Q);
	printf("\n");
	PrintStack(e_attack(TCentaur));
	return 0;
}

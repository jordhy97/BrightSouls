/* File: Driver untuk ADT Mesin Kata */

#include <stdio.h>
#include "mesinkata.h"

int main()
{
	/* KAMUS */
	Kata K, TEST;
	int converted;

	/* ALGORITMA */
	printf("Testing Mesinkata and mesinkar\n\n");
	printf("Reading Kata from testmesinkata.txt...\n");
	STARTKATA("../../src/MesinKarKata/testmesinkata.txt");
	while (!EndKata)
	{
		TulisKata(CKata);
		printf("\n");		
	    ADVKATA();
	}
	printf("\n");

	printf("Testing BacaKata, CreateKata, and IsKataSama\n");
    printf("Input Kata: ");
    BacaKata(&K);
    if(!IsKataEmpty(K))
    {
    	printf("Kata not empty\n");
    }
    CreateKata(&TEST, "TEST");
    if(IsKataSama(K,TEST))
    {
    	printf("Kata yang dimasukkan adalah TEST\n");
    }
    else
    {
    	printf("Kata yang dimasukkan bukan TEST\n");
    }

    printf("\nTesting KataToInteger\n");
    printf("Input angka: ");
    BacaKata(&K);
    converted = KataToInteger(K);
    printf("Converted to int: %d\n", converted);
	return 0;
}
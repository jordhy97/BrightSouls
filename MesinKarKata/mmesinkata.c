#include <stdio.h>
#include "mesinkata.h"

int main(){
	Kata K;
	int i, N;
	STARTKATA("test.txt");
	while (!EndKata){
		i=1;
		while(i<=CKata.Length){
			printf("%c", CKata.TabKata[i]);
			i++;
		}
		printf(" ");		
	    ADVKATA();
	}
	printf("\n");

    BacaKata(&K);
	
	N=0;
	EndKata = false;
	STARTKATA("test.txt");
	while(!EndKata){
		if(IsKataSama(K,CKata)){
			N++;
		}
		ADVKATA();
	}

	printf("%d\n", N);
}
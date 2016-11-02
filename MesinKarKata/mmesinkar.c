#include <stdio.h>
#include "mesinkata.h"

int main(){
	Kata KataWHILE;
	int i, NWHILE;
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

    KataWHILE.TabKata[1] = 'W';
	KataWHILE.TabKata[2] = 'H';
	KataWHILE.TabKata[3] = 'I';
	KataWHILE.TabKata[4] = 'L';
	KataWHILE.TabKata[5] = 'E';
	KataWHILE.Length = 5;
	NWHILE = 0;
	
	EndKata = false;
	STARTKATA("test.txt");
	while(!EndKata){
		if(IsKataSama(KataWHILE,CKata)){
			NWHILE++;
		}
		ADVKATA();
	}

	printf("%d\n", NWHILE);
}
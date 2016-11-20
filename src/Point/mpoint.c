#include <stdio.h>
#include "point.h"

int main(){
	/* KAMUS */
	POINT P;

	/* ALGORITMA */
	printf("TESTING POINT\n\n");
	printf("Input POINT P:\n");
	BacaPOINT(&P);
	printf("P: ");
	TulisPOINT(P);
	printf("\n");
	SetPOINT(&P, PlusDelta(P, 1, 1));
	printf("P setelah digeser (1,1): ");
	TulisPOINT(P);
	printf("\n");
	return 0;
}
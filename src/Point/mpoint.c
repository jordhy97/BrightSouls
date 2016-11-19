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
	SetPOINT(&P, NextX(P));
	printf("P setelah digeser sejauh 1 ke kanan: ");
	TulisPOINT(P);
	printf("\n");
	SetPOINT(&P, NextY(P));
	printf("P setelah digeser lagi sejauh 1 ke atas: ");
	TulisPOINT(P);
	printf("\n");
	return 0;
}
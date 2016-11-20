 /* File 	 : mjam.c 					*/
/* Topik	 : ADT JAM					*/

#include "jam.h"
#include <stdio.h>

int main()
{
	/* KAMUS */
	JAM J1, J2, Jmin, Jmax;
	int N, i;

	/* ALGORITMA */
	printf("TESTING JAM\n\n");
	printf("Jam Sekarang: ");
	GetCurrentJAM(&J1);
	TulisJAM(J1);
	printf("\n");
	printf("dalam detik: %ld\n", JAMToDetik(J1));
	printf("\nInput J2: ");
	BacaJAM(&J2);
	printf("Jam 2: ");
	TulisJAM(J2);
	printf("\n");
	printf("Durasi dari Jam sekarang ke Jam 2: %ld\n", Durasi(J1,J2));
	printf("dalam Jam: ");
	TulisJAM(DetikToJAM(Durasi(J1,J2)));
	printf("\n");
	printf("Jam Sekarang + Jam2: ");
	TulisJAM(AddJAM(J1,J2));
	printf("\n");
   	return 0;
}
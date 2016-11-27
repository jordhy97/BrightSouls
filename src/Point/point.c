/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada point.h */

#include "point.h"
#include <stdio.h>

POINT MakePOINT (int X, int Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{
	/* KAMUS LOKAL */
	POINT P;

	/* ALGORITMA */
	Absis(P) = X;
	Ordinat(P) = Y;
	return P;
}

void SetPOINT(POINT *P1, POINT P2)
/* I.S. P1 sembarang, P2 terdefinisi */
/* F.S. P1 berisi P2 */
{
	/* ALGORITMA */
	Absis(*P1) = Absis(P2);
	Ordinat(*P1) = Ordinat(P2);
}
          
/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */  
POINT PlusDelta (POINT P, int deltaX, int deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
	/* ALGORITMA */
	return MakePOINT(Absis(P) + deltaX, Ordinat(P) + deltaY);;
}
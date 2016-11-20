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

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPOINT (POINT * P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
{
	/* KAMUS LOKAL */
	int X, Y;

	/* ALGORITMA */
	scanf("%d %d", &X, &Y);
	*P = MakePOINT(X,Y);
}

void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang, atau di antaranya */
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
{
	/* ALGORITMA */
	printf("(%d,%d)", Absis(P), Ordinat(P));
}
                                              
/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */  
POINT PlusDelta (POINT P, int deltaX, int deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
	/* ALGORITMA */
	return MakePOINT(Absis(P) + deltaX, Ordinat(P) + deltaY);;
}
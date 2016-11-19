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
POINT NextX (POINT P)
/* Mengirim salinan P dengan absis ditambah satu */              
{
	/* KAMUS LOKAL */
	POINT Pcopy;

	/* ALGORITMA */
	Absis(Pcopy) = Absis(P) + 1;
	Ordinat(Pcopy) = Ordinat(P);
	return Pcopy;

}

POINT NextY (POINT P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{
	/* KAMUS LOKAL */
	POINT Pcopy;

	/* ALGORITMA */
	Absis(Pcopy) = Absis(P);
	Ordinat(Pcopy) = Ordinat(P) + 1;
	return Pcopy;

}
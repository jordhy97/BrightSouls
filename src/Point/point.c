//NIM				: 13515145
//Nama				: Erfandi Suryo Putra
//Tanggal			: 1 September 2016
//Topik praktikum	: Modularisasi

#include "point.h"
#include <stdio.h>

POINT MakePOINT (int X, int Y)
/* Membentuk sebuah POINT dari komponen-komponennya */


{
	POINT P;

	Absis(P) = X;
	Ordinat(P) = Y;
	return P;

}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
POINT NextX (POINT P)
/* Mengirim salinan P dengan absis ditambah satu */              
{
	POINT Pcopy;
	Absis(Pcopy) = Absis(P) + 1;
	Ordinat(Pcopy) = Ordinat(P);
	return Pcopy;

}

POINT NextY (POINT P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{
	POINT Pcopy;
	Absis(Pcopy) = Absis(P);
	Ordinat(Pcopy) = Ordinat(P) + 1;
	return Pcopy;

}

POINT PlusDelta (POINT P, int deltaX, int deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
	POINT Pcopy;
	Absis(Pcopy) = Absis(P) + deltaX;
	Ordinat(Pcopy) = Ordinat(P) + deltaY;
	return Pcopy;

}


void Geser (POINT *P, int deltaX, int deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{
	*P=MakePOINT(Absis(*P)+deltaX, Ordinat(*P)+deltaY);

}

void GeserKeSbX (POINT *P)
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
{
	*P=MakePOINT(Absis(*P), 0);

}

void GeserKeSbY (POINT *P)
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
{
	*P=MakePOINT(0, Ordinat(*P));

}
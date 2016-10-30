/* NIM/Nama     : 13515004/Jordhy Fernando */
/* Nama file    : mmatriks.c               */
/* Tanggal      : 29 Oktober 2016          */
/* Deskripsi    : Driver untuk matriks.c   */

#include <stdio.h>
#include "matriks.h"

void CetakMATRIKS(MATRIKS M);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */

int main()
{
	int baris, kol;
	STARTMATRIKS("coba.txt");
	while(!EndMATRIKS)
	{
		CetakMATRIKS(CMATRIKS);
		ADVMATRIKS();
		printf("\n");
	}
	return 0;
}

void CetakMATRIKS(MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
{
	/* KAMUS */
	indeks i, j;

	/* ALGORITMA */
	for(i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++)
	{
		for(j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++)
		{
			printf("%c", Elmt(M,i,j));
			if(j != GetLastIdxKol)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}
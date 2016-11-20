#include "stackqueue.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyS (Stack *S) {
/* I.S. S sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */
	/* ALGORITMA */
	Top(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyS (Stack S) {
/* Mengirim true jika Stack kosong*/
	/* ALGORITMA */
	return (Top(S)==Nil);
}

boolean IsFullS (Stack S) {
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
	/* ALGORITMA */
	return(Top(S)==MaxEl);
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, ElmtStack Q) {
/* Menambahkan Q sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. Q menjadi TOP yang baru,TOP bertambah 1 */
	/* ALGORITMA */
	Top(*S)++; 
	InfoTop(*S) = Q;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, ElmtStack* Q) {
/* Menghapus Q dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. Q adalah nilai elemen TOP yang lama, TOP berkurang 1 */
	/* ALGORITMA */
	*Q = InfoTop(*S); 
	Top(*S)--;
}

boolean IsEmptyQ (ElmtStack Q) {
/* Mengirim true jika Q kosong */
	/* ALGORITMA */
	return ((Head(Q)==Nil) && (Tail(Q)==Nil));
}

boolean IsFullQ (ElmtStack Q) {
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu NBElmtQ (Q) = 4*/
	/* ALGORITMA */
	return(NBElmtQ (Q) == 4);
}

int NBElmtQ (ElmtStack Q) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
	/* ALGORITMA */
	if (IsEmptyQ(Q)) {
		return (0);
	}
	else {
		if (Tail(Q)>=Head(Q)) {
			return(Tail(Q)-Head(Q)+1);
		}
		else {
			return(4-Head(Q)+1+Tail(Q));
		}
	}
}

/* *** Kreator *** */
void CreateEmptyQ (ElmtStack * Q) {
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dengan
Head(Q) = Nil dan Tail(Q) = Nil */
	/* ALGORITMA */
	Head(*Q) = Nil;
	Tail(*Q) = Nil;
}


/* *** Primitif Add/Delete *** */
void Add (ElmtStack * Q, infotype X) {
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
	/* ALGORITMA */
	if (IsEmptyQ(*Q)) {
		Head(*Q) = 1;
		Tail(*Q) = 1;
		InfoTail(*Q) = X;
	}
	else {
		Tail(*Q)++;
		if (Tail(*Q) > 4) {
			Tail(*Q) = 1;
		}
		InfoTail(*Q) = X;
	}
}

void Del (ElmtStack * Q, infotype * X) {
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
	/* ALGORITMA */
	*X = InfoHead(*Q);
	if (NBElmtQ(*Q) == 1) {
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}
	else {
		Head(*Q)++;
		if (Head(*Q) > 4) {
			Head(*Q) = 1;
		}
	}
}

void RandomStack (Stack *S) {
/* Proses: Mengacak urutan elemen stack yang berisi queue-queue aksi monster atau boss*/
/* I.S. Stack tidak mungkin kosong */
/* F.S. Elemen-elemen stack ditukar secara random */
	/* KAMUS LOKAL */
	int x,y,i;
	ElmtStack temp;

	/* ALGORITMA */
	srand(time(NULL));
	for (i=0; i<Top(*S); i++) {
		x = rand() % Top(*S) +1;
		y = rand() % Top(*S) +1;
		temp = (*S).T[x];
		(*S).T[x] = (*S).T[y];
		(*S).T[y] = temp;
	}	
}

void PrintStack (Stack S) {
/* Proses: menampilkan urutan aksi dari tiap ronde battle pada stack*/
/* I.S. Stack tidak kosong */
/* F.S. Urutan aksi dari tiap ronde battle pada stack ditampilkan ke layar */
	/* KAMUS LOKAL */
	ElmtStack Q;
	int i, y, z;

	/* ALGORITMA */
	i = 1;
	srand(time(NULL));
	while(!IsEmptyS(S)) {
		printf("[%d] ",i);
		Pop(&S, &Q);
		z = rand() % 4 + 1;
		y = rand() % 4 + 1;
		while (y == z) {
			z = rand() % 4 + 1;
			y = rand() % 4 + 1;
		} 
		PrintQueue(Q, y, z);
		printf("\n");
		i++;	
	}
}

void PrintQueue (ElmtStack Q, int pos1, int pos2) {
/* Proses: menampilkan urutan aksi dari salah satu ronde battle pada stack*/
/* I.S. Elemen stack tidak kosong*/
/* F.S. Urutan aksi dari salah satu ronde battle pada stack ditampilkan ke layar dengan dua aksi di pos1 dan pos 2 ditutupi oleh '#' */
	/* KAMUS LOKAL */
	infotype X;

	/* ALGORITMA */
	
	while (!IsEmptyQ(Q)) {
		if (Head(Q)==pos1 || Head(Q)==pos2) {
			Del(&Q,&X);
			printf("# ");
		}
		else {
			Del(&Q,&X);
			printf("%c ",X);
		}
	}
}

void PrintQueueNR (ElmtStack Q)
/* Proses: menampilkan urutan aksi dari salah satu ronde battle*/
/* I.S. Stack tidak kosong */
/* F.S. Urutan aksi dari salah satu ronde battle pada stack ditampilkan ke layar*/
{
	infotype X;
	while (!IsEmptyQ(Q))
	{
		Del(&Q,&X);
		if (!IsEmptyQ(Q))
		{
			printf("%c ",X);
		}
		else
		{
			printf("%c",X);	
		}
	}
}

void PrintQueueBattleE (ElmtStack Q,int i, int y, int z)
/* Proses: menampilkan urutan aksi enemy dari salah satu ronde battle pada stack pada saat kalkulasi damage*/
/* I.S. Stack tidak kosong */
/* F.S. Urutan aksi enemy dari salah satu ronde battle pada stack ditampilkan ke layar pada saat kalkulasi damage*/
{
	infotype X;
	int j;
	while (!IsEmptyQ(Q))
	{
		j++;
		if (NBElmtQ(Q) == (4-(i-1)))
		{
			printf(">");
		}
		Del(&Q,&X);
		if (!IsEmptyQ(Q))
		{
			if (j==y || j==z)
			{
				if (j <= i)
				{
					printf("%c ",X);
				}
				else
				{
					printf("# ");
				}
			}
			else
			{
				printf("%c ",X);
			}
		}
		else
		{
			if (j==y || j==z)
			{
				if (j <= i)
				{
					printf("%c",X);
				}
				else
				{
					printf("#");
				}
			}
			else
			{
				printf("%c",X);
			}
		}
	}
}

void PrintQueueBattleP (ElmtStack Q,int i)
/* Proses: menampilkan urutan aksi dari salah satu ronde battle pada saat kalkulasi damage*/
/* I.S. Stack tidak kosong */
/* F.S. Urutan aksi player dari salah satu ronde battle ditampilkan ke layar pada saat kalkulasi damage*/
{
	infotype X;
	while (!IsEmptyQ(Q))
	{
		if (NBElmtQ(Q) == (4-(i-1)))
		{
			printf(">");
		}
		Del(&Q,&X);
		if (!IsEmptyQ(Q))
		{
			printf("%c ",X);
		}
		else
		{
			printf("%c",X);
		}
	}
}

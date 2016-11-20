/* File 	 : jam.c 					*/
/* Deskripsi : Realisasi/ kode program dari semua prototype yg didefinisikan pada jam.h */

#include "jam.h"
#include <stdio.h>
#include <time.h>

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
boolean IsJAMValid (int H, int M, int S)
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
{
	/* ALGORITMA */
	return ((H >= 0 && H <= 23) && (M >= 0 && M <= 59) && (S >= 0 && S <= 59));
}

JAM MakeJAM (int HH, int MM, int SS)
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
{
	/* KAMUS LOKAL */
	JAM J;

	/* ALGORITMA */
	Hour(J) = HH;
	Minute(J) = MM;
	Second(J) = SS;
	return J;
}

void SetJAM(JAM *J1, JAM J2)
/* I.S. J1 sembarang, J2 terdefinisi */
/* F.S. J1 berisi J2 */
{
	/* ALGORITMA */
	Hour(*J1) = Hour(J2);
	Minute(*J1) = Minute(J2);
	Second(*J1) = Second(J2);
}

/* *** Selektor *** */
void GetCurrentJAM(JAM *J)
/* I.S. J sembarang */
/* F.S. J berisi JAM sekarang */
{
	/* KAMUS LOKAL */
	time_t t;
	int H, M, S;
	char *currtime;

	/* ALGORTIMA */
    time(&t);
    currtime = ctime(&t);
    H = ((currtime[11] - '0') * 10 + (currtime[12] - '0'));
    M = ((currtime[14] - '0') * 10 + (currtime[15] - '0'));
    S = ((currtime[17] - '0') * 10 + (currtime[18] - '0'));
    *J = MakeJAM(H,M,S);
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J)
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
{
	/* KAMUS LOKAL */
	int H, M, S;

	/* ALGORITMA */
	scanf("%d %d %d", &H, &M, &S);
	while(!IsJAMValid(H, M, S))
	{
		printf("Jam tidak valid\n");
		scanf("%d %d %d", &H, &M, &S);
	}
	*J = MakeJAM(H, M, S);
}

void TulisJAM (JAM J)
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
{
	/* ALGORITMA */
	if(Hour(J) < 10)
	{
		printf("0%d:", Hour(J));
	}
	else
	{
		printf("%d:", Hour(J));	
	}
	if(Minute(J) < 10)
	{
		printf("0%d:", Minute(J));
	}
	else
	{
		printf("%d:", Minute(J));	
	}
	if(Second(J) < 10)
	{
		printf("0%d", Second(J));
	}
	else
	{
		printf("%d", Second(J));	
	}
}


/***** KHUSUS NCURSES *****/
void wTulisJAM (WINDOW *win, JAM J)
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar win dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
{
	/* ALGORITMA */
	if(Hour(J) < 10)
	{
		wprintw(win, "0%d:", Hour(J));
	}
	else
	{
		wprintw(win, "%d:", Hour(J));	
	}
	if(Minute(J) < 10)
	{
		wprintw(win, "0%d:", Minute(J));
	}
	else
	{
		wprintw(win, "%d:", Minute(J));	
	}
	if(Second(J) < 10)
	{
		wprintw(win, "0%d", Second(J));
	}
	else
	{
		wprintw(win, "%d", Second(J));	
	}
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToDetik (JAM J)
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
{
	/* ALGORITMA */
	return (3600 * Hour(J) + 60 * Minute(J) + Second(J));
}

JAM DetikToJAM (long N)
/* Mengirim  konversi detik ke JAM */
{
	/* KAMUS LOKAL */
	int sisa;
	JAM J;
	
	/* ALGORITMA */
	Hour(J) = N / 3600;
	sisa = N % 3600;
	Minute(J) = sisa / 60;
	Second(J) = sisa % 60;
	return J;
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Operator aritmatika JAM *** */
long Durasi (JAM JAw, JAM JAkh)
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
{
	/* KAMUS LOKAL */

	long d1, d2;
	/* ALGORITMA */
	d1 = JAMToDetik(JAw);
	d2 = JAMToDetik(JAkh);
	if(d1 > d2)
	{
		return (86400 + d2 - d1);
	}
	else
	{
		return (d2-d1);
	}
}

JAM AddJAM(JAM J1, JAM J2)
/* Mengirim hasil J1 + J2 */
{
	/* ALGORITMA */
	return DetikToJAM(JAMToDetik(J1) + JAMToDetik(J2));
}
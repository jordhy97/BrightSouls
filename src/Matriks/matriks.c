/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada matriks.h */

#include <stdio.h>
#include "matriks.h"

boolean EndMATRIKS;
MATRIKS CMATRIKS;

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
	/* ALGORITMA */
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
	/* ALGORITMA */
	return BrsMin;
}

indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
	/* ALGORITMA */
	return KolMin;
}

indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
	/* ALGORITMA */
	return (NBrsEff(M) + BrsMin - 1);
}

indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
	/* ALGORITMA */
	return (NKolEff(M) + KolMin - 1);
}

/* ********** Assignment  MATRIKS ********** */
void AssignMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
	/* ALGORITMA */
	*MHsl = MIn;
}


/* ********* I/O MATRIKS ************** */
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
      if(j != GetLastIdxKol(M))
      {
        printf(" ");
      }
    }
    printf("\n");
  }
}

/* ********** Load MATRIKS ********** */
void STARTMATRIKS(char *namafile)
/* I.S. : CC sembarang, file dengan nama namafile terdefinisi dan siap dibaca
   F.S. : EndMATRIKS = true, dan CC = MARK; 
          atau EndMATRIKS = false, CMATRIKS adalah MATRIKS yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir MATRIKS 
   Proses : Membuka file dengan nama namafile dan membaca ukuran MATRIKS yang akan dibaca dan membuat MATRIKS CMATRIKS dengan ukuran tersebut, kemudian mengakuisisi MATRIKS dengan procedure SalinMATRIKS */
{
	/* KAMUS LOKAL */
		int NB, NK;

	/* ALGORITMA */
	{
		START(namafile);
		if(CC == MARK)
		{
			EndMATRIKS = true;
		}
		else
		{
      EndMATRIKS = false;
			NB = 0;
			NK = 0;
			while(CC != BLANK)
			{
				NB = (NB*10) + (CC - '0');
				ADV();

			}
			ADV();
			while(CC != ENTER)
			{
				NK = (NK*10) + (CC - '0');
				ADV();
			}
      ADV();
			MakeMATRIKS(NB, NK, &CMATRIKS);
			SalinMATRIKS();
		}
	}
}

void ADVMATRIKS()
/* I.S. : CC adalah karakter pertama MATRIKS yang akan diakuisisi 
   F.S. : CMATRIKS adalah MATRIKS terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari MATRIKS berikutnya, mungkin MARK
          Jika CC = MARK, maka EndMATRIKS = true      
   Proses : Akuisisi MATRIKS menggunakan procedure SalinMATRIKS */
{
    /* ALGORITMA */
    if(CC != MARK)
    {
    	while((CC == ENTER) || (CC == BLANK))
    	{
    		ADV();
    	}
        SalinMATRIKS();
    }
    else
    {
        EndMATRIKS = true;
    }
}

void SalinMATRIKS()
/* Mengakuisisi MATRIKS, menyimpan dalam CMATRIKS  
   I.S. : CC adalah karakter pertama dari MATRIKS
   F.S. : CMATRIKS berisi MATRIKS yang sudah diakuisisi; 
          CC = MARK atau CC = baris kosong; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi. */
{
    /* KAMUS LOKAL */
    int baris, kol;

    /* ALGORITMA */
    baris = 1;
    kol = 1;
    for(;;)
    {
        if(CC == ENTER)
        {
        	ADV();
        	if((CC == MARK) || (CC == ENTER))
        	{
        		break;
        	}
        	else
        	{
        		baris++;
        		kol = 1;
        	}
        }
        else
        {
          Elmt(CMATRIKS,baris,kol) = CC;
        	kol++;
        	ADV();
        	if(CC == MARK)
	        {
	            break;
	        }
        }
    }
    while(CC == ENTER)
    {
      ADV();
    }
}
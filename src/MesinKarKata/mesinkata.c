#include "mesinkata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;

/* KONSTRUKTOR */
void CreateKata(Kata *K, char *s)
/* I.S. : K sembarang, s terdefinisi dan tidak mengandung BLANK */
/* F.S. : K berisi string s yang diubah menjadi tipe Kata */
{
  /* KAMUS LOKAL */
  int i;

  /* ALGORITMA */
  i = 0;
  while(s[i] != '\0')
  {
    (*K).TabKata[i+1] = s[i];
    i++;
  }
  (*K).Length = i;
}

/* I/O */
void BacaKata(Kata *K)
/* I.S. : K sembarang */
/* F.S. : K berisi kata yang merupakan input dari user */
/* Proses : Membaca input dari user sampai diinput ENTER atau BLANK */
{
  /* KAMUS LOKAL */
  int i;
  char C;

  /* ALGORTIMA */
  i=0;
  scanf("%c", &C);
  while ((C != ENTER) && (C != BLANK))
  {
      i++;
      (*K).TabKata[i]=C;
      scanf("%c", &C);
  }
  (*K).Length = i;
}

/* I/O KHUSUS NCURSES */
void wBacaKata(WINDOW *win, Kata *K)
/* I.S. : K sembarang */
/* F.S. : K berisi kata yang merupakan input dari user */
/* Proses : Membaca input dari user sampai diinput ENTER atau BLANK */
{
  /* KAMUS LOKAL */
  int i, x, y, C;

  /* ALGORITMA */
  i = 0;
  keypad(win,TRUE);
  C = wgetch(win);
  while ((C != ENTER) && (C != BLANK))
  {
    if(C == KEY_BACKSPACE)
    {
      if(i != 0)
      {
        getyx(win, y, x);
        wprintw(win, " ");
        wmove(win,y, x);
        wrefresh(win);
        i--;
      }
      else
      {
        getyx(win, y, x);
        wmove(win,y, x + 1);
      }
    }
    else
    {
      i++;
      (*K).TabKata[i]= (char) C;
    }
    C = wgetch(win);
  }
  keypad(win,FALSE);
  (*K).Length = i;
}

void wTulisKata(WINDOW *win, Kata K)
/* I.S. : K terdefinisi */
/* F.S. : K ditampilkan ke layar win */
{
  /* KAMUS LOKAL */
  int i;

  /* ALGORITMA */
  for(i = 1; i <= K.Length; i++)
  {
    wprintw(win, "%c", K.TabKata[i]);
  }
}

/* MESIN KATA */
void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{
  /* ALGORITMA */
  while ((CC == BLANK) && (CC != MARK))
  ADV();
}

void STARTKATA(char *namafile)
/* I.S. : CC sembarang, namafile adalah namafile eksternal yang ingin diakses 
   F.S. : EndKata = true, dan CC = MARK{} 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
  /* ALGORITMA */
  START(namafile);
  IgnoreBlank();
  if (CC == MARK)
    EndKata = true;
  else
  {
    EndKata = false;
    SalinKata();
  }
}

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.     
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
  /* ALGORITMA */
  IgnoreBlank();
  if (CC == MARK)
    EndKata = true;
  else
  {
    SalinKata();
    IgnoreBlank();
  }
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi{} 
          CC = BLANK atau CC = MARK{} 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
  /* KAMUS LOKAL */
  int i; 

  /* ALGORITMA */
  i=1;
  for (;;) 
  {
    CKata.TabKata[i] = CC;
    ADV();
    if ((CC == MARK) || (CC == BLANK) || (i>NMax))
      break;
    else
      i++;
  }
  CKata.Length = i;
}

/* TEST KATA */
boolean IsKataSama (Kata K1, Kata K2)
/*  Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama 
  dan urutan karakter yang menyusun kata juga sama */
{
  /*  KAMUS LOKAL */
  int i;

  /*  ALGORITMA */
  if (K1.Length==K2.Length) 
  {
    i = 1;
    while ((i<K1.Length)&&(K1.TabKata[i]==K2.TabKata[i])) 
    {
      i++;
    }
    return (K1.TabKata[i]==K2.TabKata[i]);
  } 
  else 
  {
    return (K1.Length==K2.Length);
  }
}

boolean IsKataEmpty(Kata K)
/* Mengembalikan true jika K kosong (K.Length = 0) dan false jika tidak */
{
  /* ALGORITMA */
  return (K.Length == 0);
}

/* CONVERT KATA KE TIPE LAIN */
int KataToInteger (Kata K)
/* Prekondisi: K tedefinisi*/
/* Mengembalikan hasil konversi K menjadi bilangan bertipe integer */
{
  /* KAMUS LOKAL */
  int bil, X, i;

  /* ALGORITMA */
  bil = 0;
  for (i = 1; i <= K.Length; i++)
  {
    X = (K.TabKata[i] - '0');
    bil = (bil * 10) + X;
  }
  return bil;
}
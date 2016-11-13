#include "mesinkata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;
void BacaKata(Kata *K)
/* I.S. : K sembarang */
/* F.S. : K berisi kata yang merupakan input dari user */
/* Proses : Membaca input dari user sampai diinput ENTER atau BLANK */
{
  int i;
  char C;
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

void wBacaKata(WINDOW *win, Kata *K)
/* I.S. : K sembarang */
/* F.S. : K berisi kata yang merupakan input dari user */
/* Proses : Membaca input dari user sampai diinput ENTER atau BLANK */
{
  int i, x, y, C;
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
{
  /* KAMUS LOKAL */
  int i;

  /* ALGORITMA */
  for(i = 1; i <= K.Length; i++)
  {
    wprintw(win, "%c", K.TabKata[i]);
  }
}

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{
  while ((CC == BLANK) && (CC != MARK))
  ADV();
}

void STARTKATA(char *namafile)
/* I.S. : CC sembarang, namafile adalah namafile eksternal yang ingin diakses 
   F.S. : EndKata = true, dan CC = MARK{} 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
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
  int i; 
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

boolean IsKataSama (Kata K1, Kata K2)
/*  Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama 
  dan urutan karakter yang menyusun kata juga sama */
{
  /*  Kamus */
  int i=1;
  /*  Algoritma */
  if (K1.Length==K2.Length) 
  {
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

int KataToInteger (Kata K)
/* Prekondisi: K tedefinisi*/
/* Mengembalikan hasil konversi K menjadi bilangan bertipe integer */
{
  int bil, X, i;
  bil = 0;
  for (i = 1; i <= K.Length; i++)
  {
    X = (K.TabKata[i] - '0');
    bil = (bil * 10) + X;
  }
  return bil;
}
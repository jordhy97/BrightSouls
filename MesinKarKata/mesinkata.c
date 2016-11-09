#include "boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;
void BacaKata(Kata (*K)){
  int i;
  char C;
  C='a';
  i=0;
  while (C!='\n'){
    scanf("%c", &C);
    if (C!='\n'){
      i++;
      (*K).TabKata[i]=C;
    }
  }
  ((*K)).Length=i;
}

void IgnoreBlank(){
  while ((CC == BLANK) && (CC != MARK))
    ADV();
}
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA(char *C){
  START(C);
  IgnoreBlank();
  if (CC == MARK)
    EndKata = true;
  else{
    EndKata = false;
    SalinKata();
  }
}
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK{} 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA(){
  IgnoreBlank();
  if (CC == MARK)
    EndKata = true;
  else
    SalinKata();
  IgnoreBlank();
}
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.     
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata(){
  int i; 
  i=1;
  for (;;) {
    CKata.TabKata[i] = CC;
    ADV();
    if ((CC == MARK) || (CC == BLANK) || (i>NMax))
      break;
    else
      i++;
  }
  CKata.Length = i;
}
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi{} 
          CC = BLANK atau CC = MARK{} 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

boolean IsKataSama (Kata K1, Kata K2) {
/*  Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama 
  dan urutan karakter yang menyusun kata juga sama */
  /*  Kamus */
  int i=1;
  /*  Algoritma */
  if (K1.Length==K2.Length) {
    while ((i<K1.Length)&&(K1.TabKata[i]==K2.TabKata[i])) {
      i++;
    }
    return (K1.TabKata[i]==K2.TabKata[i]);
  } else {
    return (K1.Length==K2.Length);
  }
}
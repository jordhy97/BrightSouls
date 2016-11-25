#include "bintree.h"
#include <stdlib.h>
#include "../MesinKarKata/mesinkar.h"

void copystring (char *dest, char *source)
/* I.S. dest sembarang, source teredefinisi */
/* F.S. dest berisi source */
{
    /* KAMUS LOKAL */
    int i;

    /* ALGORITMA */
    i = 0;
    while(source[i] != '\0')
    {
        dest[i] = source[i];
        i++;
    }
    dest[i] = '\0';
}

/* *** Konstruktor *** */
BinTree Tree (infoTree Akar, BinTree L, BinTree R)
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (NilTree) jika alokasi gagal */
{
    /* KAMUS LOKAL */
    BinTree B;

    /* ALGORITMA */
    B = AlokNode(Akar);
    if(B != NilTree)
    {
        Left(B) = L;
        Right(B) = R;
    }
    return B;
}

void MakeTree (infoTree Akar, BinTree L, BinTree R, BinTree *P)
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R 
        jika alokasi berhasil. P = NilTree jika alokasi gagal. */
{
    /* ALGORITMA */
    *P = Tree(Akar,L,R);
}
        
/* Manajemen Memory */
addrNode AlokNode (infoTree X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak NilTree, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = NilTree, Right(P)=NilTree */
/* Jika alokasi gagal, mengirimkan NilTree */
{
    /* KAMUS LOKAL */
    addrNode P;

    /* ALGORITMA */
    P = (addrNode) malloc (sizeof(Node));
    if(P != NilTree)
    {
       copystring(SkillName(Akar(P)), SkillName(X));
       copystring(Description(Akar(P)), Description(X));
       Unlocked(Akar(P)) = Unlocked(X);
       SkillID(Akar(P)) = SkillID(X);
       Left(P) = NilTree;
       Right(P) = NilTree;
    }
    return P;
}

void DealokNode (addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
    /* ALGORITMA */
    free(P);
}

void DealokTree(BinTree *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
{
    /* ALGORITMA */
    if(!IsTreeEmpty(*P))
    {
        DealokTree(&Left(*P));
        DealokTree(&Right(*P));
        DealokNode(*P);
        *P = NilTree;
    }
}

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty (BinTree P)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
    /* ALGORITMA */
    return (P == NilTree);
}


/* Output */
void PrintTree (BinTree P, int level, int h)
/* I.S. P terdefinisi, level adalah kedalaman dari node dengan level Akar(P) = 0, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
{
    /* KAMUS LOKAL */
    int i;

    /* ALGORITMA */
    if(!IsTreeEmpty(P) && Unlocked(Akar(P)))
    {
        for(i = 1; i <= level * h; i++)
        {
              printf("-");
        }
        printf(">%s\n", SkillName(Akar(P)));
        for(i = 1; i <= level * h; i++)
        {
              printf("-");
        }
        printf(">%s\n", Description(Akar(P)));
        if(!IsTreeEmpty(Left(P)))
        {
           
            PrintTree(Left(P), level + 1, h);
        }
        if(!IsTreeEmpty(Right(P)))
        {
            PrintTree(Right(P), level + 1, h);
        }
    }
}

void wPrintTree (WINDOW *win, BinTree P, int level, int h)
/* I.S. win, P terdefinisi, level adalah kedalaman dari node dengan level Akar(P) = 0, h adalah jarak indentasi (spasi)  (Khusus Ncurses) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
{
    /* KAMUS LOKAL */
    int i;

    /* ALGORITMA */
    if(!IsTreeEmpty(P) && Unlocked(Akar(P)))
    {
        for(i = 1; i <= level * h; i++)
        {
              wprintw(win, "-");
        }
        wprintw(win, ">%s\n", SkillName(Akar(P)));
        for(i = 1; i <= level * h; i++)
        {
              wprintw(win, " ");
        }
        wprintw(win, " %s", Description(Akar(P)));
        if(!IsTreeEmpty(Left(P)) && Unlocked(Akar(Left(P))))
        {
            wprintw(win, "\n");
            wPrintTree(win, Left(P), level + 1, h);
        }
        if(!IsTreeEmpty(Right(P)) && Unlocked(Akar(Right(P))))
        {
            wprintw(win, "\n");
            wPrintTree(win, Right(P), level + 1, h);
        }
    }
}

/* *** Searching *** */
boolean SearchTree (BinTree P, int ID)
/* Mengirimkan true jika ada node dari P yang ber-ID ID */
{
    /* ALGORITMA */
    if(IsTreeEmpty(P))
    {
        return false;
    }
    else if(SkillID(Akar(P)) == ID)
    {
        return true;
    }
    else
    {
        return ((SearchTree(Left(P), ID)) || SearchTree(Right(P), ID));
    }

}
/* FILE EKSTERNAL */
void LoadTree(char *namafile, BinTree *P)
/* namafile terdefiinsi, P P kosong */
/* P berisi data dari file eksternal dengan nama namafile */
{
    /* KAMUS LOKAL */
    int i, Parent;
    infoTree X;
    boolean Kiri;

    /* ALGORTIMA */
    START(namafile);
    SkillID(X) = 0;
    while(CC != BLANK)
    {
        SkillID(X) = SkillID(X) * 10 + (CC - '0');
        ADV();
    }
    ADV();
    Unlocked(X) = CC - '0';
    ADV();
    ADV();
    Parent = 0;
    while(CC != BLANK)
    {
        Parent = Parent * 10 + (CC - '0');
        ADV();
    }
    ADV();
    Kiri = CC - '0';
    ADV();
    ADV();
    i = 0;
    while(CC != ENTER)
    {
        SkillNamechar(X,i) = CC;
        i++;
        ADV();
    }
    SkillNamechar(X,i) = '\0';
    ADV();
    i = 0;
    while(CC != ENTER)
    {
        Descriptionchar(X,i) = CC;
        i++;
        ADV();
    }
    Descriptionchar(X,i) = '\0';
    MakeTree(X, NilTree, NilTree, P);
    ADV();
    while(CC != MARK)
    {
        SkillID(X) = 0;
        while(CC != BLANK)
        {
            SkillID(X) = SkillID(X) * 10 + (CC - '0');
            ADV();
        }
        ADV();
        Unlocked(X) = CC - '0';
        ADV();
        ADV();
        Parent = 0;
        while(CC != BLANK)
        {
            Parent = Parent * 10 + (CC - '0');
            ADV();
        }
        ADV();
        Kiri = CC - '0';
        ADV();
        ADV();
        i = 0;
        while(CC != ENTER)
        {
            SkillNamechar(X,i) = CC;
            i++;
            ADV();
        }
        SkillNamechar(X,i) = '\0';
        ADV();
        i = 0;
        while(CC != ENTER && CC != MARK)
        {
            Descriptionchar(X,i) = CC;
            i++;
            ADV();
        }
        Descriptionchar(X,i) = '\0';
        AddDaun(P, Parent, X, Kiri);
        if(CC == ENTER)
        {
            ADV();
        }
    }
}

void SaveTree(char *namafile, BinTree P)
/* I.S. namafile dan P terdefinisi */
/* F.S. file eksternal dengan nama namafile berisi data P */
{
    /* KAMUS LOKAL */
    FILE *fout;

    /* ALGORITMA */
    fout = fopen(namafile, "w");
    SaveTree2(fout, P, 0, 0);
    fprintf(fout, "%c", MARK);
    fclose(fout);
}

void SaveTree2(FILE *fout, BinTree P, int Parent, boolean Kiri)
/* I.S. fout, P, Parent, dan Kiri terdefinisi */
/* F.S. FILE fout berisi data P sesuai format yang ada */
{
    if(!IsTreeEmpty(P))
    {
        fprintf(fout, "%d %d\n%d %d\n%s\n%s\n", SkillID(Akar(P)), Unlocked(Akar(P)), Parent, Kiri, SkillName(Akar(P)), Description(Akar(P)));
        SaveTree2(fout, Left(P), SkillID(Akar(P)), 1);
        SaveTree2(fout, Right(P), SkillID(Akar(P)), 0);
    }
}

/* *** Operasi lain *** */
void AddDaun (BinTree *P, int ID, infoTree Y, boolean Kiri)
/* I.S. P tidak kosong, ID adalah salah satu ID daun Pohon Biner P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau 
        sebagai anak Kanan X (jika Kiri = false) */
{
    /* ALGORITMA */
    if(SkillID(Akar(*P)) == ID)
    {
        if(Kiri)
        {
            Left(*P) = AlokNode(Y);
        }
        else
        {
            Right(*P) = AlokNode(Y);
        }
    }
    else
    {
        if(SearchTree(Left(*P), ID))
        {
            AddDaun(&Left(*P), ID, Y, Kiri);
        }
        else
        {
            AddDaun(&Right(*P), ID, Y, Kiri);
        }
    }
}

void UnlockSkill(BinTree *P, int ID)
/* I.S. P dan ID terdefinisi, infoTree dengan SkillID ID pasti ada di P */
/* F.S. Skill dengan SkillID ID di unlock */
{
    /* ALGORITMA */
    if(SkillID(Akar(*P)) == ID)
    {
        Unlocked(Akar(*P)) = true;
    }
    else
    {
        if(SearchTree(Left(*P), ID))
        {
            UnlockSkill(&Left(*P), ID);
        }
        else
        {
            UnlockSkill(&Right(*P), ID);
        }
    }
}
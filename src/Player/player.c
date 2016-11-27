/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada player.h */

#include <stdio.h>
#include "player.h"
#include <time.h>
#include <stdlib.h>

void SavePlayer(Player P, char *namafilePlayer, char *namafileSkill)
/* I.S. P terdefinisi, namafile terdefinisi */
/* F.S. data P tersimpan file eksternal*/
{
    /* KAMUS LOKAL */
    FILE *fout;
    int i;

    /* ALGORITMA */
    fout = fopen(namafilePlayer, "w");
    for(i = 1; i <= Name(P).Length; i++)
    {
        fprintf(fout, "%c", Name(P).TabKata[i]);    
    }
    fprintf(fout, "\n%d\n%d\n%d\n%d\n%d\n%d\n%d %d\n%d", Max_HP(P), HP(P), Strength(P), Defense(P), Exp(P), Level(P), Absis(Position(P)), Ordinat(Position(P)), CArea(P));
    fprintf(fout, "%c", MARK);
    fclose(fout);
    SaveTree(namafileSkill, Skill(P));
}

void LoadPlayer (Player *P, char *namafilePlayer, char *namafileSkill)
/* I.S. P sembarang, namafilePlayer dan namafileSkill terdefinisi */
/* F.S. P berisi data player dari file eksternal*/
{
    /* ALGORITMA */
    STARTKATA(namafilePlayer);
    Name(*P) = CKata;
    ADVKATA();
    Max_HP(*P) = KataToInteger(CKata);
    ADVKATA();
    HP(*P) = KataToInteger(CKata);
    ADVKATA();
    Strength(*P) = KataToInteger(CKata);
    ADVKATA();
    Defense(*P) = KataToInteger(CKata);
    ADVKATA();
    Exp(*P) = KataToInteger(CKata);
    ADVKATA();
    Level(*P) = KataToInteger(CKata);
    ADVKATA();
    Absis(Position(*P)) = KataToInteger(CKata);
    ADVKATA();
    Ordinat(Position(*P)) = KataToInteger(CKata);
    ADVKATA();
    CArea(*P) = KataToInteger(CKata);
    LoadTree(namafileSkill, &Skill(*P));
}

void CreatePlayer (Player *P, char *namafile)
/* I.S. P sembarang, namafile terdefinisi */
/* F.S. Membentuk player baru dengan status yang sudah ditentukan berdasarkan pilihan user*/ 
{
    /* KAMUS LOKAL */
    int input;

    /* ALGORITMA */
    printf("Enter Player Name: ");
    BacaKata(&Name(*P));
    printf("Choose Player Speciality\n1. Balance\n2. HP\n3. Strength\n4. Defense\nChoice: ");
    scanf("%d",&input);
    if (input == 1) {
        Max_HP(*P) = 50;
        HP(*P) = 50;
        Strength(*P) = 5;
        Defense(*P) = 5;
    }
    else if (input == 2) {
        Max_HP(*P) = 70;
        HP(*P) = 70;
        Strength(*P) = 3;
        Defense(*P) = 3;
    }
    else if (input == 3) {
        Max_HP(*P) = 40;
        HP(*P) = 40;
        Strength(*P) = 7;
        Defense(*P) = 3;
    }
    else if (input == 4) {
        Max_HP(*P) = 40;
        HP(*P) = 40;
        Strength(*P) = 3;
        Defense(*P) = 7;
    }
    CArea(*P) = 1;
    Position(*P) = MakePOINT(6,4);
    LoadTree(namafile, &Skill(*P));
    Exp(*P) = 0;
    Level(*P) = 1;
}

void print_choice(WINDOW *menu_win, int pilihan)
/* I.S. menu_win dan pilihan[1..4] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */
{
    /* KAMUS LOKAL */
    int i;  
    char *choices[] = {"Balance","Warrior","Knight","Cancel"};
    char *description[] = {"(Has balanced stats)", "(Has higher strength but lower HP and defense)", "(Has higher HP and defense but lower strength)", " "};

    /* ALGORITMA */
    wattron(menu_win, COLOR_PAIR(1));
    mvwprintw(menu_win,3,1, " Choose Player Speciality:");
    wrefresh(menu_win);
    for(i = 1; i < 5; i++)
    {   
        if(pilihan == i) 
        {    
            mvwprintw(menu_win, (i+1) * 2, 1, ">%s", choices[i-1]);
            mvwprintw(menu_win, (i+1) * 2 + 1, 1, " %s", description[i-1]);
        }
        else
        {
            mvwprintw(menu_win, (i+1) * 2, 1, " %s", choices[i-1]);
            mvwprintw(menu_win, (i+1) * 2 + 1, 1, " %s", description[i-1]);

        }
    }
    wattroff(menu_win, COLOR_PAIR(1));
    wrefresh(menu_win);
}


void wCreatePlayer(WINDOW *menu, Player *P, Kata nama, boolean *created, char *namafile)
/* I.S. P sembarang, menu, nama, dan namafile terdefinisi, created sembarang */
/* F.S. Membentuk player baru dengan (P).name = nama dengan status yang sudah ditentukan berdasarkan pilihan user, created true jika player dibuat dan false jika tidak */ 
{
    /* KAMUS LOKAL */
    boolean chosen;
    int pilihan, ch;

    /* ALGORITMA */
    keypad(menu, TRUE);
    chosen = false;
    pilihan = 1;
    print_choice(menu, pilihan);
    while(!chosen)
    {
        ch = wgetch(menu);
        switch(ch)
        {
            case KEY_UP:
                if(pilihan == 1)
                {
                    pilihan = 4;
                }
                else
                {
                    pilihan--;
                }
                break;
            case KEY_DOWN:
                if(pilihan == 4)
                {
                    pilihan = 1;
                }
                else
                {
                    pilihan++;
                }
                break;
            case ENTER :
                chosen = true;
                break;
        }
        print_choice(menu, pilihan);
    }
    switch(pilihan)
    {
        case 1:
            Max_HP(*P) = 40;
            HP(*P) = 40;
            Strength(*P) = 4;
            Defense(*P) = 4;
            break;
        case 2:
            Max_HP(*P) = 35;
            HP(*P) = 35;
            Strength(*P) = 6;
            Defense(*P) = 2;
            break;
        case 3:
            Max_HP(*P) = 45;
            HP(*P) = 45;
            Strength(*P) = 2;
            Defense(*P) = 6;
            break;           
    }
    if(pilihan != 4)
    {
        Name(*P) = nama;
        Exp(*P) = 0;
        Level(*P) = 1;
        CArea(*P) = 1;
        Position(*P) = MakePOINT(6,4);
        LoadTree(namafile, &Skill(*P));
        *created = true;
    }
    else
    {
        *created = false;
    }
}

boolean IsLevelUp(Player P)
/* Menghasilkan true jika EXP P cukup untuk naik level */
{
    /* KAMUS LOKAL */
    int i, total;

    /* ALGORITMA */
    if(Level(P) == MaxLvl)
    {
        return false;
    }
    else
    {
        total = 0;
        for(i = 1; i <= Level(P); i++)
        {
            total += i * 10 + (i-1) * 5;
        }
        return (Exp(P) >= total);
    }
}

void LevelUp (Player * P) 
/* I.S. P terdefinisi */
/* F.S. level P naik dan stats P naik */
{
    /* KAMUS LOKAL */
    int bstr, bdef, bHP;

    /* ALGORITMA */
    srand(time(NULL));
    ++Level(*P);
    if(Level(*P) > 10)
    {
        bstr = rand() % 3 + 2;
        bdef = rand() % 3 + 2;
        bHP = rand() % 10 + 1;
    }
    else
    {
        bstr = rand() % 3 + 1;
        bdef = rand() % 3 + 1;
        bHP = rand() % 5 + 1;
    }
    Strength(*P) += bstr;
    Defense(*P) += bdef;
    HP(*P) += bHP;
    Max_HP(*P) += bHP;
}
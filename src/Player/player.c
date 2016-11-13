#include <stdio.h>
#include "player.h"

void CreatePlayer (Player * P, Kata nama)
/* I.S. P sembarang, nama terdefinisi */
/* F.S. Membentuk player baru dengan (P).name = nama dengan status yang sudah ditentukan berdasarkan pilihan user*/ 
{
   /* char c;
    int input, i = 0;
    printf("Enter Player Name: ");
    do {
        scanf("%c",&c);
        if (c != '\n') {
            Name(*P).word[i] = c;
            ++i;
        }
    } while (c != '\n' && i < 20);
    Name(*P).length = i; */
    int input;
    Name(*P) = nama;
    printf("Choose Player Speciality\n1. Balance\n2. HP\n3. Strength\n4. Defense\nChoice: ");
    scanf("%d",&input);
    if (input == 1) {
        HP(*P) = 50;
        Strength(*P) = 5;
        Defense(*P) = 5;
    }
    else if (input == 2) {
        HP(*P) = 70;
        Strength(*P) = 3;
        Defense(*P) = 3;
    }
    else if (input == 3) {
        HP(*P) = 40;
        Strength(*P) = 7;
        Defense(*P) = 3;
    }
    else if (input == 4) {
        HP(*P) = 40;
        Strength(*P) = 3;
        Defense(*P) = 7;
    }
    Exp(*P) = 0;
    Level(*P) = 1;
}

void print_choice(WINDOW *menu_win, int pilihan)
/* I.S. menu_win dan pilihan[1..5] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */
{
    /* KAMUS LOKAL */
    int i;  
    char *choices[] = {"Balance","HP","Strength","Defense","Cancel"};

    /* ALGORITMA */
    wattron(menu_win, COLOR_PAIR(1));
    mvwprintw(menu_win,2,1, "Choose Player Speciality:");
     wrefresh(menu_win);
    for(i = 3; i < 8; i++)
    {   
        if(pilihan == i - 2) 
        {    
            mvwprintw(menu_win, i, 1, ">%s", choices[i-3]);
        }
        else
        {
            mvwprintw(menu_win, i, 1, " %s", choices[i-3]);
        }
    }
    wattroff(menu_win, COLOR_PAIR(1));
    wrefresh(menu_win);
}


void wCreatePlayer(WINDOW *menu, Player *P, Kata nama)
/* I.S. P sembarang, menu dan nama terdefinisi */
/* F.S. Membentuk player baru dengan (P).name = nama dengan status yang sudah ditentukan berdasarkan pilihan user*/ 
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
                    pilihan = 5;
                }
                else
                {
                    pilihan--;
                }
                break;
            case KEY_DOWN:
                if(pilihan == 5)
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
            HP(*P) = 50;
            Strength(*P) = 5;
            Defense(*P) = 5;
            break;
        case 2:
            HP(*P) = 70;
            Strength(*P) = 3;
            Defense(*P) = 3;
            break;
        case 3:
            HP(*P) = 40;
            Strength(*P) = 7;
            Defense(*P) = 3;
            break;
        case 4 :
            HP(*P) = 40;
            Strength(*P) = 3;
            Defense(*P) = 7;
            break;            
    }
    if(pilihan != 5)
    {
        Name(*P) = nama;
        Exp(*P) = 0;
        Level(*P) = 1;
    }
}

void LevelUp (Player * P) {
    int input;
    printf("Level Up, Congratulations!\n1. HP\n2. Strength\n3. Defense\nChoice: ");
    scanf("%d",&input);
    if (input == 1) HP(*P) += 10;
    else if (input == 2) ++Strength(*P);
    else if (input == 3) ++Defense(*P);
    ++Level(*P);
    //Exp(*P) -= 100;
}

/*int main() {
    int i;
    Player P;
    CreateNewPlayer(&P);
    printf("\n");
    printf("Player Name: ");
    for (i = 0; i < Name(P).length; ++i) printf("%c",Name(P).word[i]);
    printf("\n");
    printf("HP: %d\nStr: %d\nDef: %d\nExp: %d\nLevel: %d\n",HP(P),Strength(P),Defense(P),Exp(P),Level(P));
    printf("\n");
    LevelUp(&P);
    printf("\n");
    printf("Player Name: ");
    for (i = 0; i < Name(P).length; ++i) printf("%c",Name(P).word[i]);
    printf("\n");
    printf("HP: %d\nStr: %d\nDef: %d\nExp: %d\nLevel: %d\n",HP(P),Strength(P),Defense(P),Exp(P),Level(P));
    printf("\n");
    return 0;
}*/

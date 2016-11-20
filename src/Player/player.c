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
    mvwprintw(menu_win,3,1, " Choose Player Speciality:");
     wrefresh(menu_win);
    for(i = 3; i < 8; i++)
    {   
        if(pilihan == i - 2) 
        {    
            mvwprintw(menu_win, i+1, 1, ">%s", choices[i-3]);
        }
        else
        {
            mvwprintw(menu_win, i+1, 1, " %s", choices[i-3]);
        }
    }
    wattroff(menu_win, COLOR_PAIR(1));
    wrefresh(menu_win);
}


void wCreatePlayer(WINDOW *menu, Player *P, Kata nama, boolean *created)
/* I.S. P sembarang, menu dan nama terdefinisi, created sembarang */
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
            Max_HP(*P) = 50;
            HP(*P) = 50;
            Strength(*P) = 5;
            Defense(*P) = 5;
            break;
        case 2:
            Max_HP(*P) = 70;
            HP(*P) = 70;
            Strength(*P) = 3;
            Defense(*P) = 3;
            break;
        case 3:
            Max_HP(*P) = 40;
            HP(*P) = 40;
            Strength(*P) = 7;
            Defense(*P) = 3;
            break;
        case 4 :
            Max_HP(*P) = 40;
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
        CArea(*P) = 1;
        *created = true;
    }
    else
    {
        *created = false;
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

void AddSkill (Player * P) {
/* Daftar skill player pada tiap level */
    // Asumsi level tertinggi player adalah level 20
    switch (Level(*P)) {
        case 2: // Extra HP -> HP +5 (3 rounds per battle)
            MakeTree(2,Nil,Nil,&Skill(*P));
			   break;
        case 4: // Extra Strength -> Str +1 (3 rounds per battle)
            AddDaun(&Skill(*P),2,4,1);
            break;
        case 6: // Extra Defense -> Def +1 (3 rounds per battle)
            AddDaun(&Skill(*P),2,6,0);
            break;
        case 8: // Swordsman -> Damage given +3 (3 rounds per battle)
            AddDaun(&Skill(*P),4,8,1);
            break;
        case 10: // Agile -> Damage taken -3 (3 rounds per battle)
            AddDaun(&Skill(*P),6,10,1);
            break;
        case 12: // Sharp Eye -> Know all enemy movements (3 rounds per battle)
            AddDaun(&Skill(*P),4,12,0);
            break;
        case 14: // Vampire -> Absorb 25% of enemy HP and add it to your own
            AddDaun(&Skill(*P),6,14,0);
            break;
        case 16: // Paralyzed Enemy -> Battle only have 5 rounds (1 time per map)
            AddDaun(&Skill(*P),8,16,1);
            break;
        case 17: // Veteran -> Exp x2 per battle (permanent)
            AddDaun(&Skill(*P),10,17,1);
            break;
        case 18: // Stealth -> Avoid Enemy (1 time per map)
            AddDaun(&Skill(*P),12,18,1);
            break;
        case 19: // Super Healer -> Heal yourself 100% (1 time per battle)
            AddDaun(&Skill(*P),14,19,1);
            break;

	}
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

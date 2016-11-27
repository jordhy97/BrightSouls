/* File: Driver untuk ADT Player */

#include <stdio.h>
#include "player.h"
#include <time.h>
#include <stdlib.h>

int main() 
{
    /* KAMUS */
    Player P;
    infoTree Y;

    /* ALGORITMA */
    printf("TESTING Player\n\n");
    CreatePlayer(&P, "../../src/Player/skill.txt");
    printf("\n");
    printf("Player Name: ");
    TulisKata(Name(P));
    printf("\n");
    printf("HP: %d/%d\nStr: %d\nDef: %d\nExp: %d\nLevel: %d\nCArea: %d\nPosition: <%d,%d>\n",HP(P), Max_HP(P), Strength(P),Defense(P),Exp(P),Level(P), CArea(P), Absis(Position(P)), Ordinat(Position(P)));
    printf("Skill:\n");
    if(!IsUnlocked(Skill(P),SkillID(Akar(Skill(P)))))
    {
        printf("%s not Unlocked\n",SkillName(Akar(Skill(P))));
        /* Unlocking skill */
        UnlockSkill(&Skill(P), 1, &Y);
        printf("%s Unlocked\n", SkillName(Akar(Skill(P))));
    }
    PrintTree(Skill(P), 0, 3);
    printf("\n");
    Exp(P) = 100;
    if(IsLevelUp(P))
    {
        LevelUp(&P);
        printf("Level Up!\n");
        printf("Player Name: ");
        TulisKata(Name(P));
        printf("\n");
        printf("HP: %d/%d\nStr: %d\nDef: %d\nExp: %d\nLevel: %d\nCArea: %d\nPosition: <%d,%d>\n",HP(P), Max_HP(P), Strength(P),Defense(P),Exp(P),Level(P), CArea(P), Absis(Position(P)), Ordinat(Position(P)));
        printf("\n");
    }
    printf("TESTING Save and Load Player...\n\n");
    SavePlayer(P, "../../src/Player/testplayer.txt", "../../src/Player/savedskill.txt");
    LoadPlayer(&P, "../../src/Player/testplayer.txt", "../../src/Player/savedskill.txt");
    printf("Player Name: ");
    TulisKata(Name(P));
    printf("\n");
    printf("HP: %d/%d\nStr: %d\nDef: %d\nExp: %d\nLevel: %d\nCArea: %d\nPosition: <%d,%d>\n",HP(P), Max_HP(P), Strength(P),Defense(P),Exp(P),Level(P), CArea(P), Absis(Position(P)), Ordinat(Position(P)));
    printf("Skill:\n");
    PrintTree(Skill(P), 0, 3);
    printf("\n");
    return 0;
}

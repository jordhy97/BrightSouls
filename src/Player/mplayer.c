#include <stdio.h>
#include "player.h"
#include <time.h>
#include <stdlib.h>

int main() {
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
}
